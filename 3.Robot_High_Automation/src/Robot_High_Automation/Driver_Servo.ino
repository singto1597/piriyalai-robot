// Driver_Servo.ino
// ควบคุมเซอร์โว: SERVO_PORT_GATE_1 = ปล่อยน้ำเงิน/เขียว,
//                SERVO_PORT_GATE_2 = แดง/เหลือง, SERVO_PORT_FLAG = ธงจบงาน
// (ช่องเซอร์โว/มุม/ดีเลย์ทั้งหมดอยู่ใน config.h)

// ปล่อยลูกบาศก์สีแดง (ช่อง 2 หมุนไป SERVO_DROP_0_DEG ปล่อย แล้วกลับ SERVO_REST_DEG)
void kickRed() {
  AO();
  servo(SERVO_PORT_GATE_2, SERVO_DROP_0_DEG);
  impactPulse();
  oled.text(3, 0, "  Red   ");
  oled.show();
  delay(SERVO_KICK_HOLD_MS);
  servo(SERVO_PORT_GATE_2, SERVO_REST_DEG);
}

// ปล่อยลูกบาศก์สีเหลือง (ช่อง 2 หมุนไป SERVO_DROP_180_DEG ปล่อย แล้วกลับ SERVO_REST_DEG)
void kickYellow() {
  AO();
  servo(SERVO_PORT_GATE_2, SERVO_DROP_180_DEG);
  impactPulse();
  oled.text(3, 0, "  Yellow   ");
  oled.show();
  delay(SERVO_KICK_HOLD_MS);
  servo(SERVO_PORT_GATE_2, SERVO_REST_DEG);
}

// ปล่อยลูกบาศก์สีน้ำเงิน (ช่อง 1 หมุนไป SERVO_DROP_0_DEG ปล่อย แล้วกลับ SERVO_REST_DEG)
void kickBlue() {
  AO();
  servo(SERVO_PORT_GATE_1, SERVO_DROP_0_DEG);
  impactPulse();
  oled.text(3, 0, "  Blue   ");
  oled.show();
  delay(SERVO_KICK_HOLD_MS);
  servo(SERVO_PORT_GATE_1, SERVO_REST_DEG);
}

// ปล่อยลูกบาศก์สีเขียว (ช่อง 1 หมุนไป SERVO_DROP_180_DEG ปล่อย แล้วกลับ SERVO_REST_DEG)
void kickGreen() {
  AO();
  servo(SERVO_PORT_GATE_1, SERVO_DROP_180_DEG);
  impactPulse();
  oled.text(3, 0, "  Green   ");
  oled.show();
  delay(SERVO_KICK_HOLD_MS);
  servo(SERVO_PORT_GATE_1, SERVO_REST_DEG);
}

// ยกธงขึ้น (สัญญาณจบการทำงาน)
void raiseFlag() {
  stopMotors();
  servo(SERVO_PORT_FLAG, SERVO_FLAG_UP_DEG);
}

// ลดธงลง
void lowerFlag() {
  stopMotors();
  servo(SERVO_PORT_FLAG, SERVO_FLAG_DOWN_DEG);
}

// กระแทกเบาๆ (เดินหน้าถอยหลังสั้นๆ) เพื่อให้ลูกบาศก์หลุดจากตัวปล่อย
void impactPulse() {
  delay(IMPACT_PAUSE_MS);
  backwardFor(speed, IMPACT_BACKUP_MS);
  stopMotors();
  forwardFor(speed, IMPACT_FORWARD_MS);
  stopMotors();
}

// ทดสอบชุดเซอร์โวทั้งหมด (ยกธง → ปล่อยครบ 4 สี → ลดธง)
void testServo() {
  raiseFlag();
  kickRed();
  kickYellow();
  kickBlue();
  kickGreen();
  lowerFlag();
}
