// balance_control.ino
// เดินตามเส้นพร้อมตรวจจับแยก/สะพาน และจัดตำแหน่งให้กึ่งกลางเส้น (ถอยหลัง)

// เดินตามเส้น + ตรวจจับเส้นดำพิเศษ (แยก/เส้นดำ)
// คืนค่า: 0 = ยังเดินต่อ, 2 = เจอแยก/เส้นดำ, 4 = อีกฝั่งไม่เจอเส้น (ทางตัน)
int followLineAndAlign() {
  int status = 0;
  int alignTimeoutMs = 500;

  checkBridge();        // เช็คตะเกียบ/สะพาน (ผลไม่ใช้ตรงนี้)
  delay(pidLoopDelayMs);
  updateLineError();

  // เส้นดำอยู่ทั้งสองข้างของเซนเซอร์หน้า → เจอแยก
  if ((sensorL1 == 0) && (sensorR1 == 0)) {
    delay(5);
    updateLineError();
    if ((sensorL1 == 0) && (sensorR1 == 0)) status = 2;
  }
  // เส้นดำอยู่ฝั่งซ้าย → หมุนวนไปทางขวาหาเส้น
  else if ((sensorL1 == 0) && (sensorR1 == 1)) {
    updateLineError();
    if ((sensorL1 == 0) && (sensorR1 == 0)) status = 2;
    else if ((sensorL1 == 0) && (sensorR1 == 1)) {
      status = 2;
      AO();
      motor(1, -pivotSpeed); motor(2, -pivotSpeed);
      motor(3,  pivotSpeed); motor(4,  pivotSpeed);
      startStopwatch4();
      while (sensorR3 == 1) {
        updateLineBinary();
        if (stopwatchElapsed4() > alignTimeoutMs) {   // วนนานเกิน → อีกฝั่งไม่มีเส้น (ทางตัน)
          stopMotors();
          sensorR3 = 0;
          status = 4;
          motor(1, pivotSpeed); motor(2, pivotSpeed);
          motor(3, -pivotSpeed); motor(4, -pivotSpeed);
          delay(alignTimeoutMs - 50);
          stopMotors();
        }
      }
      delay(50);
    }
  }
  // เส้นดำอยู่ฝั่งขวา → หมุนวนไปทางซ้ายหาเส้น
  else if ((sensorL1 == 1) && (sensorR1 == 0)) {
    delay(5);
    updateLineError();
    if ((sensorL1 == 0) && (sensorR1 == 0)) status = 2;
    else if ((sensorL1 == 1) && (sensorR1 == 0)) {
      status = 2;
      AO();
      motor(1, pivotSpeed); motor(2, pivotSpeed);
      motor(3, -pivotSpeed); motor(4, -pivotSpeed);
      startStopwatch4();
      while (sensorL3 == 1) {
        updateLineBinary();
        if (stopwatchElapsed4() > alignTimeoutMs) {   // วนนานเกิน → อีกฝั่งไม่มีเส้น (ทางตัน)
          stopMotors();
          sensorL3 = 0;
          status = 4;
          motor(1, -pivotSpeed); motor(2, -pivotSpeed);
          motor(3,  pivotSpeed); motor(4,  pivotSpeed);
          delay(alignTimeoutMs - 50);
          stopMotors();
        }
      }
      delay(50);
    }
  }
  else {
    followLinePid();   // ไม่เจอแยก → เดินตามเส้นด้วย PID ปกติ
  }
  return status;
}

// ถอยหลังปรับสมดุลให้เส้นอยู่ตรงกลางเซนเซอร์หลัง
// คืนค่า: 1 = ปรับทางซ้ายสำเร็จ, 2 = ปรับทางขวา, 3 = เจอเส้นทั้งสองข้าง, 4 = หมดเวลาหรือทางตัน
int backwardAlign(int timeMs) {
  int status = 0;
  int alignTimeoutMs = 400;

  startStopwatch();
  backwardFor(slowSpeed, 1);

  while (status == 0) {
    updateBackLineBinary();
    if ((backL == 0) && (backR == 1)) {   // เส้นดำอยู่ซ้าย → หมุนวนไปทางขวาหาเส้น
      status = 1;
      AO();
      motor(1, slowSpeed); motor(2, slowSpeed);
      motor(3, -slowSpeed); motor(4, -slowSpeed);
      startStopwatch1();
      while (backR == 1) {
        updateBackLineBinary();
        if (stopwatchElapsed1() > alignTimeoutMs) {   // วนนานเกิน → ทางตัน
          stopMotors();
          backR = 0;
          status = 4;
          motor(1, -slowSpeed); motor(2, -slowSpeed);
          motor(3, slowSpeed); motor(4, slowSpeed);
          delay(alignTimeoutMs / 2);
          stopMotors();
        }
      }
      delay(30);
    }
    else if ((backL == 1) && (backR == 0)) {   // เส้นดำอยู่ขวา → หมุนวนไปทางซ้ายหาเส้น
      status = 2;
      AO();
      motor(1, -slowSpeed); motor(2, -slowSpeed);
      motor(3, slowSpeed / 2); motor(4, slowSpeed / 2);
      startStopwatch1();
      while (backL == 1) {
        updateBackLineBinary();
        if (stopwatchElapsed1() > alignTimeoutMs) {   // วนนานเกิน → ทางตัน
          stopMotors();
          backL = 0;
          status = 4;
          motor(1, slowSpeed); motor(2, slowSpeed);
          motor(3, -slowSpeed); motor(4, -slowSpeed);
          delay(alignTimeoutMs / 2);
          stopMotors();
        }
      }
      delay(30);
    }
    else if ((backL == 0) && (backR == 0)) status = 3;   // เจอเส้นทั้งสองข้าง
    if (stopwatchElapsed() > timeMs) status = 4;          // หมดเวลาถอยหลัง
  }
  stopMotors();
  return status;
}
