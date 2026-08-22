// Driver_RgbSensor.ino
// ฮาร์ดแวร์เซนเซอร์สี TCS34725: เริ่มต้น + อ่านค่าสีดิบเป็น RGB565
// (การจำแนกสีพื้นเป็นสีอะไร อยู่ใน Logics_ColorDetection.ino)
// (เกน/เวลา integration/ดีเลย์ อยู่ใน config.h)

// แปลง RGB (0-255) เป็นสี 16 บิตแบบ RGB565 (ใช้เทียบกับค่าอ้างอิงสี)
static uint16_t rgbTo565(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t color;
  color = (uint16_t)(r & 0xF8) << 8;
  color |= (uint16_t)(g & 0xFC) << 3;
  color |= (uint16_t)(b & 0xF8) >> 3;
  return color;
}

// เริ่มต้น RGB sensor และตรวจสอบว่าเจอเซนเซอร์หรือไม่
void initColorSensor() {
  delay(COLOR_POWERON_DELAY_MS);
  Serial.begin(SERIAL_BAUD);
  oled.text(0, 0, "Color Sensor Test!");
  if (tcs.begin()) {
    oled.text(1, 0, "Found sensor!");
  } else {
    oled.text(1, 0, "No TCS34725 found!");
  }
  oled.show();
  tcs.setIntegrationTime(COLOR_OPERATING_INTEGRATION_TIME);
  tcs.setGain(COLOR_GAIN);
}

// อ่านค่าสีแล้วแปลงเป็น RGB565 (ค่าที่ใช้เทียบกับ ref สี)
uint16_t readRgbColor() {
  uint16_t clear, red, green, blue;

  delay(COLOR_READ_DELAY_MS);   // รอให้ TCS34725 อ่านเสร็จ (~50ms)
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
