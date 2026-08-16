// turn_control.ino
// ควบคุมการหมุนของหุ่นยนต์ (หมุนรอบตัวเองด้วยความเร็วคงที่ turnSpeed)
// ระยะเวลาหมุนคำนวณจากค่าคงที่ 24400/turnSpeed และ 36000/turnSpeed (ปรับจูนจากสนามจริง)

// เลี้ยวซ้าย 90 องศา
void turnLeft() {
  spinLeft(turnSpeed, 24400 / turnSpeed);
}

// เลี้ยวขวา 90 องศา
void turnRight() {
  spinRight(turnSpeed, 24400 / turnSpeed);
}

// กลับตัวทางซ้าย 180 องศา
void uTurnLeft() {
  spinLeft(turnSpeed, 36000 / turnSpeed);
}

// กลับตัวทางขวา 180 องศา
void uTurnRight() {
  spinRight(turnSpeed, 36000 / turnSpeed);
}

// หมุนซ้ายรอบตัวเอง ด้วยความเร็ว-เวลาที่กำหนด
void spinLeft(int spinSpeed, int timeMs) {
  stopMotors();
  SL(spinSpeed);
  delay(timeMs);
  stopMotors();
}

// หมุนขวารอบตัวเอง ด้วยความเร็ว-เวลาที่กำหนด
void spinRight(int spinSpeed, int timeMs) {
  stopMotors();
  SR(spinSpeed);
  delay(timeMs);
  stopMotors();
}
