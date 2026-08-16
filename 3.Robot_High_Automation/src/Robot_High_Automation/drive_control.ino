// drive_control.ino
// ควบคุมมอเตอร์: เดินหน้า / ถอยหลัง / หยุด ด้วยความเร็วฐานที่คำนวณไว้

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

// หยุดมอเตอร์ทุกตัว (รอ 100ms ให้มอเตอร์หยุดสนิท)
void stopMotors() {
  AO();
  delay(100);
}
