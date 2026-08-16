// auto_lane_rgb.ino
// Logic โหมด 7/8: วิ่งตรงยาวในช่อง (ตามเส้น) เช็คสีพื้นที่วาง
// ถ้าเจอช่องว่างให้เลี้ยวเข้าไป; ถ้าช่องเดิมวางซ้ำ → สลับไปโหมดเช็คทีละช่อง

void autoDriveLaneRgb() {
  int status;

  while (1) {
    status = 0;
    forwardFor(speed, 1);
    while (status == 0) {                       // ทางหลัก
      status = followLineAndAlign();
      if (status >= 2) {                        // เจอแยก/เส้นดำ
        checkFloorAndKick();
        if ((floorColor != White) && (floorColor != Black)) {   // เจอพื้นที่วาง
          backwardFor(50, 200);
          if (robotMode == 8) uTurnLeft(); else uTurnRight();
          backwardAlign(350);
          if ((redCount > 1) || (yellowCount > 1) || (blueCount > 1) || (greenCount > 1)) {   // สีเดิมวางไปแล้ว
            forwardFor(speed, 500);
            if (robotMode == 8) turnLeft(); else turnRight();
            robotMode = robotMode - 2;          // สลับไปโหมดเช็คทีละช่อง (วนทางเดิมทีละช่อง)
            if (backwardAlign(400) == 4) {      // ไม่มีเส้นให้จูน
              stopMotors();
              forwardFor(slowSpeed, 400);
            }
            else {                              // มีเส้นให้จูน
              stopMotors();
              forwardFor(slowSpeed, 200);
            }
            autoScanCellsRgb();
          }
        }
        else {                                  // ไม่เจอพื้นที่วาง → เลี้ยวไปเส้นข้างๆ
          if (robotMode == 7) turnRight(); else turnLeft();
          backwardAlign(400);
          if (driveToJunction(speed, 400) == 2) {   // ทางตัน → กลับหลังหัน
            stopMotors();
            backwardFor(speed, 230);
            if (robotMode == 7) uTurnRight(); else uTurnLeft();
            backwardAlign(400);
            if (driveToJunction(speed, 400) == 2) {   // ทางตันด้านที่ 3 → ย้อนกลับ
              stopMotors();
              backwardFor(speed, 230);
              if (robotMode == 7) turnLeft(); else turnRight();
              backwardAlign(400);
            }
          }
        }
      }
    }
  }
}
