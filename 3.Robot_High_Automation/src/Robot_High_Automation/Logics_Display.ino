// Logics_Display.ino
// หน้าจอ OLED ทั้งหมดของหุ่นยนต์ — รวมฟังก์ชันวาดหน้าจอไว้ที่เดียว (แยกการแสดงผลออกจากลอจิก)
// จอ 128x64: ฟอนต์ขนาด 1 = 8 แถว (0-7) x 21 ตัวอักษร, ขนาด 2 = 4 แถว (0-3) x ~10 ตัวอักษร
// ⚠️ ฟอนต์ OLED เป็น ASCII เท่านั้น — ห้ามใส่ตัวอักษรไทย/ยูนิโค้ดลงหน้าจอ (มีได้แค่ในคอมเมนต์)
// (ชื่อโหมด/สี อ่านจาก global robotMode / redCount..greenCount ใน main)

// ---- ตัวช่วย ----

// ชื่อโหมด (5=SCAN ขวา, 6=SCAN ซ้าย, 7=LANE ขวา, 8=LANE ซ้าย)
const char* modeName(int mode) {
  if (mode == 5) return "SCAN-R";
  if (mode == 6) return "SCAN-L";
  if (mode == 7) return "LANE-R";
  if (mode == 8) return "LANE-L";
  return "????";
}

// ชื่อสี (ตามค่าคงที่ Blue..Red ใน config.h)
const char* colorName(int color) {
  if (color == Blue)   return "BLUE";
  if (color == Green)  return "GREEN";
  if (color == Black)  return "BLACK";
  if (color == White)  return "WHITE";
  if (color == Yellow) return "YELLOW";
  if (color == Red)    return "RED";
  return "?";
}

// จำนวนลูกบาศก์ที่วางไปแล้วของแต่ละสี (ใช้แสดงผลบนหน้าจอ)
int countFor(int color) {
  if (color == Red)    return redCount;
  if (color == Yellow) return yellowCount;
  if (color == Blue)   return blueCount;
  if (color == Green)  return greenCount;
  return 0;
}

// รีเซ็ตจอ + ค่าเริ่มต้น (โหมดจอปกติ + หรี่แสง + ฟอนต์ขนาด 1)
void oledReset() {
  oled.clear();
  oled.mode(0);
  oled.dim(true);
  oled.textSize(1);
}

// วาดเส้นคั่นเต็มบรรทัดที่แถว row
void drawDivider(int row) {
  oled.text(row, 0, "====================");
}

// ---- หน้าจอหลัก ๆ ----

// หน้าจอต้อนรับ (ตอนเปิดเครื่อง ก่อนเลือกโหมด) — แสดงโหมดทั้ง 4 + ความเร็ว
void drawWelcomeScreen() {
  oledReset();
  oled.text(0, 0, " PHIRIYALAI  ROBOT ");
  oled.text(1, 0, " High 4W  POP32 V2 ");
  drawDivider(2);
  oled.text(3, 0, " Mode 5: SCAN-R");
  oled.text(4, 0, " Mode 6: SCAN-L");
  oled.text(5, 0, " Mode 7: LANE-R");
  oled.text(6, 0, " Mode 8: LANE-L");
  oled.text(7, 0, " Spd=%d ACC=%d", speed, accSpeed);
  oled.show();
}

// หน้าจอเลือกโหมด (วาดใหม่ทุก loop) — แสดงวิธีกดปุ่ม + knob test mode
void drawStartScreen() {
  oledReset();
  oled.text(0, 0, "== SELECT MODE ==");
  oled.text(1, 0, "A tap=5  hold=6");
  oled.text(2, 0, "B tap=7  hold=8");
  oled.text(3, 0, "OK tap=TEST %d", modeSelect);
  oled.text(4, 0, "OK hold=CALIB");
  drawDivider(5);
  oled.text(6, 0, "Default M%d %s", robotMode, modeName(robotMode));
  oled.text(7, 0, "Spd=%d ACC=%d", speed, accSpeed);
  oled.show();
}

// หน้าจอเริ่มวิ่ง (ฟอนต์ใหญ่ 2x)
void drawStartingScreen() {
  oledReset();
  oled.textSize(2);
  oled.text(0, 0, "STARTING!");
  oled.text(1, 0, "MODE=%d", robotMode);
  oled.text(2, 0, "%s", modeName(robotMode));
  oled.text(3, 0, "GO !!");
  oled.show();
}

// หน้าจอสถานะระหว่างวิ่ง — สีพื้น + จำนวนที่วางแล้ว + ความเร็ว (เรียกทุกครั้งที่เช็คสี)
void drawRunStatus(int floor) {
  oledReset();
  oled.text(0, 0, "== M%d %s ==", robotMode, modeName(robotMode));
  oled.text(1, 0, "Floor : %s", colorName(floor));
  oled.text(2, 0, "Placed R:%d Y:%d", redCount, yellowCount);
  oled.text(3, 0, "       B:%d G:%d", blueCount, greenCount);
  oled.text(4, 0, "Spd=%d Pv=%d", speed, pivotSpeed);
  drawDivider(5);
  oled.text(7, 0, "RUNNING...");
  oled.show();
}

// หน้าจอปล่อยลูกบาศก์ (เรียกจาก kickRed/Yellow/Blue/Green)
void drawKickScreen(int color) {
  oledReset();
  oled.text(0, 0, "=== KICK BLOCK ===");
  oled.text(1, 0, "Color : %s", colorName(color));
  oled.text(2, 0, "Gate  : CH%d", (color == Red || color == Yellow) ? 2 : 1);
  oled.text(3, 0, "Count : %d", countFor(color));
  drawDivider(4);
  oled.text(6, 0, "Dropping block...");
  oled.show();
}

// หน้าจอเมนูปรับความเร็ว (Speed / ACCSpeed)
void drawSpeedMenuScreen(const char* label, int value) {
  oledReset();
  oled.text(0, 0, "== SET SPEED ==");
  oled.text(1, 0, "tap  = +%d", SPEED_STEP);
  oled.text(2, 0, "hold = confirm");
  drawDivider(3);
  oled.text(4, 0, "%s : %d", label, value);
  oled.show();
}

// หน้าจอเสร็จสิ้นการปรับความเร็ว (พร้อมเริ่มงาน)
void drawSpeedReadyScreen() {
  oledReset();
  oled.text(2, 0, "== READY ==");
  oled.text(4, 0, "Spd=%d ACC=%d", speed, accSpeed);
  oled.text(6, 0, "Press OK to start");
  oled.show();
}

// ---- หน้าจอ calibrate ----

// หน้าจอเซนเซอร์หน้า 7 ตัว (1 ค่า/แถว)
// useWhite=true = แสดงค่า white (sensor*), false = แสดงค่า black/avg (ref*)
void drawFrontCalib(const char* title, bool useWhite) {
  oledReset();
  oled.text(0, 0, "== %s ==", title);
  oled.text(1, 0, "L3 %d", useWhite ? sensorL3 : refL3);
  oled.text(2, 0, "L2 %d", useWhite ? sensorL2 : refL2);
  oled.text(3, 0, "L1 %d", useWhite ? sensorL1 : refL1);
  oled.text(4, 0, "C  %d", useWhite ? sensorC  : refC);
  oled.text(5, 0, "R1 %d", useWhite ? sensorR1 : refR1);
  oled.text(6, 0, "R2 %d", useWhite ? sensorR2 : refR2);
  oled.text(7, 0, "R3 %d", useWhite ? sensorR3 : refR3);
  oled.show();
}

// หน้าจอเซนเซอร์หลัง 2 ตัว (ใช้ตอนถอย/จัดตำแหน่ง)
void drawBackCalib(const char* title, bool useWhite) {
  oledReset();
  oled.text(0, 0, "== %s ==", title);
  oled.text(2, 0, "Left  %d", useWhite ? backL : refBackL);
  oled.text(3, 0, "Right %d", useWhite ? backR : refBackR);
  oled.show();
}

// หน้าจอค่าอ้างอิงสีทั้งหมด (แสดงความคืบหน้าระหว่าง calibrate สี)
void drawColorRefList() {
  oledReset();
  oled.text(0, 0, "== COLOR REFS ==");
  oled.text(1, 0, "Blue   %l", refBlue);
  oled.text(2, 0, "Green  %l", refGreen);
  oled.text(3, 0, "Black  %l", refBlack);
  oled.text(4, 0, "White  %l", refWhite);
  oled.text(5, 0, "Yellow %l", refYellow);
  oled.text(6, 0, "Red    %l", refRed);
  oled.text(7, 0, "tap OK to continue");
  oled.show();
}

// หน้าจอจบงาน — เวลารวม + โหมด + จำนวนลูกบาศก์ทั้งหมด
void drawFinishScreen(long runningTime) {
  oledReset();
  oled.text(0, 0, "== RUN FINISHED ==");
  oled.text(1, 0, "Time  : %l.%l s", runningTime / 1000, runningTime % 1000);
  oled.text(2, 0, "Mode  : %d %s", robotMode, modeName(robotMode));
  oled.text(3, 0, "Placed R:%d Y:%d", redCount, yellowCount);
  oled.text(4, 0, "       B:%d G:%d", blueCount, greenCount);
  drawDivider(5);
  oled.text(7, 0, "Power off to stop");
  oled.show();
}
