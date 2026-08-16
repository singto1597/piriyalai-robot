// auto_scan_cells_rgb.ino
// Logic โหมด 5/6: วิ่งเช็คสีทีละช่อง (ตามเส้น) ปล่อยลูกบาศก์สีที่ตรงกับช่อง แล้วเลี้ยวไปช่องถัดไป

// วนลูปวิ่งเช็คทีละช่องตลอด (จนกว่าจะเก็บครบ 4 สีแล้วยกธงจบ)
void autoScanCellsRgb() {
  while (1) {
    followOneCellRgb(speed, 1350);
  }
}

// วิ่งเข้าไป 1 ช่อง (เดินตามเส้นเป็นเวลา timeMs) แล้วคืนความเร็วเดิม
void followOneCellRgb(int tracSpeed, int timeMs) {
  baseSpeed = tracSpeed;
  updateSpeedPidParams();
  followLineToColorBox(tracSpeed, timeMs);
  baseSpeed = speed;
  updateSpeedPidParams();
}

// เดินตามเส้นไปเรื่อยๆ จนกว่าจะ: ครบเวลา (status=1) หรือเจอแยก (status>=2)
//  - status 1: ไม่เจอเส้นดำ → เช็คสี ดูแลสะพาน แล้วเลี้ยวตามทิศทางของ robotMode (5=ขวา, 6=ซ้าย)
//  - status 2+: เจอแยก → เช็คสี ถ้าเป็นพื้นที่วาง (ไม่ใช่ขาว/ดำ) ถอยออกมาแล้วปล่อยลูกบาศก์
void followLineToColorBox(int tracSpeed, int timeMs) {
  int status = 0;

  startStopwatch();
  forwardFor(tracSpeed, 1);
  while (status == 0) {
    status = followLineAndAlign();
    if ((stopwatchElapsed() > timeMs) && (status == 0)) {   // ครบเวลาโดยไม่เจอแยก
      status = 1;
      checkFloorAndKick();
      showColorValue();
      if (bridgeStatus == 2) {          // เพิ่งลงจากสะพาน → เดินข้ามไปให้พ้น
        followLineFor(speed, 1050);
        stopMotors();
        bridgeStatus = 0;
      }
      else if (bridgeStatus == 1) bridgeStatus = 2;   // เลี้ยวขาขึ้นสะพานเสร็จแล้ว
      if (robotMode == 5) turnRight(); else turnLeft();
    }
    if (status >= 2) {                  // เจอเส้นดำ (แยก)
      checkFloorAndKick();
      showColorValue();
      backwardFor(speed, 350);
      if ((floorColor != White) && (floorColor != Black)) backwardFor(speed, 550);   // เป็นพื้นที่วาง ถอยเพิ่ม
      if (robotMode == 5) turnLeft(); else turnRight();
      if (status == 4) stopMotors();
    }
  }
}

// เช็คสีพื้น แล้วปล่อยลูกบาศก์สีที่ตรงกับช่องนั้น (แดง/เหลืองต้องถอยมากกว่า + กลับตัว)
// ถ้าเก็บครบ 4 สี → ยกธงจบการทำงาน
void checkFloorAndKick() {
  stopMotors();
  delay(50);
  detectFloorColor();
  delay(50);
  switch (floorColor) {
    case Blue:
      backwardFor(speed, 150); AO();
      kickBlue(); blueCount++;
      break;
    case Green:
      backwardFor(speed, 150); AO();
      kickGreen(); greenCount++;
      break;
    default:
      // เช็คซ้ำอีกครั้ง (กรณีสีแรกไม่ตรง Blue/Green) → แดง/เหลือง
      stopMotors();
      detectFloorColor();
      switch (floorColor) {
        case Red:
          backwardFor(speed, 420); AO();
          kickRed(); redCount++;
          backwardFor(speed, 1050);
          uTurnLeft();
          break;
        case Yellow:
          backwardFor(speed, 420); AO();
          kickYellow(); yellowCount++;
          backwardFor(speed, 1050);
          uTurnLeft();
          break;
      }
  }
  // เก็บครบ 4 สีแล้ว → ยกธง
  if ((redCount > 0) && (yellowCount > 0) && (blueCount > 0) && (greenCount > 0)) {
    backwardFor(50, 50);
    stopMotors();
    raiseFlag();
    finishRun();
  }
}

// เช็คตะเกียบ/สะพานด้วยลิมิตสวิตช์ (analog 7)
// คืนค่า: 1 = เจอตะเกียบ, 2 = ปกติ, 3 = ขึ้นสะพาน, 4 = ลงสะพาน
int checkBridge() {
  if (analog(7) > refLimitSwitch) {   // สวิชถูกกด
    forwardFor(slowSpeed, 50);
    if (analog(7) < refLimitSwitch) {   // เดินไปแล้วพ้นสวิช → เจอตะเกียบ
      forwardFor(slowSpeed - 5, 1700);
      stopMotors();
      return 1;
    }
    else {                              // ยังกดอยู่ → เป็นสะพาน
      if (bridgeStatus == 0) {          // ขาขึ้นสะพาน
        followLineFor(speed, 2350);
        bridgeStatus = 1;
        return 3;
      }
      else {                            // ขาลงสะพาน
        while (analog(7) > refLimitSwitch) {}
        forwardFor(slowSpeed - 10, 100);
        bridgeStatus = 0;
        return 4;
      }
    }
  }
  else return 2;
}
