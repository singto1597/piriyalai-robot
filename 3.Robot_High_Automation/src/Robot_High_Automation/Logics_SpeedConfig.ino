// Logics_SpeedConfig.ino
// คำนวณความเร็วฐานของล้อแต่ละข้าง + เกน PID ตามช่วงความเร็ว (ตาราง SPEED_BANDS ใน config.h)
// หมายเหตุ: เดิมมี loadSensorCalibration() ไว้โหลดค่าอ้างอิงเซนเซอร์
// แต่ตอนนี้ค่าอ้างอิงถูก init ที่ตัวแปรกลางใน Robot_High_Automation.ino จาก config.h แล้ว

// คำนวณความเร็วฐานล้อหน้า/หลัง + เกน PID ตามช่วงของ baseSpeed
// เลือกแถวแรกใน SPEED_BANDS ที่ baseSpeed <= speedLimit (ถ้าเกินสุดให้ใช้แถวสุดท้าย)
void updateSpeedPidParams() {
  int i;
  SpeedBand band = SPEED_BANDS[SPEED_BAND_COUNT - 1];   // ค่าเริ่มต้น = แถวเร็วสุด

  maxSpeed = PID_OUTPUT_LIMIT;
  ki = 0;
  lineError = 0;
  prevLineError = 0;

  for (i = 0; i < SPEED_BAND_COUNT; i++) {
    if (baseSpeed <= SPEED_BANDS[i].speedLimit) {
      band = SPEED_BANDS[i];
      break;
    }
  }

  leftBaseSpeed  = baseSpeed + band.leftOffset;
  rightBaseSpeed = baseSpeed + band.rightOffset;
  backLeftBaseSpeed  = baseSpeed + band.backLeftOffset;
  backRightBaseSpeed = baseSpeed + band.backRightOffset;
  kp = band.kp;
  kd = band.kd;
  pidLoopDelayMs = band.pidLoopDelayMs;
}
