// input_buttons.ino
// อ่านปุ่ม OK และโหมดทดสอบที่เลือกจาก knob ตอนเริ่มทำงาน

// เช็คว่ากดปุ่ม OK ค้างอยู่หรือไม่
bool isOkPressed() {
  if (SW_OK()) return true;
  else return false;
}

// รอจนกว่าจะปล่อยปุ่ม OK
void waitOkRelease() {
  while (isOkPressed()) { delay(10); }
}

// รอจนกว่าจะกดปุ่ม OK
void waitOkPress() {
  while (isOkPressed() == false) { delay(10); }
}

// รันโหมดทดสอบตามตำแหน่ง knob (0-5) แล้วจบการทำงาน
void runTestMode(int mode) {
  switch (mode) {
    case 0: // เดินหน้า
      forwardFor(speed, 1600);
      finishRun();
      break;
    case 1: // ถอยหลัง
      backwardFor(speed, 1600);
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
