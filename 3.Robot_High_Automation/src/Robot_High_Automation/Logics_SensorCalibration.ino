// Logics_SensorCalibration.ino
// ตั้งค่าอ้างอิง (calibration) ของเซนเซอร์เส้นหน้า/หลัง และค่าอ้างอิงสีทั้ง 6 สี
//  - กด OK เพื่อยืนยันแต่ละค่า
//  - ถ้าครั้งแรกกด OK ค้างเกิน CALIBRATE_SKIP_TO_SPEED_MS → ข้ามไปเมนูปรับความเร็วแทน
void calibrateSensors() {
  oled.clear();
  oled.textSize(1);
  oled.text(0, 1, "Black");
  oled.show();
  waitOkTap();
  startStopwatch();
  beep(1);
  waitOkRelease();

  if (stopwatchElapsed() > CALIBRATE_SKIP_TO_SPEED_MS) {   // กดค้างเกิน: ข้ามไปตั้งความเร็ว
    configureSpeeds();
  }
  else {
    // ===== เก็บค่าดำของเซนเซอร์หน้า 7 ตัว =====
    readLineSensors();
    refL3 = sensorL3;
    refL2 = sensorL2;
    refL1 = sensorL1;
    refC  = sensorC;
    refR1 = sensorR1;
    refR2 = sensorR2;
    refR3 = sensorR3;
    oled.text(1, 0, "L3=%d", sensorL3);
    oled.text(2, 0, "L2=%d", sensorL2);
    oled.text(3, 0, "L1=%d", sensorL1);
    oled.text(4, 0, "C =%d", sensorC);
    oled.text(5, 0, "R1=%d", sensorR1);
    oled.text(6, 0, "R2=%d", sensorR2);
    oled.text(7, 0, "R3=%d", sensorR3);
    oled.text(0, 9, "White");
    oled.show();
    waitOkTapBeep(2);

    // ===== เก็บค่าขาวของเซนเซอร์หน้า =====
    readLineSensors();
    oled.text(1, 8, "L3=%d", sensorL3);
    oled.text(2, 8, "L2=%d", sensorL2);
    oled.text(3, 8, "L1=%d", sensorL1);
    oled.text(4, 8, "C =%d", sensorC);
    oled.text(5, 8, "R1=%d", sensorR1);
    oled.text(6, 8, "R2=%d", sensorR2);
    oled.text(7, 8, "R3=%d", sensorR3);
    oled.show();
    waitOkTapBeep(3);

    // ===== ค่าเฉลี่ยดำ-ขาว ใช้เป็นค่าอ้างอิง =====
    oled.text(0, 14, "Average");
    refL3 = (refL3 + sensorL3) / 2;
    refL2 = (refL2 + sensorL2) / 2;
    refL1 = (refL1 + sensorL1) / 2;
    refC  = (refC  + sensorC)  / 2;
    refR1 = (refR1 + sensorR1) / 2;
    refR2 = (refR2 + sensorR2) / 2;
    refR3 = (refR3 + sensorR3) / 2;
    oled.text(1, 17, "%d", refL3);
    oled.text(2, 17, "%d", refL2);
    oled.text(3, 17, "%d", refL1);
    oled.text(4, 17, "%d", refC);
    oled.text(5, 17, "%d", refR1);
    oled.text(6, 17, "%d", refR2);
    oled.text(7, 17, "%d", refR3);
    oled.show();
    waitOkTap();

    // ===== เก็บค่าดำของเซนเซอร์หลัง 2 ตัว =====
    beep(100);
    oled.clear();
    oled.text(0, 0, " Black");
    oled.show();
    waitOkTapBeep(0);
    readBackLineSensors();
    refBackL = backL;
    refBackR = backR;
    oled.text(1, 0, "BL=%d", backL);
    oled.text(2, 0, "BR=%d", backR);
    oled.text(0, 9, "White");
    oled.show();
    waitOkTapBeep(1);

    // ===== เก็บค่าขาวของเซนเซอร์หลัง =====
    readBackLineSensors();
    oled.text(1, 8, "BL=%d", backL);
    oled.text(2, 8, "BR=%d", backR);
    oled.text(0, 14, "Average");
    oled.show();
    waitOkTapBeep(2);

    // ===== ค่าเฉลี่ยเซนเซอร์หลัง =====
    refBackL = (refBackL + backL) / 2;
    refBackR = (refBackR + backR) / 2;
    oled.text(1, 17, "%d", refBackL);
    oled.text(2, 17, "%d", refBackR);
    oled.show();
    waitOkTap();

    // ===== เก็บค่าอ้างอิงสีทั้ง 6 สี (จอดังกล่าวไว้บนแต่ละสี) =====
    beep(100);
    oled.clear();
    oled.text(1, 0, " Blue");
    oled.show();
    waitOkTapBeep(100);
    refBlue = readRgbColor();
    oled.text(1, 0, " Blue   = %l", refBlue);
    oled.text(2, 0, " Green ");
    oled.show();
    waitOkTapBeep(100);
    refGreen = readRgbColor();
    oled.text(2, 0, " Green  = %l", refGreen);
    oled.text(3, 0, " Black  ");
    oled.show();
    waitOkTapBeep(100);
    refBlack = readRgbColor();
    oled.text(3, 0, " Black  = %l", refBlack);
    oled.text(4, 0, " White ");
    oled.show();
    waitOkTapBeep(100);
    refWhite = readRgbColor();
    oled.text(4, 0, " White  = %l", refWhite);
    oled.text(5, 0, " Yellow ");
    oled.show();
    waitOkTapBeep(100);
    refYellow = readRgbColor();
    oled.text(5, 0, " Yellow = %l", refYellow);
    oled.text(6, 0, " Red ");
    oled.show();
    waitOkTapBeep(100);
    refRed = readRgbColor();
    oled.text(6, 0, " Red    = %l", refRed);
    oled.text(8, 0, " OK To Start ");
    oled.show();
    waitOkTapBeep(100);
  }
}
