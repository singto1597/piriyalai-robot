void initSystem() {
  for (int pins = 4; pins <= 7; pins++) {
    pinMode(pins, OUTPUT);
    digitalWrite(pins, LOW);
  }
}


void motorControl(int speedLeft, int speedRight) {
  bool LD, RD;
  LD = (speedLeft >= 0 ? false : true);
  RD = (speedRight >= 0 ? false : true);
  speedLeft = abs(speedLeft);
  speedRight = abs(speedRight);
  digitalWrite(dirA, LD);           //digital(5,LOW)    LOW =  เดินหน้า   HIGHT =  ถอยหลัง, 0 LOW False,  1 HIGHT True
  analogWrite(pwmA, speedLeft);
  digitalWrite(dirB, RD);
  analogWrite(pwmB, speedRight);

}


void readSensor() {
  glcd(0, 0, "READING..");
  beep();
  for (int i = 0; i < 500; i++) {
    qtr.calibrate();
    delay(10);
  }
  beep();
  glcdClear();
  for (int i = 0; i < 8; i++) {
    glcd(i, 0, "%d", qtr.calibratedMinimumOn[i]);
    glcd(i, 8, "%d", qtr.calibratedMaximumOn[i]);
  }
}

void showSensor() {
  glcdClear();
  beep();

  while (1) {
    // อ่านค่าจาก QTR ทั้ง 8 เซ็นเซอร์
    unsigned int sensorValues[8];
    qtr.read(sensorValues);

    // เคลียร์บรรทัดเก่า
    glcdClear();

    // โชว์ค่าบน GLCD
    for (int i = 0; i < 8; i++) {
      glcd(i * 6, 0, "%4d", sensorValues[i]); // ค่าดิบ
    }

    // ถ้ากดปุ่ม SWITCH ให้หยุดแสดง
    if (!digitalRead(SWITCH)) {
      beep();
      break;
    }

    delay(50); // หน่วงนิดเพื่อให้จออ่านง่าย
  }
}

void testMotor() {
  glcdClear();
  glcd(0, 0, "Motor Test Ready");

  // รอให้กดปุ่มเริ่ม
  while (digitalRead(SWITCH) == HIGH) {
    // รอจนปุ่มถูกกด
  }
  beep();

  // === ทดสอบล้อซ้าย ===
  glcdClear();
  glcd(0, 0, "Left FWD");
  motorControl(120, 0); // ล้อซ้ายเดินหน้า
  delay(1000);

  motorControl(0, 0); // หยุด
  beep();
  delay(300);

  glcdClear();
  glcd(0, 0, "Left REV");
  motorControl(-120, 0); // ล้อซ้ายถอยหลัง
  delay(1000);

  motorControl(0, 0);
  beep();
  delay(500);

  // === ทดสอบล้อขวา ===
  glcdClear();
  glcd(0, 0, "Right FWD");
  motorControl(0, 120); // ล้อขวาเดินหน้า
  delay(1000);

  motorControl(0, 0);
  beep();
  delay(300);

  glcdClear();
  glcd(0, 0, "Right REV");
  motorControl(0, -120); // ล้อขวาถอยหลัง
  delay(1000);

  motorControl(0, 0);
  beep();
  delay(500);

  // === วิ่งตรง ===
  glcdClear();
  glcd(0, 0, "Forward");
  motorControl(120, 120);
  delay(1000);

  motorControl(0, 0);
  beep();
  delay(300);

  // === ถอยหลัง ===
  glcdClear();
  glcd(0, 0, "Reverse");
  motorControl(-120, -120);
  delay(1000);

  motorControl(0, 0);
  beep();

  glcdClear();
  glcd(0, 0, "Test Done");
}


void setValueQTR() {
  qtr.calibrate();
  for (int i = 0; i < 8; i++) {
    qtr.calibratedMinimumOn[i] = minValue[i];
    qtr.calibratedMaximumOn[i] = maxValue[i];
  }
}

void viewPos() {
  Serial.begin(9600);

  //1 == true
  while (1) {
    Position = qtr.readLine(sensorValue, QTR_EMITTERS_ON, 0, 0, 200, 50); // 0  ตัวแ แรกคือสีขาว
    Serial.println(Position);
    delay(100);
    
  }
}

void stdPID(int baseSpeed, float Kp, float Kd) {
  Position = qtr.readLine(sensorValue, QTR_EMITTERS_ON, 0, 0, 200, 50);
  error = Position - 3500;
  pidValue = (Kp * error) + (Kd * (error - lastError));   //error  คือ  ปัจจุบัน  และจะกลายเป็น last error ในรอบต่อไป
  lastError = error;
  
  if (pidValue > baseSpeed) pidValue = baseSpeed;
  if (pidValue < -baseSpeed) pidValue = -baseSpeed;
  leftValue = baseSpeed + pidValue;
  rightValue = baseSpeed - pidValue;
  if (leftValue > 255) leftValue = 255;
  if (leftValue < 10) leftValue = -170;
  if (rightValue > 255) rightValue = 255;
  if (rightValue < 10) rightValue = -170;
  motorControl(leftValue, rightValue);

}


void PidTimer(int baseSpeed, float Kp, float Kd, int Timer, int turnN) {
  
  LastTime = millis();
  
  while ((millis() - LastTime) <= Timer) {
    Position = qtr.readLine(sensorValue, QTR_EMITTERS_ON, 0, 0, 200, 50);
    
    error = Position - 3500;
    pidValue = (Kp * error) + (Kd * (error - lastError));   //error  คือ  ปัจจุบัน  และจะกลายเป็น last error ในรอบต่อไป
    lastError = error;
    
    if (pidValue > baseSpeed) pidValue = baseSpeed;
    if (pidValue < -baseSpeed) pidValue = -baseSpeed;
    
    leftValue = baseSpeed + pidValue;
    rightValue = baseSpeed - pidValue;
    
    if (leftValue > 255) leftValue = 255;
    if (leftValue < 10) leftValue = -170;
    if (rightValue > 255) rightValue = 255;
    if (rightValue < 10) rightValue = -170;
    motorControl(leftValue, rightValue);
  }
}

void Stop(int a) {
  motor_stop(ALL);
  delay(a);
}
