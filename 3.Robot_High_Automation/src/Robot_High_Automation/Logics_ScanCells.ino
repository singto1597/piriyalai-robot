// Logics_ScanCells.ino
// Logic โหมด 5/6: วิ่งเช็คสีทีละช่อง (ตามเส้น) ปล่อยลูกบาศก์สีที่ตรงกับช่อง แล้วเลี้ยวไปช่องถัดไป
// (ระยะเวลา/ความเร็ว/ขา อยู่ใน config.h)

// วนลูปวิ่งเช็คทีละช่องตลอด (จนกว่าจะเก็บครบ 4 สีแล้วยกธงจบ)
void autoScanCellsRgb() {
  while (1) {
    followOneCellRgb(speed, CELL_SCAN_TIME_MS);
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

// เดินตามเส้นไปเรื่อยๆ จนกว่าจะ: ครบเวลา (status=1) หรือเจอแยก (status>=STATUS_JUNCTION)
//  - status 1: ไม่เจอเส้นดำ → ดูสีที่อ่านกลางช่อง: ถ้าเป็นช่องวาง (ฟ้า/เขียว/เหลือง/แดง) → หยุดปล่อย
//              ถ้าเป็นขาว/ดำ → ไม่หยุด เลี้ยวตามทิศทางของโหมดเลย (เร็วขึ้น — ไม่เสียเวลาเช็คซ้ำ)
//              แล้วดูแลสะพาน
//  - status 2+: เจอแยก → เช็คสี ถ้าเป็นพื้นที่วาง (ไม่ใช่ขาว/ดำ) ถอยออกมาแล้วปล่อยลูกบาศก์
void followLineToColorBox(int tracSpeed, int timeMs) {
  int status = STATUS_NORMAL;
  bool colorScanned = false;            // อ่านสีกลางช่องแล้วหรือยัง

  startStopwatch();
  forwardFor(tracSpeed, MOTION_START_TICK_MS);
  while (status == STATUS_NORMAL) {
    status = followLineAndAlign();

    // อ่านสีกลางช่องครั้งเดียว (หุ่นอยู่กลางช่อง = ตำแหน่งแม่นสุด)
    // ใช้พยากรณ์สีช่องก่อนถึงปลายช่อง: ถ้าเป็นขาว/ดำ → ปลายช่องเลี้ยวเลย ไม่ต้องหยุดเช็ค
    // หมายเหตุ: อ่านขณะหุ่นยังวิ่ง (~160ms) — ตำแหน่งหยุดยังเท่าเดิม (stopwatch นับเวลารวม)
    //           แต่สีที่อ่านคือตำแหน่งกลางช่อง (แม่นกว่าเดิมที่อ่านตอนหยุดปลายช่อง)
    if (!colorScanned && (status == STATUS_NORMAL) &&
        (stopwatchElapsed() > (long)timeMs * CELL_COLOR_SNAPSHOT_PERCENT / 100)) {
      detectFloorColor();
      colorScanned = true;
    }

    // ครบเวลาโดยไม่เจอแยก → เช็คสี/สะพาน แล้วเลี้ยวตามทิศโหมด
    if ((stopwatchElapsed() > timeMs) && (status == STATUS_NORMAL)) {
      status = 1;
      if (!colorScanned) detectFloorColor();   // เผื่อช่องสั้นจนอ่านกลางช่องไม่ทัน

      // ช่องขาว/ดำ → ไม่ใช่ช่องวาง: ข้ามการหยุดเช็คซ้ำไปเลย (ประหยัด ~360ms/ช่อง)
      // ช่องวางจริง (ฟ้า/เขียว/เหลือง/แดง) → หยุดปล่อย (checkFloorAndKick อ่านซ้ำเพื่อยืนยันเอง)
      if (!((floorColor == White) || (floorColor == Black))) {
        checkFloorAndKick();
      }
      showColorValue();
      if (bridgeStatus == 2) {          // เพิ่งลงจากสะพาน → เดินข้ามไปให้พ้น
        followLineFor(speed, BRIDGE_CLEAR_MS);
        stopMotors();
        bridgeStatus = 0;
      }
      else if (bridgeStatus == 1) bridgeStatus = 2;   // เลี้ยวขาขึ้นสะพานเสร็จแล้ว
      turnByMode();
    }

    // เจอเส้นดำ (แยก) → เช็คสี/ปล่อยลูกบาศก์ แล้วเลี้ยวออกจากแยก
    if (status >= STATUS_JUNCTION) {
      checkFloorAndKick();
      showColorValue();
      backwardFor(speed, JUNCTION_BACKUP_MS);
      if ((floorColor != White) && (floorColor != Black)) backwardFor(speed, DROP_ZONE_BACKUP_MS);   // เป็นพื้นที่วาง ถอยเพิ่ม
      turnAgainstMode();
      if (status == STATUS_DEADEND) stopMotors();
    }
  }
}

// เช็คสีพื้น แล้วปล่อยลูกบาศก์สีที่ตรงกับช่องนั้น (แดง/เหลืองต้องถอยมากกว่า + กลับตัว)
// ถ้าเก็บครบ 4 สี → ยกธงจบการทำงาน
void checkFloorAndKick() {
  stopMotors();
  delay(COLOR_READ_SETTLE_MS);
  detectFloorColor();
  delay(COLOR_READ_SETTLE_MS);

  if ((floorColor == Blue) || (floorColor == Green)) {
    // น้ำเงิน/เขียว: ปล่อยเซอร์โวช่อง 1 (ถอยสั้นๆ ไม่ต้องกลับตัว)
    backwardFor(speed, KICK_BACKUP_MS);
    AO();
    if (floorColor == Blue) { kickBlue(); blueCount++; }
    else                    { kickGreen(); greenCount++; }
  }
  else if ((floorColor == Red) || (floorColor == Yellow)) {
    // แดง/เหลือง: เช็คสีซ้ำอีกครั้ง (สีแรกอาจเพี้ยน) แล้วปล่อยเซอร์โวช่อง 2 (ถอยไกล + กลับตัว)
    // (เดิมเป็น else — ขาว/ดำจะถูกบังคับอ่านซ้ำเสีย ~314ms; เปลี่ยนเป็น else-if เพื่อข้ามขาว/ดำทันที)
    stopMotors();
    detectFloorColor();
    if ((floorColor == Red) || (floorColor == Yellow)) {
      backwardFor(speed, RED_YELLOW_BACKUP_MS);
      AO();
      if (floorColor == Red) { kickRed(); redCount++; }
      else                   { kickYellow(); yellowCount++; }
      backwardFor(speed, RED_YELLOW_UTURN_MS);
      uTurnLeft();
    }
  }

  // เก็บครบ 4 สีแล้ว → ยกธง
  if ((redCount > 0) && (yellowCount > 0) && (blueCount > 0) && (greenCount > 0)) {
    backwardFor(FLAG_BACKUP_SPEED, FLAG_BACKUP_MS);
    stopMotors();
    raiseFlag();
    finishRun();
  }
}

// เช็คตะเกียบ/สะพานด้วยลิมิตสวิตช์ (PIN_LIMIT_SWITCH)
// คืนค่า: BRIDGE_FORK = เจอตะเกียบ, BRIDGE_NORMAL = ปกติ, BRIDGE_CLIMB = ขึ้นสะพาน, BRIDGE_DESCEND = ลงสะพาน
int checkBridge() {
  if (analog(PIN_LIMIT_SWITCH) <= refLimitSwitch) return BRIDGE_NORMAL;   // สวิชไม่ถูกกด (= เดิม: !(> ref)) = ปกติ

  // สวิชถูกกด → เดินแตะสวิชอีกที ถ้าพ้นแล้ว = เจอตะเกียบ
  forwardFor(slowSpeed, BRIDGE_PROBE_MS);
  if (analog(PIN_LIMIT_SWITCH) < refLimitSwitch) {
    forwardFor(slowSpeed - FORK_CLEAR_SPEED_OFFSET, FORK_CLEAR_MS);
    stopMotors();
    return BRIDGE_FORK;
  }

  // ยังกดอยู่ → เป็นสะพาน
  if (bridgeStatus == 0) {          // ขาขึ้นสะพาน
    followLineFor(speed, BRIDGE_UP_MS);
    bridgeStatus = 1;
    return BRIDGE_CLIMB;
  }
  // ขาลงสะพาน
  while (analog(PIN_LIMIT_SWITCH) > refLimitSwitch) {}
  forwardFor(slowSpeed - BRIDGE_DOWN_SPEED_OFFSET, BRIDGE_DOWN_MS);
  bridgeStatus = 0;
  return BRIDGE_DESCEND;
}
