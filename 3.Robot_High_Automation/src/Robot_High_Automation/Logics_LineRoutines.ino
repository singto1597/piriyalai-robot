// Logics_LineRoutines.ino
// ท่ารวมสำหรับเดินตามเส้นเป็นเวลาที่กำหนด

// เดินตามเส้นด้วยความเร็วที่กำหนดเป็นระยะเวลาที่กำหนด
// (ใช้ต่อเนื่องจากการวิ่งช่องละช่อง / ข้ามสะพาน)
void followLineFor(int tracSpeed, int tracTimeMs) {
  baseSpeed = tracSpeed;
  updateSpeedPidParams();
  startStopwatch3();
  updateLineError();
  while (stopwatchElapsed3() < tracTimeMs) {
    followLinePid();
    delay(pidLoopDelayMs);
    updateLineError();
  }
  baseSpeed = speed;
  updateSpeedPidParams();
}
