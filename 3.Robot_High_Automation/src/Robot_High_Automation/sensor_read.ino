// sensor_read.ino
// อ่านค่าดิบ (analog) ของเซนเซอร์เส้นทั้ง 9 ตัว

// อ่านเซนเซอร์เส้นหน้า 7 ตัว (sensorL3..sensorR3)
void readLineSensors() {
  sensorL3 = analog(0);
  sensorL2 = analog(1);
  sensorL1 = analog(2);
  sensorC  = analog(3);
  sensorR1 = analog(4);
  sensorR2 = analog(5);
  sensorR3 = analog(6);
}

// อ่านเซนเซอร์เส้นหลัง 2 ตัว (ใช้ตอนถอยหลัง/จัดตำแหน่ง)
void readBackLineSensors() {
  backL = analog(7);
  backR = analog(8);
}
