// Driver_Turn.ino
// ควบคุมการหมุนของหุ่นยนต์ (หมุนรอบตัวเองด้วยความเร็วคงที่ turnSpeed)
// เวลาหมุนคำนวณจาก TURN_90_MS_FACTOR/turnSpeed และ TURN_180_MS_FACTOR/turnSpeed
// (ค่า factor ปรับจูนได้ใน config.h ตามสนามจริง)

// เลี้ยวซ้าย 90 องศา
void turnLeft() {
  spinLeft(turnSpeed, TURN_90_MS_FACTOR / turnSpeed);
}

// เลี้ยวขวา 90 องศา
void turnRight() {
  spinRight(turnSpeed, TURN_90_MS_FACTOR / turnSpeed);
}

// กลับตัวทางซ้าย 180 องศา
void uTurnLeft() {
  spinLeft(turnSpeed, TURN_180_MS_FACTOR / turnSpeed);
}

// กลับตัวทางขวา 180 องศา
void uTurnRight() {
  spinRight(turnSpeed, TURN_180_MS_FACTOR / turnSpeed);
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
