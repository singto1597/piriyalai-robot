// junction_navigation.ino
// Logic เดินไปหาแยก (junction) 1 ช่อง ใช้ในโหมดวิ่งตรงยาว (7/8)

// เดินตามเส้นไปจนเจอแยก หรือครบเวลา
// คืนค่า: 2 = เจอแยก/เส้นดำ, 1 = ครบเวลาไม่เจอเส้น
int driveToJunction(int tracSpeed, int timeMs) {
  int status = 0;

  startStopwatch();
  forwardFor(tracSpeed, 1);
  while (status == 0) {
    checkBridge();                    // เช็คตะเกียบ/สะพาน (ผลไม่ใช้ตรงนี้)
    updateLineError();
    if ((sensorL1 == 0) && (sensorR1 == 1)) {   // เจอดำข้างซ้าย → หมุนวนไปทางขวาจนเจอเส้น
      AO();
      motor(1, -slowSpeed); motor(2, -slowSpeed);
      motor(3,  slowSpeed); motor(4,  slowSpeed);
      while (sensorR3 == 1) { updateLineBinary(); }
      delay(50);
      status = 2;
    }
    else if ((sensorL1 == 1) && (sensorR1 == 0)) {   // เจอดำข้างขวา → หมุนวนไปทางซ้ายจนเจอเส้น
      AO();
      motor(1, slowSpeed); motor(2, slowSpeed);
      motor(3, -slowSpeed); motor(4, -slowSpeed);
      while (sensorL3 == 1) { updateLineBinary(); }
      delay(50);
      status = 2;
    }
    else if (sensorC == 0) {          // เจอดำตรงกลาง → เจอแยก
      status = 2;
    }
    else if (stopwatchElapsed() > timeMs) {   // ครบเวลาโดยไม่เจอเส้นดำ
      status = 1;
    }
    else {
      followLinePid();
    }
  }
  return status;
}
