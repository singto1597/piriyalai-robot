#include <POP32.h>
#include "Adafruit_TCS34725.h"
#include "config.h"      // ค่าคงที่/ค่าจูนทั้งหมดของหุ่นยนต์ (แก้ไฟล์นี้ไฟล์เดียว)

//////////////////////////////////////////////////////////////
// หุ่นยนต์ระดับสูง 4 ล้อ (POP32) — โหมด RGB 5/6/7/8
//   5/6 : เช็คสีทีละช่อง (5 = เลี้ยวขวา, 6 = เลี้ยวซ้าย)
//   7/8 : วิ่งตรงยาว       (7 = เลี้ยวขวา, 8 = เลี้ยวซ้าย)
// ไฟล์นี้ = ตัวล็อกอิน (entry point): ตัวแปรกลาง + setup() + loop()
//   Driver_*  = ควบคุมฮาร์ดแวร์ (มอเตอร์/เซนเซอร์/เซอร์โว)
//   Logics_*  = ลอจิกการตัดสินใจ (แทร็กเส้น/เช็คสี/นำทาง)
//////////////////////////////////////////////////////////////

// ===== ฮาร์ดแวร์ส่วนกลาง =====
// เซนเซอร์สี TCS34725 (อ่าน/เริ่มต้น อยู่ใน Driver_RgbSensor.ino)
Adafruit_TCS34725 tcs = Adafruit_TCS34725(COLOR_START_INTEGRATION_TIME, COLOR_GAIN);

// ===== ความเร็ว (ค่าเริ่มต้นมาจาก config.h, เปลี่ยนได้จากเมนู) =====
int speed = DEFAULT_SPEED;                // ความเร็วหลัก
int pivotSpeed = DEFAULT_PIVOT_SPEED;     // ความเร็วหมุนวนจัดตำแหน่ง
int slowSpeed = DEFAULT_SLOW_SPEED;       // ความเร็วช้า (ปรับตำแหน่ง)
int accSpeed = DEFAULT_ACC_SPEED;         // ความเร็วเร่ง
int baseSpeed = DEFAULT_SPEED;            // ความเร็วฐานปัจจุบัน (คำนวณสำหรับ PID)
int turnSpeed = DEFAULT_TURN_SPEED;       // ความเร็วเลี้ยว
int maxSpeed = PID_OUTPUT_LIMIT;          // ความเร็วสูงสุด (จำกัด Output ของ PID)
int leftBaseSpeed, rightBaseSpeed;         // ความเร็วฐานล้อหน้า (ซ้าย/ขวา)
int backLeftBaseSpeed, backRightBaseSpeed; // ความเร็วฐานล้อหลัง (ซ้าย/ขวา)

// ===== PID เดินตามเส้น (เซนเซอร์หน้า) =====
int lineError;                 // error ตำแหน่งเส้น (-5..LINE_ERROR_CENTER)
int prevLineError;             // error ของรอบก่อนหน้า (สำหรับ Kd)
int integral;                  // ค่า integral สะสม (สำหรับ Ki)
int kp, kd, ki;                // เกน PID
int pidLoopDelayMs;            // หน่วงเวลาของวง PID

// ===== ค่าอ้างอิงเซนเซอร์เส้น (เริ่มต้นจาก config.h, calibrate ใหม่ได้ตอนเริ่ม) =====
int refL3 = REF_LINE_L3, refL2 = REF_LINE_L2, refL1 = REF_LINE_L1, refC = REF_LINE_C;
int refR1 = REF_LINE_R1, refR2 = REF_LINE_R2, refR3 = REF_LINE_R3;   // เซนเซอร์หน้า 7 ตัว
int refBackL = REF_BACK_LEFT, refBackR = REF_BACK_RIGHT;             // เซนเซอร์หลัง 2 ตัว
int refLimitSwitch = REF_LIMIT_SWITCH;   // ค่าอ้างอิงลิมิตสวิตช์ (ตะเกียบ/สะพาน)

// ===== ค่าเซนเซอร์เส้น (0 = เจอดำ, 1 = ขาว) =====
int sensorL3, sensorL2, sensorL1, sensorC, sensorR1, sensorR2, sensorR3;
int backL, backR;              // เซนเซอร์หลัง

// ===== นาฬิกาจับเวลา (millis) 5 ตัว =====
long stopwatchMs, stopwatch1Ms, stopwatch2Ms, stopwatch3Ms, stopwatch4Ms;

// ===== โหมดการทำงาน =====
// 5 : เช็คทีละช่อง เลี้ยวขวา (กด SW_A สั้นๆ)
// 6 : เช็คทีละช่อง เลี้ยวซ้าย (กด SW_A ค้าง 1 วิ)
// 7 : วิ่งตรงยาว เลี้ยวขวา
// 8 : วิ่งตรงยาว เลี้ยวซ้าย
int robotMode = DEFAULT_ROBOT_MODE;

// ===== สี (RGB) =====
long refBlue = REF_COLOR_BLUE, refGreen = REF_COLOR_GREEN, refBlack = REF_COLOR_BLACK;
long refWhite = REF_COLOR_WHITE, refYellow = REF_COLOR_YELLOW, refRed = REF_COLOR_RED;   // ค่าอ้างอิงสี
int floorColor;                // สีพื้นปัจจุบัน
int colorRank[6] = {Blue, Green, Black, White, Yellow, Red};   // ลำดับค่าอ้างอิงสี (index: Blue..Red)

int redCount = 0, yellowCount = 0, blueCount = 0, greenCount = 0;   // จำนวนลูกบาศก์ที่ปล่อยไป
int bridgeStatus = 0;          // 0 = ปกติ, 1 = ขึ้นสะพาน, 2 = ลงสะพาน

// ===== โหมดทดสอบ (เลือกจาก knob ตอนเริ่ม) =====
int modeSelect = 0;
int knobValue = 0;

void setup() {
  baseSpeed = speed;
  updateSpeedPidParams();

  // ใช้ RGB sensor จำแนกสีพื้น (โหมด 5-8 ใช้สีพื้นตลอด)
  initColorSensor();
  delay(COLOR_INIT_SETTLE_MS);
  detectFloorColor();      // อ่านสี 1 ครั้งตอน boot (เพื่อให้ showColorValue แสดงค่าจริง — ไม่อ่านซ้ำระหว่างวิ่ง)
  showColorValue();
  delay(COLOR_SHOW_HOLD_MS);
  beep(0);

  // หน้าจอต้อนรับ + แสดงโหมด/ความเร็ว
  oled.clear();
  oled.mode(0);
  oled.dim(true);
  oled.textSize(1);
  oled.text(0, 0, " PHIRIYALAI SCHOOL");
  oled.text(1, 0, " High 4 Wheels POP32");
  oled.text(2, 0, "      PR_ROBOT    ");
  oled.text(3, 0, "     Speed = %d   ", speed);
  oled.text(4, 0, "     ACCSpeed=%d", accSpeed);
  oled.text(5, 0, "       Mode = %d   ", robotMode);
  oled.show();

  // เลือกโหมดที่หน้าจอก่อนเริ่มงาน:
  //  - หมุน knob + กด SW_B สั้นๆ   = ทดสอบโหมดตามตำแหน่ง knob (0-5)
  //  - กด SW_B ค้าง >= SW_HOLD_SERVO_CAL_MS = ทดสอบเซอร์โว + ตั้งค่าอ้างอิงใหม่
  //  - กด SW_A สั้นๆ                 = โหมด 5 (เช็คทีละช่อง เลี้ยวขวา)
  //  - กด SW_A ค้าง >= SW_HOLD_MODE6_MS  = โหมด 6 (เช็คทีละช่อง เลี้ยวซ้าย)
  while (1) {
    knobValue = knob();
    modeSelect = map(knobValue, KNOB_ADC_MIN, KNOB_ADC_MAX, TEST_MODE_MIN, TEST_MODE_MAX);
    oled.text(7, 0, "   TESTMode = %d   ", modeSelect);
    oled.show();
    if (SW_B()) {
      startStopwatch();
      beep(1);
      while (SW_B()) {
        if (stopwatchElapsed() >= SW_HOLD_SERVO_CAL_MS) {   // กดค้าง: ทดสอบเซอร์โว + calibrate
          beep(2);
          testServo();
          calibrateSensors();
          break;
        }
      }
      runTestMode(modeSelect);
      break;
    }
    if (SW_A()) {
      startStopwatch();
      beep(1);
      while (SW_A()) {}
      if (stopwatchElapsed() >= SW_HOLD_MODE6_MS) robotMode = 6;   // กดค้าง = โหมด 6
      else robotMode = 5;                                          // กดสั้น = โหมด 5
      break;
    }
  }

  // เริ่มวิ่งจริง
  baseSpeed = speed;
  oled.clear();
  oled.textSize(2);
  oled.text(0, 0, "  Starting   ");
  oled.text(1, 0, "   Mode=%d   ", robotMode);
  oled.show();
  startStopwatch2();
}

void loop() {
  switch (robotMode) {
    case 5: autoScanCellsRgb(); break;   // เช็คทีละช่อง
    case 6: autoScanCellsRgb(); break;   // เช็คทีละช่อง
    case 7: autoDriveLaneRgb(); break;   // วิ่งตรงยาว
    case 8: autoDriveLaneRgb(); break;   // วิ่งตรงยาว
  }
  finishRun();
}
