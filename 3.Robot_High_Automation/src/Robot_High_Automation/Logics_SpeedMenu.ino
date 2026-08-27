// Logics_SpeedMenu.ino
// เมนูปรับความเร็วหลัก (Speed) และความเร็วเร่ง (ACCSpeed) ผ่านปุ่ม OK
//  - กดสั้น        : เพิ่มความเร็วทีละ SPEED_STEP (เกิน SPEED_MAX วนกลับไป SPEED_MIN)
//  - กดค้าง >= SPEED_MENU_HOLD_CONFIRM_MS : ยืนยันค่าและไปขั้นถัดไป
// (ค่าปุ่ม/ความเร็ว อยู่ใน config.h, หน้าจอวาดใน Logics_Display.ino)

// ตั้งค่าความเร็วตัวเดียวผ่านปุ่ม OK (ใช้ร่วมกันระหว่าง Speed และ ACCSpeed)
//  - กดสั้น = +SPEED_STEP, กดค้าง = ยืนยันค่า
void configureSpeedValue(const char* label, int &speedVar, int pressTone, int confirmTone) {
  int okStatus = No;
  while (okStatus == No) {
    if (isOkPressed()) {
      startStopwatch();
      beep(pressTone);
      waitOkRelease();
      if (stopwatchElapsed() >= SPEED_MENU_HOLD_CONFIRM_MS) {   // กดค้าง: ยืนยันค่า
        beep(confirmTone);
        okStatus = Yes;
      }
      else {                                                    // กดสั้น: เปลี่ยนค่า
        speedVar += SPEED_STEP;
        if (speedVar > SPEED_MAX) speedVar = SPEED_MIN;
        drawSpeedMenuScreen(label, speedVar);
      }
    }
  }
}

void configureSpeeds() {
  // ===== ตั้ง Speed =====
  drawSpeedMenuScreen("Speed", speed);
  configureSpeedValue("Speed", speed, 0, 1);

  // ===== ตั้ง ACCSpeed =====
  drawSpeedMenuScreen("ACCSpeed", accSpeed);
  configureSpeedValue("ACCSpeed", accSpeed, 2, 100);

  // ใช้ความเร็วที่ตั้งใหม่ คำนวณ PID ใหม่ แล้วแสดงข้อความให้กด OK เริ่มงาน
  baseSpeed = speed;
  turnSpeed = baseSpeed;
  updateSpeedPidParams();
  drawSpeedReadyScreen();
}
