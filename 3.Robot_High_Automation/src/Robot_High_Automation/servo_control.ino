// servo_control.ino
// ควบคุมเซอร์โว: ช่อง 1 = ปล่อยลูกบาศก์น้ำเงิน/เขียว, ช่อง 2 = แดง/เหลือง, ช่อง 5 = ธงจบงาน

// ปล่อยลูกบาศก์สีแดง (เซอร์โวช่อง 2 หมุนไป 0° ปล่อย แล้วกลับมา 90°)
void kickRed() {
  AO();
  servo(2, 0);
  impactPulse();
  oled.text(3, 0, "  Red   ");
  oled.show();
  delay(300);
  servo(2, 90);
}

// ปล่อยลูกบาศก์สีเหลือง (เซอร์โวช่อง 2 หมุนไป 180° ปล่อย แล้วกลับมา 90°)
void kickYellow() {
  AO();
  servo(2, 180);
  impactPulse();
  oled.text(3, 0, "  Yellow   ");
  oled.show();
  delay(300);
  servo(2, 90);
}

// ปล่อยลูกบาศก์สีน้ำเงิน (เซอร์โวช่อง 1 หมุนไป 0° ปล่อย แล้วกลับมา 90°)
void kickBlue() {
  AO();
  servo(1, 0);
  impactPulse();
  oled.text(3, 0, "  Blue   ");
  oled.show();
  delay(300);
  servo(1, 90);
}

// ปล่อยลูกบาศก์สีเขียว (เซอร์โวช่อง 1 หมุนไป 180° ปล่อย แล้วกลับมา 90°)
void kickGreen() {
  AO();
  servo(1, 180);
  impactPulse();
  oled.text(3, 0, "  Green   ");
  oled.show();
  delay(300);
  servo(1, 90);
}

// ยกธงขึ้น (สัญญาณจบการทำงาน)
void raiseFlag() {
  stopMotors();
  servo(5, 20);
}

// ลดธงลง
void lowerFlag() {
  stopMotors();
  servo(5, 130);
}

// กระแทกเบาๆ (เดินหน้าถอยหลังสั้นๆ) เพื่อให้ลูกบาศก์หลุดจากตัวปล่อย
void impactPulse() {
  delay(100);
  backwardFor(speed, 50);
  stopMotors();
  forwardFor(speed, 50);
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
