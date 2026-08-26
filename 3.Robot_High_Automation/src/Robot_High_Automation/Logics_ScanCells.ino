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
//  - status 1: ไม่เจอเส้นดำ → เช็คสี ถ้าเป็นพื้นที่วางให้วางบล็อค แล้วเลี้ยวตามทิศของโหมด
//  - status 2+: เจอแยก → เช็คสี ถ้าเป็นพื้นที่วางให้วางบล็อค (ปล่อย-ถอย-ปรับ-เลี้ยวตามโหมด)
//               ถ้าเป็นแยกธรรมดา (ขาว/ดำ) ถอยออกแยกแล้วเลี้ยวสวนโหมด
void followLineToColorBox(int tracSpeed, int timeMs) {
  int status = STATUS_NORMAL;

  startStopwatch();
  forwardFor(tracSpeed, MOTION_START_TICK_MS);
  while (status == STATUS_NORMAL) {
    status = followLineAndAlign();

    // ครบเวลาโดยไม่เจอแยก → เช็คสี/วางบล็อค แล้วเลี้ยวตามทิศโหมด
    if ((stopwatchElapsed() > timeMs) && (status == STATUS_NORMAL)) {
      status = 1;
      checkFloorAndKick();
      showColorValue();
      if (bridgeStatus == 2) {          // เพิ่งลงจากสะพาน → เดินข้ามไปให้พ้น
        followLineFor(speed, BRIDGE_CLEAR_MS);
        stopMotors();
        bridgeStatus = 0;
      }
      else if (bridgeStatus == 1) bridgeStatus = 2;   // เลี้ยวขาขึ้นสะพานเสร็จแล้ว
      if ((floorColor == White) || (floorColor == Black)) turnByMode();
      // เป็นพื้นที่วาง → checkFloorAndKick วางบล็อคเสร็จแล้ว (เลี้ยวตามโหมดไปแล้วใน placeBlockAndExit)
    }

    // เจอเส้นดำ (แยก) → เช็คสี/วางบล็อค หรือถอยออกจากแยก
    if (status >= STATUS_JUNCTION) {
      checkFloorAndKick();
      showColorValue();
      if ((floorColor == White) || (floorColor == Black)) {   // แยกธรรมดา → ถอยออกแยก แล้วเลี้ยวสวนโหมด
        backwardFor(speed, JUNCTION_BACKUP_MS);
        turnAgainstMode();
      }
      // เป็นพื้นที่วาง → checkFloorAndKick วางบล็อคเสร็จแล้ว (ปล่อย-ถอย-ปรับ-เลี้ยวตามโหมด) วนลูปต่อไป
      if (status == STATUS_DEADEND) stopMotors();
    }
  }
}

// เช็คสีพื้น ถ้าเป็นพื้นที่วางลูกบาศก์ (สีใดก็ได้) → วางบล็อค routine เดียว
// แล้วเช็คว่าเก็บครบ 4 สีหรือยัง (ครบ → ยกธงจบงาน)
void checkFloorAndKick() {
  stopMotors();
  delay(COLOR_READ_SETTLE_MS);
  detectFloorColor();
  delay(COLOR_READ_SETTLE_MS);

  // แดง/เหลืองอ่านสีซ้ำยืนยัน (ค่าสีเสี่ยงเพี้ยนรอบแรก — บันทึกใน skills.md)
  // หมายเหตุ: อ่านซ้ำแค่เพื่อความแม่นยำของสี — motion วางบล็อคยัง unified เดียวกันทุกสี
  if ((floorColor == Red) || (floorColor == Yellow)) {
    stopMotors();
    detectFloorColor();
  }

  // พื้นที่วาง (ไม่ใช่ขาว/ดำ) → วางบล็อค routine เดียวกันทุกสี ไม่แบ่งสี
  if ((floorColor == Blue) || (floorColor == Green) ||
      (floorColor == Red)  || (floorColor == Yellow)) {
    placeBlockAndExit();
  }

  // เก็บครบ 4 สีแล้ว → ยกธง
  if ((redCount > 0) && (yellowCount > 0) && (blueCount > 0) && (greenCount > 0)) {
    backwardFor(FLAG_BACKUP_SPEED, FLAG_BACKUP_MS);
    stopMotors();
    raiseFlag();
    finishRun();
  }
}

// วางบล็อค routine เดียวกันทุกสี (ไม่แบ่งสี):
//   1) ปล่อยลูกบาศก์ตามสีที่เช็คเจอ
//   2) ถอยหลังจนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ
//   3) ปรับให้ตรง (ให้เส้นตั้งฉาก/กึ่งกลางตัวหุ่น)
//   4) เลี้ยวตามโหมด แล้วลูปหลักวนต่อไป
void placeBlockAndExit() {
  kickForColor(floorColor);              // ปล่อยลูกบาศก์ก่อน
  reverseUntilBackLine();                // ถอยจนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ
  backwardAlign(PLACE_ALIGN_TOTAL_MS);   // ปรับให้ตรง
  turnByMode();                          // เลี้ยวตามโหมด
}

// ปล่อยลูกบาศก์ตามสีที่ตรวจเจอ (ช่องเซอร์โว 1 = น้ำเงิน/เขียว, ช่อง 2 = แดง/เหลือง) + นับจำนวน
void kickForColor(int color) {
  if (color == Blue)        { kickBlue();   blueCount++; }
  else if (color == Green)  { kickGreen();  greenCount++; }
  else if (color == Red)    { kickRed();    redCount++; }
  else if (color == Yellow) { kickYellow(); yellowCount++; }
}

// ถอยหลังช้าๆ จนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ (กันค้างด้วย timeout)
void reverseUntilBackLine() {
  startStopwatch();
  backwardFor(slowSpeed, MOTION_START_TICK_MS);   // กระตุกมอเตอร์ให้เริ่มถอย
  while (1) {
    updateBackLineBinary();
    if ((backL == 0) && (backR == 0)) break;                     // ทั้ง 2 ข้างเจอเส้นดำ → พอ
    if (stopwatchElapsed() > PLACE_REVERSE_TIMEOUT_MS) break;    // กันค้าง (ถอยนานเกินไม่เจอเส้น)
    backwardFor(slowSpeed, PLACE_REVERSE_STEP_MS);               // ถอยต่อไปทีละขั้น
  }
  stopMotors();
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
