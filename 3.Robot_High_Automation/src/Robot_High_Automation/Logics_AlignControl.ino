// Logics_AlignControl.ino
// เดินตามเส้นพร้อมตรวจจับแยก/สะพาน และจัดตำแหน่งให้กึ่งกลางเส้น (ถอยหลัง)
// (ระยะเวลา/ความเร็ว อยู่ใน config.h; การอ่านเซนเซอร์อยู่ใน Driver_ReadSensor.ino)

// ---- ตัวช่วยตรวจตำแหน่งเส้น (อ่านจาก sensorL1/sensorR1 หลัง updateLineError) ----

// เส้นดำอยู่ทั้งสองข้างของเซนเซอร์หน้า (= เจอแยก/เส้นดำกว้าง)
bool lineOnBothSides() { return (sensorL1 == 0) && (sensorR1 == 0); }

// เส้นดำอยู่ฝั่งซ้ายของเซนเซอร์หน้า (ซ้ายดำ, ขวาขาว)
bool lineOnLeftSide()  { return (sensorL1 == 0) && (sensorR1 == 1); }

// เส้นดำอยู่ฝั่งขวาของเซนเซอร์หน้า (ซ้ายขาว, ขวาดำ)
bool lineOnRightSide() { return (sensorL1 == 1) && (sensorR1 == 0); }

// หมุนวนให้ watchSensor เห็นเส้น (ค่าเปลี่ยนเป็น 0) ภายใน timeoutMs
//  - leftSpin/rightSpin   : ความเร็วล้อซ้าย/ขวาตอนหมุน (เครื่องหมายกำหนดทิศ)
//  - retractLeft/Right    : ความเร็วหมุนกลับสั้นๆ เมื่อเจอทางตัน
//  - watchSensor          : ตัวแปรเซนเซอร์ที่ต้องเห็นเส้น (ส่งแบบอ้างอิง เพื่อบังคับค่าเมื่อ timeout)
//  - refreshSensors       : ฟังก์ชันอ่านเซนเซอร์ในลูป — ต้องเป็นตัวที่อัปเดต watchSensor
//                           (updateLineBinary = เซนเซอร์หน้า, updateBackLineBinary = เซนเซอร์หลัง)
// คืนค่า: STATUS_JUNCTION = เจอเส้นแล้ว, STATUS_DEADEND = หมุนครบเวลาแล้วไม่เจอ (ทางตัน)
int pivotToFindLine(int leftSpin, int rightSpin,
                    int retractLeft, int retractRight,
                    int &watchSensor,
                    int timeoutMs, int retractMs, int settleMs,
                    void (*refreshSensors)()) {
  bool deadEnd = false;

  AO();
  motor(MOTOR_CH_LEFT_1, leftSpin);   motor(MOTOR_CH_LEFT_2, leftSpin);
  motor(MOTOR_CH_RIGHT_1, rightSpin); motor(MOTOR_CH_RIGHT_2, rightSpin);
  startStopwatch4();

  while ((watchSensor == 1) && (!deadEnd)) {
    refreshSensors();
    if (stopwatchElapsed4() > timeoutMs) {   // หมุนนานเกิน → อีกฝั่งไม่มีเส้น (ทางตัน)
      stopMotors();
      watchSensor = 0;                       // บังคับให้ออกจากลูป
      deadEnd = true;
      motor(MOTOR_CH_LEFT_1, retractLeft);   motor(MOTOR_CH_LEFT_2, retractLeft);
      motor(MOTOR_CH_RIGHT_1, retractRight); motor(MOTOR_CH_RIGHT_2, retractRight);
      delay(retractMs);
      stopMotors();
    }
  }
  delay(settleMs);                           // รอให้หุ่นหยุดนิ่ง (ทั้งกรณีเจอเส้นและทางตัน)
  return deadEnd ? STATUS_DEADEND : STATUS_JUNCTION;
}

// หมุนวนไปทางขวาจนเซนเซอร์ขวาสุดเห็นเส้น (เมื่อเส้นอยู่ฝั่งซ้าย)
int pivotToLineRight() {
  return pivotToFindLine(-pivotSpeed, pivotSpeed, pivotSpeed, -pivotSpeed, sensorR3,
                         PIVOT_ALIGN_TIMEOUT_MS,
                         PIVOT_ALIGN_TIMEOUT_MS - PIVOT_DEADEND_RETRACT_MS,
                         PIVOT_SETTLE_MS,
                         updateLineBinary);
}

// หมุนวนไปทางซ้ายจนเซนเซอร์ซ้ายสุดเห็นเส้น (เมื่อเส้นอยู่ฝั่งขวา)
int pivotToLineLeft() {
  return pivotToFindLine(pivotSpeed, -pivotSpeed, -pivotSpeed, pivotSpeed, sensorL3,
                         PIVOT_ALIGN_TIMEOUT_MS,
                         PIVOT_ALIGN_TIMEOUT_MS - PIVOT_DEADEND_RETRACT_MS,
                         PIVOT_SETTLE_MS,
                         updateLineBinary);
}

// เดินตามเส้น + ตรวจจับเส้นดำพิเศษ (แยก/เส้นดำ)
// คืนค่า: STATUS_NORMAL = ยังเดินต่อ, STATUS_JUNCTION = เจอแยก/เส้นดำ, STATUS_DEADEND = ทางตัน
int followLineAndAlign() {
  checkBridge();                       // เช็คตะเกียบ/สะพาน (ผลไม่ใช้ตรงนี้)
  delay(pidLoopDelayMs);
  updateLineError();

  // 1) เจอแยก (เส้นดำทั้งสองข้าง) → อ่านซ้ำเพื่อยืนยัน
  if (lineOnBothSides()) {
    delay(LINE_RECHECK_DELAY_MS);
    updateLineError();
    if (lineOnBothSides()) return STATUS_JUNCTION;
    return STATUS_NORMAL;              // อ่านซ้ำแล้วไม่เจอแยก → เดินต่อ
  }

  // 2) เส้นดำฝั่งซ้าย → หมุนวนไปทางขวาจนเซนเซอร์ขวาสุดเห็นเส้น
  if (lineOnLeftSide()) {
    updateLineError();                 // (เดิม: กรณีนี้ไม่มี delay ก่อนอ่านซ้ำ)
    if (lineOnBothSides()) return STATUS_JUNCTION;
    if (!lineOnLeftSide()) return STATUS_NORMAL;    // เส้นหลุดระหว่างอ่านซ้ำ → เดินต่อ
    return pivotToLineRight();
  }

  // 3) เส้นดำฝั่งขวา → หมุนวนไปทางซ้ายจนเซนเซอร์ซ้ายสุดเห็นเส้น
  if (lineOnRightSide()) {
    delay(LINE_RECHECK_DELAY_MS);      // (เดิม: กรณีนี้มี delay ก่อนอ่านซ้ำ)
    updateLineError();
    if (lineOnBothSides()) return STATUS_JUNCTION;
    if (!lineOnRightSide()) return STATUS_NORMAL;
    return pivotToLineLeft();
  }

  // 4) ไม่เจอแยก → เดินตามเส้นด้วย PID ปกติ
  followLinePid();
  return STATUS_NORMAL;
}

// ถอยหลังปรับสมดุลให้เส้นอยู่ตรงกลางเซนเซอร์หลัง
// คืนค่า: 1 = ปรับซ้ายสำเร็จ, 2 = ปรับขวาสำเร็จ, 3 = เจอเส้นทั้งสองข้าง, 4 = หมดเวลาหรือทางตัน
int backwardAlign(int timeMs) {
  int status = STATUS_NORMAL;          // 0
  startStopwatch();
  backwardFor(slowSpeed, MOTION_START_TICK_MS);

  while (status == STATUS_NORMAL) {
    updateBackLineBinary();

    // เส้นดำอยู่ซ้ายหลัง → หมุนวนให้เส้นไปเข้าขวาหลัง (ล้อขวาถอยช้าครึ่งหนึ่งเพื่อกันไถล)
    if ((backL == 0) && (backR == 1)) {
      status = 1;   // ปรับทางซ้ายสำเร็จ (ค่ารหัสเฉพาะ backwardAlign)
      if (pivotToFindLine(slowSpeed, -slowSpeed, -slowSpeed, slowSpeed, backR,
                          BACK_ALIGN_TIMEOUT_MS, BACK_ALIGN_TIMEOUT_MS / 2,
                          BACK_PIVOT_SETTLE_MS,
                          updateBackLineBinary) == STATUS_DEADEND) {
        status = STATUS_DEADEND;
      }
    }
    // เส้นดำอยู่ขวาหลัง → หมุนวนให้เส้นไปเข้าซ้ายหลัง (ล้อขวาเดินหน้าช้าครึ่งหนึ่งเพื่อกันไถล)
    else if ((backL == 1) && (backR == 0)) {
      status = 2;   // ปรับทางขวาสำเร็จ (ค่ารหัสเฉพาะ backwardAlign)
      if (pivotToFindLine(-slowSpeed, slowSpeed / 2, slowSpeed, -slowSpeed, backL,
                          BACK_ALIGN_TIMEOUT_MS, BACK_ALIGN_TIMEOUT_MS / 2,
                          BACK_PIVOT_SETTLE_MS,
                          updateBackLineBinary) == STATUS_DEADEND) {
        status = STATUS_DEADEND;
      }
    }
    // เจอเส้นทั้งสองข้าง → จัดตำแหน่งเรียบร้อย
    else if ((backL == 0) && (backR == 0)) status = 3;

    if (stopwatchElapsed() > timeMs) status = STATUS_DEADEND;   // หมดเวลาถอยหลัง
  }
  stopMotors();
  return status;
}
