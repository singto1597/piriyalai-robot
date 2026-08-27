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
      showRunStatus();
      if ((floorColor == White) || (floorColor == Black)) turnByMode();
      // เป็นพื้นที่วาง → checkFloorAndKick วางบล็อคเสร็จแล้ว (เลี้ยวตามโหมดไปแล้วใน placeBlockAndExit)
    }

    // เจอเส้นดำ (แยก) → เช็คสี/วางบล็อค หรือถอยออกจากแยก
    if (status >= STATUS_JUNCTION) {
      if (status == STATUS_JUNCTION) backOffJunction();   // เซนเซอร์หน้าเจอเส้น → ถอยนิดหน่อยก่อนเช็คสี (กันเบรกไม่ทัน)
      checkFloorAndKick();
      showRunStatus();
      if ((floorColor == White) || (floorColor == Black)) {   // แยกธรรมดา → ถอยออกแยก แล้วเลี้ยวสวนโหมด
        backwardFor(speed, JUNCTION_BACKUP_MS);
        turnAgainstMode();
      }
      // เป็นพื้นที่วาง → checkFloorAndKick วางบล็อคเสร็จแล้ว (ปล่อย-ถอย-ปรับ-เลี้ยวตามโหมด) วนลูปต่อไป
      if (status == STATUS_DEADEND) stopMotors();
    }
  }
}

// ถอยออกจากเส้นดำนิดหน่อย กันหุ่นวิ่งเร็ว/เบรกไม่ทัน (เซนเซอร์หน้าเพิ่งเจอเส้น)
// เรียกก่อนเช็คสี เพื่อให้ RGB sensor กลับมาอยู่เหนือช่องเดิม ไม่ไปอ่านสีฝั่งตรงข้ามเส้น
// (ระยะถอยใน config.h — JUNCTION_BACKOFF_MS)
void backOffJunction() {
  reverseForWithBackPid(slowSpeed, JUNCTION_BACKOFF_MS);
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

  // สีที่เคยวางไปเรียบร้อยแล้ว (count > 0) → ถือเป็นสีขาว (ข้าม ไม่วางซ้ำ แล้ววนลูปต่อไป)
  if ((floorColor == Red && redCount > 0) ||
      (floorColor == Yellow && yellowCount > 0) ||
      (floorColor == Blue && blueCount > 0) ||
      (floorColor == Green && greenCount > 0)) {
    floorColor = White;
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
//   1) ปล่อยลูกบาศก์ตามสีที่เช็คเจอ (แดง/เหลืองถอยออกก่อนปล่อย)
//   2) ถอยหลังจนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ (PID เซนเซอร์หลังปรับให้ถอยตรง)
//   3) ปรับให้ตรง (ให้เส้นตั้งฉาก/กึ่งกลางตัวหุ่น)
//   4) เดินหน้าให้ห่างจากเส้น (กันหุ่นติด/หมุนทับเส้น)
//   5) เลี้ยวตามโหมด แล้วลูปหลักวนต่อไป
void placeBlockAndExit() {
  kickForColor(floorColor);              // ปล่อยลูกบาศก์ก่อน
  reverseWithBackPid(slowSpeed, PLACE_REVERSE_STEP_MS, PLACE_REVERSE_TIMEOUT_MS);  // ถอยจนเซนเซอร์หลังทั้ง 2 ข้างเจอเส้นดำ (ปรับตรงด้วย PID เซนเซอร์หลัง)
  backwardAlign(PLACE_ALIGN_TOTAL_MS);   // ปรับให้ตรง
  forwardFor(slowSpeed, PLACE_LEAVE_LINE_FORWARD_MS);   // เดินหน้าให้ห่างออกมาจากเส้น
  turnByMode();                          // เลี้ยวตามโหมด
}

// ปล่อยลูกบาศก์ตามสีที่ตรวจเจอ (ช่องเซอร์โว 1 = น้ำเงิน/เขียว, ช่อง 2 = แดง/เหลือง) + นับจำนวน
// แดง/เหลืองปล่อยลึกเข้าไปในพื้นที่วาง → ถอยออกมานิดหน่อยก่อนแล้วค่อยปล่อย
void kickForColor(int color) {
  if (color == Red) {
    reverseForWithBackPid(slowSpeed, KICK_RED_YELLOW_BACKUP_MS);   // ถอยออกก่อนปล่อย
    kickRed();
    redCount++;
  }
  else if (color == Yellow) {
    reverseForWithBackPid(slowSpeed, KICK_RED_YELLOW_BACKUP_MS);   // ถอยออกก่อนปล่อย
    kickYellow();
    yellowCount++;
  }
  else if (color == Blue)  { kickBlue();   blueCount++; }
  else if (color == Green) { kickGreen();  greenCount++; }
}

// เช็คตะเกียบ/สะพาน (ลิมิตสวิตช์ — อ่านแบบดิจิทัล) — ยุบรวมกันเป็นอันเดียวแล้ว
// ถ้าสวิชถูกกด = เจอสิ่งกีดขวาง (ตะเกียบหรือสะพาน — พฤติกรรมคล้ายกัน ไม่ต้องแยก)
// → เดินตามเส้นตามเวลา BRIDGE_CLEAR_MS ให้พ้นไปเลย (ระยะเดียวใน config.h)
void checkBridge() {
  if (!limitSwitchPressed()) return;        // สวิชไม่ถูกกด = ปกติ ไม่ต้องทำอะไร
  followLineFor(speed, BRIDGE_CLEAR_MS);    // เดินตามเส้นข้ามตะเกียบ/สะพานให้พ้น
  stopMotors();
}
