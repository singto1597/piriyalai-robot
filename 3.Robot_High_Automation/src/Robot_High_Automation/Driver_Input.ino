// Driver_Input.ino
// อ่านปุ่ม OK / สวิตช์ SW_A SW_B และ knob (อินพุตฮาร์ดแวร์)
// รวมโหมดทดสอบ (test mode) ที่เลือกจาก knob

// เช็คว่ากดปุ่ม OK ค้างอยู่หรือไม่
bool isOkPressed() {
  if (SW_OK()) return true;
  else return false;
}

// รอจนกว่าจะปล่อยปุ่ม OK
void waitOkRelease() {
  while (isOkPressed()) { delay(BUTTON_POLL_DELAY_MS); }
}

// รอจนกว่าจะกดปุ่ม OK
void waitOkPress() {
  while (isOkPressed() == false) { delay(BUTTON_POLL_DELAY_MS); }
}

// รอให้ผู้ใช้กด-ปล่อยปุ่ม OK หนึ่งครั้ง (ใช้ในเมนู calibrate)
void waitOkTap() {
  waitOkRelease();
  waitOkPress();
}

// รอให้ผู้ใช้กด-ปล่อยปุ่ม OK หนึ่งครั้ง แล้วส่งเสียง beep ตามโทนที่กำหนด
void waitOkTapBeep(int beepTone) {
  waitOkTap();
  beep(beepTone);
}

// รันโหมดทดสอบตามตำแหน่ง knob (0-5) แล้วจบการทำงาน
void runTestMode(int mode) {
  switch (mode) {
    case 0: // เดินหน้า
      forwardFor(speed, TEST_DRIVE_MS);
      finishRun();
      break;
    case 1: // ถอยหลัง
      backwardFor(speed, TEST_DRIVE_MS);
      finishRun();
      break;
    case 2: // เลี้ยวซ้าย
      turnLeft();
      finishRun();
      break;
    case 3: // เลี้ยวขวา
      turnRight();
      finishRun();
      break;
    case 4: // U-Turn ซ้าย
      uTurnLeft();
      finishRun();
      break;
    case 5: // U-Turn ขวา
      uTurnRight();
      finishRun();
      break;
  }
}
