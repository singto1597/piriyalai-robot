// Driver_Motor.ino
// ควบคุมมอเตอร์: เดินหน้า / ถอยหลัง / หยุด / หมุนวน ด้วยความเร็วฐานที่คำนวณไว้
// (เกน PID/ความเร็วฐาน มาจาก config.h ผ่าน updateSpeedPidParams)

// เดินหน้าตรงด้วยความเร็วฐานล้อหน้า
void driveForward() {
  FD2(leftBaseSpeed, rightBaseSpeed);
}

// เดินหน้าด้วยความเร็วที่กำหนดเป็นระยะเวลาที่กำหนด แล้วคืนความเร็วเดิม
void forwardFor(int motorSpeed, int timeMs) {
  baseSpeed = motorSpeed;
  updateSpeedPidParams();
  driveForward();
  delay(timeMs);
  baseSpeed = speed;
  updateSpeedPidParams();
}

// ถอยหลังตรงด้วยความเร็วฐานล้อหลัง
void driveBackward() {
  BK2(backLeftBaseSpeed, backRightBaseSpeed);
}

// ถอยหลังด้วยความเร็วที่กำหนดเป็นระยะเวลาที่กำหนด แล้วคืนความเร็วเดิม
void backwardFor(int motorSpeed, int timeMs) {
  baseSpeed = motorSpeed;
  updateSpeedPidParams();
  driveBackward();
  delay(timeMs);
  baseSpeed = speed;
  updateSpeedPidParams();
}

// หยุดมอเตอร์ทุกตัว (รอ STOP_SETTLE_MS ให้มอเตอร์หยุดสนิท)
void stopMotors() {
  AO();
  delay(STOP_SETTLE_MS);
}

// ถอยหลังด้วย PID เซนเซอร์หลัง: ถอยจนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ
// ระหว่างถอย ปรับความเร็วล้อซ้าย/ขวาให้หุ่นถอยตรง (ฝั่งที่เห็นเส้นก่อน = หุ่นเอียง → หน่วงล้อฝั่งนั้น)
// คืนค่า true = เจอเส้นดำทั้ง 2 ข้าง, false = ถอยครบ timeoutMs ยังไม่เจอ (กันค้าง)
bool reverseWithBackPid(int motorSpeed, int stepMs, int timeoutMs) {
  baseSpeed = motorSpeed;
  updateSpeedPidParams();
  startStopwatch();
  BK2(backLeftBaseSpeed, backRightBaseSpeed);

  while (1) {
    updateBackLineBinary();
    if ((backL == 0) && (backR == 0)) break;          // ทั้ง 2 ข้างเจอเส้นดำ → พอ
    if (stopwatchElapsed() > timeoutMs) {              // กันค้าง: ถอยนานเกินยังไม่เจอเส้น
      stopMotors();
      return false;
    }
    // PID เซนเซอร์หลัง: ปรับล้อซ้าย/ขวาให้ถอยตรง (ความต่างใน config.h)
    int bl = backLeftBaseSpeed;
    int br = backRightBaseSpeed;
    if (backL == 0)      { bl -= BACK_PID_ADJUST; br += BACK_PID_ADJUST; }
    else if (backR == 0) { br -= BACK_PID_ADJUST; bl += BACK_PID_ADJUST; }
    BK2(bl, br);
    delay(stepMs);
  }
  stopMotors();
  return true;
}

// ถอยหลังเป็นเวลา timeMs ด้วย PID เซนเซอร์หลัง (ปรับให้ถอยตรง)
// ใช้ถอยระยะสั้นๆ เช่น กันเบรกไม่ทัน (กลับเข้าช่อง) หรือถอยก่อนปล่อยแดง/เหลือง
void reverseForWithBackPid(int motorSpeed, int timeMs) {
  baseSpeed = motorSpeed;
  updateSpeedPidParams();
  startStopwatch();
  BK2(backLeftBaseSpeed, backRightBaseSpeed);

  while (stopwatchElapsed() < timeMs) {
    updateBackLineBinary();
    int bl = backLeftBaseSpeed;
    int br = backRightBaseSpeed;
    if (backL == 0)      { bl -= BACK_PID_ADJUST; br += BACK_PID_ADJUST; }
    else if (backR == 0) { br -= BACK_PID_ADJUST; bl += BACK_PID_ADJUST; }
    BK2(bl, br);
    delay(pidLoopDelayMs);
  }
  stopMotors();
}

// หมุนวนรอบตัวเองไปทางขวา (ล้อซ้ายถอย / ล้อขวาเดินหน้า) ด้วยความเร็ว spinSpeed
void pivotRight(int spinSpeed) {
  AO();
  motor(MOTOR_CH_LEFT_1, -spinSpeed);  motor(MOTOR_CH_LEFT_2, -spinSpeed);
  motor(MOTOR_CH_RIGHT_1, spinSpeed);  motor(MOTOR_CH_RIGHT_2, spinSpeed);
}

// หมุนวนรอบตัวเองไปทางซ้าย (ล้อซ้ายเดินหน้า / ล้อขวาถอย) ด้วยความเร็ว spinSpeed
void pivotLeft(int spinSpeed) {
  AO();
  motor(MOTOR_CH_LEFT_1, spinSpeed);   motor(MOTOR_CH_LEFT_2, spinSpeed);
  motor(MOTOR_CH_RIGHT_1, -spinSpeed); motor(MOTOR_CH_RIGHT_2, -spinSpeed);
}
