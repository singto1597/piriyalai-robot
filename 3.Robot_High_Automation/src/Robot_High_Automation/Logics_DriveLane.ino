// Logics_DriveLane.ino
// Logic โหมด 7/8: วิ่งตรงยาวในช่อง (ตามเส้น) เช็คสีพื้นที่วาง
// ถ้าเจอช่องว่างให้เลี้ยวเข้าไป; ถ้าช่องเดิมวางซ้ำ → สลับไปโหมดเช็คทีละช่อง
// (ระยะเวลา/ความเร็ว อยู่ใน config.h)

// เช็คว่าลูกบาศก์สีใดสีหนึ่งถูกปล่อยไปแล้วอย่างน้อย 2 ครั้ง
// (= เจอช่องเดิมที่วางลูกบาศก์ไปแล้ว) → ต้องสลับไปโหมดเช็คทีละช่อง
bool isColorAlreadyPlaced() {
  return (redCount > 1) || (yellowCount > 1) || (blueCount > 1) || (greenCount > 1);
}

// จัดการเมื่อเจอพื้นที่วางลูกบาศก์: ถอยเข้าไป, กลับตัว, จัดตำแหน่ง
// ถ้าช่องนี้วางซ้ำสีเดิม → สลับไปโหมดเช็คทีละช่อง (5/6) และวิ่งเช็คต่อไป
void handleDropZoneCell() {
  backwardFor(DROP_BACKUP_SPEED, DROP_BACKUP_MS);
  uTurnByMode();
  backwardAlign(ALIGN_DROP_TOTAL_MS);

  if (!isColorAlreadyPlaced()) return;   // ช่องใหม่ → ปล่อยไปแล้ว กลับไปเดินเส้นยาวต่อ

  // ช่องเดิมวางซ้ำ → เดินหน้า เลี้ยว แล้วสลับโหมดไปเช็คทีละช่อง
  forwardFor(speed, DUP_CELL_DRIVE_MS);
  turnByMode();
  robotMode = robotMode - MODE_LANE_TO_SCAN_OFFSET;

  if (backwardAlign(ALIGN_TOTAL_MS) == STATUS_DEADEND) {   // ไม่มีเส้นให้จูน
    stopMotors();
    forwardFor(slowSpeed, REJOIN_FORWARD_MS);
  }
  else {                                                    // มีเส้นให้จูน
    stopMotors();
    forwardFor(slowSpeed, REJOIN_SHORT_FORWARD_MS);
  }
  autoScanCellsRgb();
}

// เดินไปเส้นข้างๆ (เมื่อช่องปัจจุบันไม่ใช่พื้นที่วาง)
// ถ้าเจอทางตันซ้ำ 2 ครั้ง → ย้อนกลับมาเดินทางเดิม
void handleAdjacentLane() {
  turnByMode();
  backwardAlign(ALIGN_TOTAL_MS);

  if (driveToJunction(speed, JUNCTION_DRIVE_MS) != STATUS_JUNCTION) return;   // ไม่ทางตัน → เดินต่อ

  // ทางตัน → กลับหลังหัน แล้วลองเส้นที่ 3
  stopMotors();
  backwardFor(speed, DEAD_END_BACKUP_MS);
  uTurnByMode();
  backwardAlign(ALIGN_TOTAL_MS);

  if (driveToJunction(speed, JUNCTION_DRIVE_MS) != STATUS_JUNCTION) return;

  // ทางตันด้านที่ 3 → ย้อนกลับมาเดินทางเดิม
  stopMotors();
  backwardFor(speed, DEAD_END_BACKUP_MS);
  turnAgainstMode();
  backwardAlign(ALIGN_TOTAL_MS);
}

void autoDriveLaneRgb() {
  int status;

  while (1) {
    status = STATUS_NORMAL;
    forwardFor(speed, MOTION_START_TICK_MS);
    while (status == STATUS_NORMAL) {                       // ทางหลัก
      status = followLineAndAlign();
      if (status < STATUS_JUNCTION) continue;               // ยังไม่เจอแยก → เดินตามเส้นต่อ

      // เจอแยก/เส้นดำ → เช็คสีพื้นที่วาง
      checkFloorAndKick();
      if ((floorColor != White) && (floorColor != Black)) handleDropZoneCell();   // เจอพื้นที่วาง
      else handleAdjacentLane();                                                   // เดินไปเส้นข้างๆ
    }
  }
}
