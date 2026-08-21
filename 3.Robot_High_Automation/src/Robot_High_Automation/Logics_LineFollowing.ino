// Logics_LineFollowing.ino
// แปลงค่าดิบจากเซนเซอร์เส้นเป็นค่า 0/1 และคำนวณ PID สำหรับเดินตามเส้น
// (การอ่านเซนเซอร์ อยู่ใน Driver_ReadSensor.ino; เกน PID อยู่ใน config.h)

// แปลงเซนเซอร์หน้า: 0 = เจอเส้นดำ, 1 = พื้นขาว
void updateLineBinary() {
  readLineSensors();
  if (sensorL3 < refL3) sensorL3 = 0; else sensorL3 = 1;
  if (sensorL2 < refL2) sensorL2 = 0; else sensorL2 = 1;
  if (sensorL1 < refL1) sensorL1 = 0; else sensorL1 = 1;
  if (sensorC  < refC)  sensorC  = 0; else sensorC  = 1;
  if (sensorR1 < refR1) sensorR1 = 0; else sensorR1 = 1;
  if (sensorR2 < refR2) sensorR2 = 0; else sensorR2 = 1;
  if (sensorR3 < refR3) sensorR3 = 0; else sensorR3 = 1;
}

// คำนวณ error ของเส้นตามตำแหน่งเส้นที่เจอ:   (ตารางนี้คืออัลกอริทึม — ห้ามแก้)
// 0 = อยู่ตรงกลาง, + = เบนไปขวา, - = เบนไปซ้าย, LINE_ERROR_CENTER = เจอเส้นดำตรงกลาง (แยก)
void updateLineError() {
  updateLineBinary();
  if (sensorC == 0) lineError = LINE_ERROR_CENTER;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==0)) lineError = -1;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==0)&&(sensorR3==0)) lineError = -2;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==0)&&(sensorR3==1)) lineError = -3;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==0)&&(sensorR2==0)&&(sensorR3==1)) lineError = -4;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==0)&&(sensorR2==1)&&(sensorR3==1)) lineError = -5;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==1)) lineError = 0;
  else if ((sensorL3==1)&&(sensorL2==1)&&(sensorL1==0)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==1)) lineError = 5;
  else if ((sensorL3==1)&&(sensorL2==0)&&(sensorL1==0)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==1)) lineError = 4;
  else if ((sensorL3==1)&&(sensorL2==0)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==1)) lineError = 3;
  else if ((sensorL3==0)&&(sensorL2==0)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==1)) lineError = 2;
  else if ((sensorL3==0)&&(sensorL2==1)&&(sensorL1==1)&&(sensorC==1)&&(sensorR1==1)&&(sensorR2==1)&&(sensorR3==1)) lineError = 1;
}

// จำกัดค่าให้อยู่ในช่วง -maxSpeed..maxSpeed (กัน PID สั่งมอเตอร์เกินกำลัง)
int clampOutput(int value) {
  if (value > maxSpeed) return maxSpeed;
  if (value < -maxSpeed) return -maxSpeed;
  return value;
}

// PID เดินตามเส้น: ปรับความเร็วล้อซ้าย/ขวาตาม error แล้วสั่งมอเตอร์ทั้ง 4 ล้อ
void followLinePid() {
  int output = (kp * lineError) + (ki * integral) + (kd * (lineError - prevLineError));
  int leftOutput  = clampOutput(leftBaseSpeed + output);
  int rightOutput = clampOutput(rightBaseSpeed - output);

  motor(MOTOR_CH_LEFT_1, leftOutput);
  motor(MOTOR_CH_LEFT_2, leftOutput);
  motor(MOTOR_CH_RIGHT_1, rightOutput);
  motor(MOTOR_CH_RIGHT_2, rightOutput);
  prevLineError = lineError;
  integral += lineError;
}

// แปลงเซนเซอร์หลัง: 0 = เจอเส้นดำ, 1 = พื้นขาว
void updateBackLineBinary() {
  readBackLineSensors();
  if (backL < refBackL) backL = 0; else backL = 1;
  if (backR < refBackR) backR = 0; else backR = 1;
}
