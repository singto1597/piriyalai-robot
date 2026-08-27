// Logics_SensorCalibration.ino
// ตั้งค่าอ้างอิง (calibration) ของเซนเซอร์เส้นหน้า/หลัง และค่าอ้างอิงสีทั้ง 6 สี
//  - กด OK เพื่อยืนยันแต่ละค่า
//  - ถ้าขั้นแรกกด OK ค้างเกิน CALIBRATE_SKIP_TO_SPEED_MS → ข้ามไปเมนูปรับความเร็วแทน
// (หน้าจอวาดใน Logics_Display.ino)
void calibrateSensors() {
  // ===== หน้าจอแนะนำ + เช็คว่าจะข้ามไปตั้งความเร็วหรือไม่ =====
  oledReset();
  oled.text(0, 0, "== CALIBRATION ==");
  oled.text(2, 0, "1) put on BLACK");
  oled.text(3, 0, "2) tap OK each step");
  oled.text(4, 0, "3) repeat on WHITE");
  oled.text(6, 0, "hold OK>%ds = skip", CALIBRATE_SKIP_TO_SPEED_MS / 1000);
  oled.show();
  waitOkTap();
  startStopwatch();
  beep(1);
  waitOkRelease();

  if (stopwatchElapsed() > CALIBRATE_SKIP_TO_SPEED_MS) {   // กดค้างเกิน: ข้ามไปตั้งความเร็ว
    configureSpeeds();
    return;
  }

  // ===== เก็บค่าดำของเซนเซอร์หน้า 7 ตัว =====
  readLineSensors();
  refL3 = sensorL3;
  refL2 = sensorL2;
  refL1 = sensorL1;
  refC  = sensorC;
  refR1 = sensorR1;
  refR2 = sensorR2;
  refR3 = sensorR3;
  drawFrontCalib("FRONT BLACK", false);
  waitOkTapBeep(2);

  // ===== เก็บค่าขาวของเซนเซอร์หน้า =====
  readLineSensors();
  drawFrontCalib("FRONT WHITE", true);
  waitOkTapBeep(3);

  // ===== ค่าเฉลี่ยดำ-ขาว ใช้เป็นค่าอ้างอิง =====
  refL3 = (refL3 + sensorL3) / 2;
  refL2 = (refL2 + sensorL2) / 2;
  refL1 = (refL1 + sensorL1) / 2;
  refC  = (refC  + sensorC)  / 2;
  refR1 = (refR1 + sensorR1) / 2;
  refR2 = (refR2 + sensorR2) / 2;
  refR3 = (refR3 + sensorR3) / 2;
  drawFrontCalib("FRONT AVG", false);
  waitOkTap();

  // ===== เก็บค่าดำของเซนเซอร์หลัง 2 ตัว =====
  beep(100);
  oledReset();
  oled.text(0, 0, "== BACK SENSORS ==");
  oled.text(2, 0, "put on BLACK");
  oled.text(3, 0, "tap OK");
  oled.show();
  waitOkTapBeep(0);
  readBackLineSensors();
  refBackL = backL;
  refBackR = backR;
  drawBackCalib("BACK BLACK", false);
  waitOkTapBeep(1);

  // ===== เก็บค่าขาวของเซนเซอร์หลัง =====
  readBackLineSensors();
  drawBackCalib("BACK WHITE", true);
  waitOkTapBeep(2);

  // ===== ค่าเฉลี่ยเซนเซอร์หลัง =====
  refBackL = (refBackL + backL) / 2;
  refBackR = (refBackR + backR) / 2;
  drawBackCalib("BACK AVG", false);
  waitOkTap();

  // ===== เก็บค่าอ้างอิงสีทั้ง 6 สี (จอค้างไว้บนแต่ละสี) =====
  beep(100);
  const char* calibColors[6] = {"BLUE", "GREEN", "BLACK", "WHITE", "YELLOW", "RED"};
  long* colorRefs[6] = {&refBlue, &refGreen, &refBlack, &refWhite, &refYellow, &refRed};

  for (int i = 0; i < 6; i++) {
    oledReset();
    oled.text(0, 0, "== RGB COLOR REF ==");
    oled.text(2, 0, "Place on %s", calibColors[i]);
    oled.text(3, 0, "tap OK to read");
    oled.text(6, 0, "%d/6 done", i);
    oled.show();
    waitOkTapBeep(100);
    *colorRefs[i] = readRgbColor();
    drawColorRefList();           // แสดงค่าที่เก็บไปแล้วทั้งหมด
  }
  waitOkTapBeep(100);
}
