// Logics_FinishRun.ino
// Logic จบการวิ่ง: หยุดรถ แสดงเวลารวม + โหมด + จำนวนลูกบาศก์บนจอ แล้วค้างหน้าจอไว้

void finishRun() {
  long int runningTime;
  runningTime = stopwatchElapsed2();
  AO();
  beep(200);
  drawFinishScreen(runningTime);
  while (1) {}   // ค้างหน้าจอ (ปิดเครื่องเพื่อเริ่มใหม่)
}
