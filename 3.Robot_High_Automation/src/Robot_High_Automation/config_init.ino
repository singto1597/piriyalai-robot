// config_init.ino
// ตั้งค่าค่าอ้างอิง (threshold) ของเซนเซอร์เส้น/สี และคำนวณเกน PID ตามความเร็วที่เลือก

// โหลดค่าอ้างอิงของเซนเซอร์เส้นหน้า 7 ตัว, เซนเซอร์หลัง 2 ตัว,
// ค่าอ้างอิงสี 6 สี และค่าลิมิตสวิตช์ (ตะเกียบ/สะพาน)
void loadSensorCalibration() {
  refL3 = 3134;
  refL2 = 2930;
  refL1 = 2881;
  refC  = 3144;
  refR1 = 2754;
  refR2 = 3018;
  refR3 = 2636;
  refBackL = 2500;
  refBackR = 2500;

  refBlue   = 10833;
  refGreen  = 13288;
  refBlack  = 21193;
  refWhite  = 19145;
  refYellow = 27396;
  refRed    = 45413;

  refLimitSwitch = 4000;
}

// คำนวณความเร็วฐานของล้อแต่ละข้าง + เกน PID หน้า ตามช่วงของ baseSpeed
void updateSpeedPidParams() {
  maxSpeed = 100;
  ki = 0;
  lineError = 0;
  prevLineError = 0;

  if (baseSpeed <= 50) {
    leftBaseSpeed  = baseSpeed - 6;
    rightBaseSpeed = baseSpeed;
    backLeftBaseSpeed  = baseSpeed - 5;
    backRightBaseSpeed = baseSpeed;
    kp = 20; kd = 25; pidLoopDelayMs = 10;
  }
  else if (baseSpeed <= 60) {
    leftBaseSpeed  = baseSpeed - 6;
    rightBaseSpeed = baseSpeed;
    backLeftBaseSpeed  = baseSpeed - 3;
    backRightBaseSpeed = baseSpeed;
    kp = 18; kd = 30; pidLoopDelayMs = 10;
  }
  else if (baseSpeed <= 70) {
    leftBaseSpeed  = baseSpeed;
    rightBaseSpeed = baseSpeed;
    backLeftBaseSpeed  = baseSpeed;
    backRightBaseSpeed = baseSpeed;
    kp = 21; kd = 30; pidLoopDelayMs = 10;
  }
  else if (baseSpeed <= 80) {
    leftBaseSpeed  = baseSpeed - 6;
    rightBaseSpeed = baseSpeed;
    backLeftBaseSpeed  = baseSpeed;
    backRightBaseSpeed = baseSpeed;
    kp = 24; kd = 30; pidLoopDelayMs = 10;
  }
  else if (baseSpeed <= 90) {
    leftBaseSpeed  = baseSpeed - 6;
    rightBaseSpeed = baseSpeed;
    backLeftBaseSpeed  = baseSpeed;
    backRightBaseSpeed = baseSpeed;
    kp = 27; kd = 35; pidLoopDelayMs = 10;
  }
  else {
    leftBaseSpeed  = baseSpeed - 6;
    rightBaseSpeed = baseSpeed;
    backLeftBaseSpeed  = baseSpeed;
    backRightBaseSpeed = baseSpeed;
    kp = 30; kd = 50; pidLoopDelayMs = 10;
  }
}
