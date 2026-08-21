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
