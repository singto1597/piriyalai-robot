// rgb_sensor.ino
// เซนเซอร์สี TCS34725: เริ่มต้น อ่านค่าสี แล้วจำแนกว่าพื้นเป็นสีอะไร

// เริ่มต้น RGB sensor และตรวจสอบว่าเจอเซนเซอร์หรือไม่
void initColorSensor() {
  delay(100);
  Serial.begin(115200);
  oled.text(0, 0, "Color Sensor Test!");
  if (tcs.begin()) {
    oled.text(1, 0, "Found sensor!");
  } else {
    oled.text(1, 0, "No TCS34725 found!");
  }
  oled.show();
  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
  tcs.setGain(TCS34725_GAIN_4X);
}

// อ่านค่าสีแล้วแปลงเป็น RGB565 (ค่าที่ใช้เทียบกับ ref สี)
uint16_t readRgbColor() {
  uint16_t clear, red, green, blue;

  delay(60);   // ใช้เวลาอ่าน ~50ms
  tcs.getRawData(&red, &green, &blue, &clear);

  // คำนวณสัดส่วนสีแต่ละตัว เทียบกับค่า clear แล้วปรับขนาดเป็น 0-255
  uint32_t sum = clear;
  float r, g, b;
  r = red;    r /= sum;
  g = green;  g /= sum;
  b = blue;   b /= sum;
  r *= 256; g *= 256; b *= 256;

  return rgbTo565((int)r, (int)g, (int)b);
}

// แสดงค่าสีปัจจุบันบนหน้าจอ
void showColorValue() {
  int colorRgb = readRgbColor();
  oled.clear();
  oled.text(0, 0, "Color=%d    ", colorRgb);
  oled.show();
}

// จำแนกสีพื้นตามโหมด RGB_MODE (0 = เทียบช่วงคงที่, 1 = เทียบลำดับอัตโนมัติ)
int detectFloorColor() {
  if (RGB_MODE == 0) return detectFloorColorByRange();
  else return detectFloorColorByRank();
}

// จำแนกสีแบบเทียบกับช่วง +-500 จากค่าอ้างอิงคงที่ของแต่ละสี
int detectFloorColorByRange() {
  long colorRgb = readRgbColor();
  if (colorRgb < (refBlue + 500) && colorRgb > (refBlue - 500)) {
    floorColor = Blue;      // น้ำเงิน
  }
  else if (colorRgb < (refGreen + 500) && colorRgb > (refGreen - 500)) {
    floorColor = Green;     // เขียว
  }
  else if (colorRgb < (refBlack + refWhite) / 2) {
    floorColor = Black;     // ดำ
  }
  else if (colorRgb < (refWhite + refYellow) / 2) {
    floorColor = White;     // ขาว
  }
  else if (colorRgb < (refYellow + refRed) / 2) {
    floorColor = Yellow;    // เหลือง
  }
  else {
    floorColor = Red;       // แดง
  }
  return floorColor;
}

// คำนวณลำดับ (rank) ของค่าอ้างอิงสีทั้ง 6: ค่ามากสุดได้ rank 5, น้อยสุดได้ 0
void rankColorRefs() {
  int rank;

  rank = 0;   // Blue
  colorRank[rank] = 0;
  if (refBlue > refGreen)  colorRank[rank]++;
  if (refBlue > refBlack)  colorRank[rank]++;
  if (refBlue > refWhite)  colorRank[rank]++;
  if (refBlue > refYellow) colorRank[rank]++;
  if (refBlue > refRed)    colorRank[rank]++;

  rank = 1;   // Green
  colorRank[rank] = 0;
  if (refGreen > refBlue)  colorRank[rank]++;
  if (refGreen > refBlack) colorRank[rank]++;
  if (refGreen > refWhite) colorRank[rank]++;
  if (refGreen > refYellow) colorRank[rank]++;
  if (refGreen > refRed)   colorRank[rank]++;

  rank = 2;   // Black
  colorRank[rank] = 0;
  if (refBlack > refBlue)  colorRank[rank]++;
  if (refBlack > refGreen) colorRank[rank]++;
  if (refBlack > refWhite) colorRank[rank]++;
  if (refBlack > refYellow) colorRank[rank]++;
  if (refBlack > refRed)   colorRank[rank]++;

  rank = 3;   // White
  colorRank[rank] = 0;
  if (refWhite > refBlue)  colorRank[rank]++;
  if (refWhite > refGreen) colorRank[rank]++;
  if (refWhite > refBlack) colorRank[rank]++;
  if (refWhite > refYellow) colorRank[rank]++;
  if (refWhite > refRed)   colorRank[rank]++;

  rank = 4;   // Yellow
  colorRank[rank] = 0;
  if (refYellow > refBlue)  colorRank[rank]++;
  if (refYellow > refGreen) colorRank[rank]++;
  if (refYellow > refBlack) colorRank[rank]++;
  if (refYellow > refWhite) colorRank[rank]++;
  if (refYellow > refRed)   colorRank[rank]++;

  rank = 5;   // Red
  colorRank[rank] = 0;
  if (refRed > refBlue)  colorRank[rank]++;
  if (refRed > refGreen) colorRank[rank]++;
  if (refRed > refBlack) colorRank[rank]++;
  if (refRed > refWhite) colorRank[rank]++;
  // หมายเหตุ: เดิมเขียน `if(RefRed>Yellow)` (Yellow = ค่าคงที่ 4) ไม่ใช่ `RefYellow`
  // คงพฤติกรรมเดิมไว้ตามที่กำหนด
  if (refRed > Yellow) colorRank[rank]++;
}

// จำแนกสีโดยใช้ลำดับของค่าอ้างอิง (ค่าสีไม่จำเป็นต้องเรียงกัน)
// หาขอบเขตล่าง/บนของช่วงที่ค่าที่อ่านได้ตกลง แล้วเทียบกับค่ากลางของช่วง
int detectFloorColorByRank() {
  int i, colorMin, colorMax;
  long refMin, refMax;
  long colorRgb = readRgbColor();

  rankColorRefs();
  for (i = 0; i < 5; i++) {
    // หาสีที่ rank == i (ขอบล่าง)
    if (colorRank[0] == i) { refMin = refBlue;  colorMin = Blue; }
    else if (colorRank[1] == i) { refMin = refGreen;  colorMin = Green; }
    else if (colorRank[2] == i) { refMin = refBlack;  colorMin = Black; }
    else if (colorRank[3] == i) { refMin = refWhite;  colorMin = White; }
    else if (colorRank[4] == i) { refMin = refYellow; colorMin = Yellow; }
    else if (colorRank[5] == i) { refMin = refRed;    colorMin = Red; }

    // หาสีที่ rank == i+1 (ขอบบน)
    if (colorRank[0] == i + 1) { refMax = refBlue;  colorMax = Blue; }
    else if (colorRank[1] == i + 1) { refMax = refGreen;  colorMax = Green; }
    else if (colorRank[2] == i + 1) { refMax = refBlack;  colorMax = Black; }
    else if (colorRank[3] == i + 1) { refMax = refWhite;  colorMax = White; }
    else if (colorRank[4] == i + 1) { refMax = refYellow; colorMax = Yellow; }
    else if (colorRank[5] == i + 1) { refMax = refRed;    colorMax = Red; }

    floorColor = colorMin;
    if (colorRgb < (refMin + refMax) / 2) return floorColor;
  }
  floorColor = colorMax;
  return floorColor;
}
