// Logics_FinishRun.ino
// Logic จบการวิ่ง: หยุดรถ แสดงเวลารวมบนจอ แล้วค้างหน้าจอไว้

void finishRun() {
  long int runningTime;
  runningTime = stopwatchElapsed2();
  AO();
  beep(200);
  oled.clear();
  oled.textSize(1);
  oled.text(0, 0, "   Finish.   ");
  oled.text(2, 0, "Running Time.");
  oled.text(4, 0, "%l.%l seconds", runningTime / 1000, runningTime % 1000);
  oled.show();
  while (1) {}
}
