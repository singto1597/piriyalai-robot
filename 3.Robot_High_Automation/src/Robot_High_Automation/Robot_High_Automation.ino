#include <POP32.h>
#include "Adafruit_TCS34725.h"

//////////////////////////////////////////////////////////////
// หุ่นยนต์ระดับสูง 4 ล้อ (POP32) — โหมด RGB 5/6/7/8
//   5/6 : เช็คสีทีละช่อง (5 = เลี้ยวขวา, 6 = เลี้ยวซ้าย)
//   7/8 : วิ่งตรงยาว       (7 = เลี้ยวขวา, 8 = เลี้ยวซ้าย)
//////////////////////////////////////////////////////////////

// แปลง RGB (0-255) เป็นสี 16 บิตแบบ RGB565 (ใช้เทียบกับค่าอ้างอิงสี)
static uint16_t rgbTo565(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t color;
  color = (uint16_t)(r & 0xF8) << 8;
  color |= (uint16_t)(g & 0xFC) << 3;
  color |= (uint16_t)(b & 0xF8) >> 3;
  return color;
}

// เซนเซอร์สี TCS34725
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// ===== ความเร็ว =====
int speed;                     // ความเร็วหลัก (ตั้งจากเมนู, ค่าเริ่มต้น 35)
int pivotSpeed;                // ความเร็วหมุนวนจัดตำแหน่ง
int slowSpeed;                 // ความเร็วช้า (ใช้ปรับตำแหน่ง)
int accSpeed;                  // ความเร็วเร่ง
int baseSpeed;                 // ความเร็วฐานปัจจุบัน (คำนวณสำหรับ PID)
int turnSpeed;                 // ความเร็วเลี้ยว
int maxSpeed;                  // ความเร็วสูงสุด (จำกัด Output ของ PID)
int leftBaseSpeed, rightBaseSpeed;         // ความเร็วฐานล้อหน้า (ซ้าย/ขวา)
int backLeftBaseSpeed, backRightBaseSpeed; // ความเร็วฐานล้อหลัง (ซ้าย/ขวา)

// ===== PID เดินตามเส้น (เซนเซอร์หน้า) =====
int lineError;                 // error ตำแหน่งเส้น (-5..100)
int prevLineError;             // error ของรอบก่อนหน้า (สำหรับ Kd)
int integral;                  // ค่า integral สะสม (สำหรับ Ki)
int kp, kd, ki;                // เกน PID
int pidLoopDelayMs;            // หน่วงเวลาของวง PID

// ===== ค่าอ้างอิงเซนเซอร์เส้น =====
int refL3, refL2, refL1, refC, refR1, refR2, refR3;   // เซนเซอร์หน้า 7 ตัว
int refBackL, refBackR;                               // เซนเซอร์หลัง 2 ตัว
int refLimitSwitch;            // ค่าอ้างอิงลิมิตสวิตช์ (ตะเกียบ/สะพาน)

// ===== ค่าเซนเซอร์เส้น (0 = เจอดำ, 1 = ขาว) =====
int sensorL3, sensorL2, sensorL1, sensorC, sensorR1, sensorR2, sensorR3;
int backL, backR;              // เซนเซอร์หลัง

// ===== นาฬิกาจับเวลา =====
long stopwatchMs, stopwatch1Ms, stopwatch2Ms, stopwatch3Ms, stopwatch4Ms;

#define No 0
#define Yes 1

// ===== โหมดการทำงาน =====
// 5 : เช็คทีละช่อง เลี้ยวขวา (กด SW_A สั้นๆ)
// 6 : เช็คทีละช่อง เลี้ยวซ้าย (กด SW_A ค้าง 1 วิ)
// 7 : วิ่งตรงยาว เลี้ยวขวา
// 8 : วิ่งตรงยาว เลี้ยวซ้าย
int robotMode = 5;

// ===== สี (RGB) =====
#define Blue 0
#define Green 1
#define Black 2
#define White 3
#define Yellow 4
#define Red 5

long refBlue, refGreen, refBlack, refWhite, refYellow, refRed;   // ค่าอ้างอิงสี
int floorColor;                // สีพื้นปัจจุบัน
int colorRank[6] = {0, 1, 2, 3, 4, 5};   // ลำดับค่าอ้างอิงสี (index: Blue..Red)
#define RGB_MODE 1             // 0 = เทียบช่วงคงที่, 1 = เทียบลำดับอัตโนมัติ

int redCount = 0, yellowCount = 0, blueCount = 0, greenCount = 0;   // จำนวนลูกบาศก์ที่ปล่อยไป
int bridgeStatus = 0;          // 0 = ปกติ, 1 = ขึ้นสะพาน, 2 = ลงสะพาน

// ===== โหมดทดสอบ (เลือกจาก knob ตอนเริ่ม) =====
int modeSelect = 0;
int knobValue = 0;

void setup() {
  speed = 35;
  accSpeed = 100;
  slowSpeed = 50;
  pivotSpeed = 42;
  baseSpeed = speed;
  turnSpeed = 100;

  updateSpeedPidParams();
  loadSensorCalibration();

  // ใช้ RGB sensor จำแนกสีพื้น (โหมด 5-8 ใช้สีพื้นตลอด)
  initColorSensor();
  delay(100);
  showColorValue();
  delay(1000);
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
  //  - กด SW_B ค้าง >= 2 วิ          = ทดสอบเซอร์โว + ตั้งค่าอ้างอิงใหม่
  //  - กด SW_A สั้นๆ                 = โหมด 5 (เช็คทีละช่อง เลี้ยวขวา)
  //  - กด SW_A ค้าง >= 1 วิ          = โหมด 6 (เช็คทีละช่อง เลี้ยวซ้าย)
  while (1) {
    knobValue = knob();
    modeSelect = map(knobValue, 0, 1023, 0, 5);
    oled.text(7, 0, "   TESTMode = %d   ", modeSelect);
    oled.show();
    if (SW_B()) {
      startStopwatch();
      beep(1);
      while (SW_B()) {
        if (stopwatchElapsed() >= 2000) {   // กดค้าง >= 2 วิ
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
      if (stopwatchElapsed() >= 1000) robotMode = 6;
      else robotMode = 5;
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
