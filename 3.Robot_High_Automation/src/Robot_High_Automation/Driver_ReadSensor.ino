// Driver_ReadSensor.ino
// อ่านค่าดิบ (analog) ของเซนเซอร์เส้นทั้ง 9 ตัว + ลิมิตสวิตช์แบบดิจิทัล (ขาเชื่อมต่ออยู่ใน config.h)
// หมายเหตุ: PIN_BACK_LEFT (analog 7) แยกขากับ PIN_LIMIT_SWITCH (GPIO 22 — อ่านแบบดิจิทัล) แล้ว

// อ่านเซนเซอร์เส้นหน้า 7 ตัว (sensorL3..sensorR3)
void readLineSensors() {
  sensorL3 = analog(PIN_LINE_L3);
  sensorL2 = analog(PIN_LINE_L2);
  sensorL1 = analog(PIN_LINE_L1);
  sensorC  = analog(PIN_LINE_C);
  sensorR1 = analog(PIN_LINE_R1);
  sensorR2 = analog(PIN_LINE_R2);
  sensorR3 = analog(PIN_LINE_R3);
}

// อ่านเซนเซอร์เส้นหลัง 2 ตัว (ใช้ตอนถอยหลัง/จัดตำแหน่ง)
void readBackLineSensors() {
  backL = analog(PIN_BACK_LEFT);
  backR = analog(PIN_BACK_RIGHT);
}

// ลิมิตสวิตช์ (ตะเกียบ/สะพาน) — อ่านแบบดิจิทัล (digitalRead)
// คืนค่า true = สวิตช์ถูกกด (เจอสิ่งกีดขวาง/สะพาน) — ระดับที่ถือว่ากด ดูที่ LIMIT_SWITCH_PRESSED_LEVEL ใน config.h
bool limitSwitchPressed() {
  return (digitalRead(PIN_LIMIT_SWITCH) == LIMIT_SWITCH_PRESSED_LEVEL);
}
