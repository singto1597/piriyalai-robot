// line_follow_pid.ino
// แปลงค่าดิบจากเซนเซอร์เส้นเป็นค่า 0/1 และคำนวณ PID สำหรับเดินตามเส้น

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

// คำนวณ error ของเส้นตามตำแหน่งเส้นที่เจอ:
// 0 = อยู่ตรงกลาง, + = เบนไปขวา, - = เบนไปซ้าย, 100 = เจอเส้นดำตรงกลาง (แยก)
void updateLineError() {
  updateLineBinary();
  if (sensorC == 0) lineError = 100;
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

// PID เดินตามเส้น: ปรับความเร็วล้อซ้าย/ขวาตาม error แล้วสั่งมอเตอร์ทั้ง 4 ล้อ
void followLinePid() {
  int output, leftOutput, rightOutput;

  output = (kp * lineError) + (ki * integral) + (kd * (lineError - prevLineError));
  leftOutput = leftBaseSpeed + output;
  rightOutput = rightBaseSpeed - output;
  if (leftOutput > maxSpeed) leftOutput = maxSpeed;
  else if (leftOutput < -maxSpeed) leftOutput = -maxSpeed;
  if (rightOutput > maxSpeed) rightOutput = maxSpeed;
  else if (rightOutput < -maxSpeed) rightOutput = -maxSpeed;
  motor(1, leftOutput);
  motor(2, leftOutput);
  motor(3, rightOutput);
  motor(4, rightOutput);
  prevLineError = lineError;
  integral += lineError;
}

// แปลงเซนเซอร์หลัง: 0 = เจอเส้นดำ, 1 = พื้นขาว
void updateBackLineBinary() {
  readBackLineSensors();
  if (backL < refBackL) backL = 0; else backL = 1;
  if (backR < refBackR) backR = 0; else backR = 1;
}
