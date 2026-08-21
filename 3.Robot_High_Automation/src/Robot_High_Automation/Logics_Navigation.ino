// Logics_Navigation.ino
// ลอจิกนำทาง: เลี้ยวตามทิศทางของโหมด + เดินหาแยก (junction) 1 ช่อง
// (การหมุน/ความเร็ว อยู่ใน Driver_*; ระยะเวลาใน config.h)

// ---- เลี้ยวตามทิศทางของโหมด ----
// โหมด 5/7 = ทำงานฝั่งขวา, โหมด 6/8 = ทำงานฝั่งซ้าย

// เลี้ยว 90° ตามทิศของโหมด (5/7 = ขวา, 6/8 = ซ้าย)
void turnByMode() { if ((robotMode == 5) || (robotMode == 7)) turnRight(); else turnLeft(); }

// เลี้ยว 90° สวนทิศของโหมด (5/7 = ซ้าย, 6/8 = ขวา) — ใช้ตอนเลี้ยวออกจากแยก
void turnAgainstMode() { if ((robotMode == 5) || (robotMode == 7)) turnLeft(); else turnRight(); }

// กลับตัว 180° ตามทิศของโหมด (5/7 = ขวา, 6/8 = ซ้าย)
void uTurnByMode() { if ((robotMode == 5) || (robotMode == 7)) uTurnRight(); else uTurnLeft(); }

// เดินตามเส้นไปจนเจอแยก หรือครบเวลา
// คืนค่า: STATUS_JUNCTION = เจอแยก/เส้นดำ, 1 = ครบเวลาไม่เจอเส้น
int driveToJunction(int tracSpeed, int timeMs) {
  int status = STATUS_NORMAL;

  startStopwatch();
  forwardFor(tracSpeed, MOTION_START_TICK_MS);
  while (status == STATUS_NORMAL) {
    checkBridge();                    // เช็คตะเกียบ/สะพาน (ผลไม่ใช้ตรงนี้)
    updateLineError();
    if ((sensorL1 == 0) && (sensorR1 == 1)) {   // เจอดำข้างซ้าย → หมุนวนไปทางขวาจนเจอเส้น
      pivotRight(slowSpeed);
      while (sensorR3 == 1) { updateLineBinary(); }
      delay(PIVOT_SETTLE_MS);
      status = STATUS_JUNCTION;
    }
    else if ((sensorL1 == 1) && (sensorR1 == 0)) {   // เจอดำข้างขวา → หมุนวนไปทางซ้ายจนเจอเส้น
      pivotLeft(slowSpeed);
      while (sensorL3 == 1) { updateLineBinary(); }
      delay(PIVOT_SETTLE_MS);
      status = STATUS_JUNCTION;
    }
    else if (sensorC == 0) {          // เจอดำตรงกลาง → เจอแยก
      status = STATUS_JUNCTION;
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
