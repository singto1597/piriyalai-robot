// config_speed_menu.ino
// เมนูปรับความเร็วหลัก (Speed) และความเร็วเร่ง (ACCSpeed) ผ่านปุ่ม OK
//  - กดสั้น        : เพิ่มความเร็วทีละ 5 (เกิน 100 วนกลับไป 60)
//  - กดค้าง >= 2 วินาที : ยืนยันค่าและไปขั้นถัดไป

void configureSpeeds() {
  int okStatus;

  // ===== ตั้ง Speed =====
  oled.clear();
  oled.text(0, 0, "    Set Speed   ");
  oled.text(1, 0, "Speed = %d", speed);
  oled.show();

  okStatus = No;
  while (okStatus == No) {
    if (isOkPressed()) {
      startStopwatch();
      beep(0);
      waitOkRelease();
      if (stopwatchElapsed() >= 2000) {   // กดค้าง: ยืนยันค่า
        beep(1);
        okStatus = Yes;
      }
      else {                              // กดสั้น: เปลี่ยนค่า
        okStatus = No;
        speed += 5;
        if (speed > 100) speed = 60;
        oled.text(1, 0, "Speed = %d  ", speed);
        oled.show();
      }
    }
  }

  // ===== ตั้ง ACCSpeed =====
  oled.text(2, 0, "ACCSpeed = %d", accSpeed);
  oled.show();

  okStatus = No;
  while (okStatus == No) {
    if (isOkPressed()) {
      startStopwatch();
      beep(2);
      waitOkRelease();
      if (stopwatchElapsed() >= 2000) {   // กดค้าง: ยืนยันค่า
        beep(100);
        okStatus = Yes;
      }
      else {                              // กดสั้น: เปลี่ยนค่า
        okStatus = No;
        accSpeed += 5;
        if (accSpeed > 100) accSpeed = 60;
        oled.text(2, 0, "ACCSpeed = %d  ", accSpeed);
        oled.show();
      }
    }
  }

  // ใช้ความเร็วที่ตั้งใหม่ คำนวณ PID ใหม่ แล้วแสดงข้อความให้กด OK เริ่มงาน
  baseSpeed = speed;
  turnSpeed = baseSpeed;
  updateSpeedPidParams();
  oled.text(3, 0, "Press OK to Start");
  oled.show();
}
