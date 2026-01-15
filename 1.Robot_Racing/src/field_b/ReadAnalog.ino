void ReadAnalog() { 
  L4 = analog(30);
  L3 = analog(29);
  L2 = analog(28);
  L1 = analog(27);
  R1 = analog(26);
  R2 = analog(25);
  R3 = analog(24);
  R4 = analog(18);
}

void DigitalRead() { 
  L4 = digitalRead(30);
  L3 = digitalRead(29);
  L2 = digitalRead(28);
  L1 = digitalRead(27);
  R1 = digitalRead(26);
  R2 = digitalRead(25);
  R3 = digitalRead(24);
  R4 = digitalRead(18);
}

void ShowAnalog() {
  glcdClear();
  setTextSize(1);
  ReadAnalog();
  glcd(0,0,"L4 = %d",L4);
  glcd(1,0,"L3 = %d",L3);
  glcd(2,0,"L2 = %d",L2);
  glcd(3,0,"L1 = %d",L1);
  glcd(4,0,"R1 = %d",R1);
  glcd(5,0,"R2 = %d",R2);
  glcd(6,0,"R3 = %d",R3);
  glcd(7,0,"R4 = %d",R4);
  beep();
}

void ShowDigital() {
  glcdClear();
  setTextSize(1);
  DigitalRead();
  glcd(0,0,"L4 = %d",L4);
  glcd(1,0,"L3 = %d",L3);
  glcd(2,0,"L2 = %d",L2);
  glcd(3,0,"L1 = %d",L1);
  glcd(4,0,"R1 = %d",R1);
  glcd(5,0,"R2 = %d",R2);
  glcd(6,0,"R3 = %d",R3);
  glcd(7,0,"R4 = %d",R4);
  beep();
}
