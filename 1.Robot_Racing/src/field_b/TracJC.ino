void StartTimer0()    //เริ่มจับเวลา Timer0
{
  BaseTimer0 = millis();    //อ่านเวลาปัจจุบันในหน่วย ms
  Timer0 = 0;  
}

void ReadTimer0()   //อ่านค่า Timer 0
{
  Timer0 = millis() - BaseTimer0;

  
}

void StartTimer()  {
  Timer = millis();
}
long int ReadTimer()  {
  return(millis() - Timer);
}

void CalError() {
  ReadAnalog();
  if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 > RefR4)) Error = -1;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 > RefR3) && (R4 > RefR4)) Error = -2;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 > RefR3) && (R4 < RefR4)) Error = -3;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 > RefR2) && (R3 > RefR3) && (R4 < RefR4)) Error = -4;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 > RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = -5;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 > RefR1) && (R2 > RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = -6;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 > RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = -7;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 0;
  else if ((L4 > RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 1;
  else if ((L4 > RefL4) && (L3 > RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 2;
  else if ((L4 < RefL4) && (L3 > RefL3) && (L2 < RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 3;
  else if ((L4 < RefL4) && (L3 > RefL3) && (L2 > RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 4;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 > RefL2) && (L1 < RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 5;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 > RefL2) && (L1 > RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 6;
  else if ((L4 < RefL4) && (L3 < RefL3) && (L2 < RefL2) && (L1 > RefL1) && (R1 < RefR1) && (R2 < RefR2) && (R3 < RefR3) && (R4 < RefR4)) Error = 7;
  else if ((L4 > RefL4) && (L3 > RefL3) && (L2 > RefL2) && (L1 > RefL1) && (R1 > RefR1) && (R2 > RefR2) && (R3 > RefR3) && (R4 > RefR4)) Error = 100;
  Error99Check=0;
}

void CalError2() {
  DigitalRead();
  if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 1)) Error = -1;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 1) && (R4 == 1)) Error = -2;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 1) && (R4 == 0)) Error = -3;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 1) && (R3 == 1) && (R4 == 0)) Error = -4;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 1) && (R3 == 0) && (R4 == 0)) Error = -5;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 1) && (R2 == 1) && (R3 == 0) && (R4 == 0)) Error = -6;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 1) && (R2 == 0) && (R3 == 1) && (R4 == 0)) Error = -7;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 0;
  else if ((L4 == 1) && (L3 == 0) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 1;
  else if ((L4 == 1) && (L3 == 1) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 2;
  else if ((L4 == 0) && (L3 == 1) && (L2 == 0) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 3;
  else if ((L4 == 0) && (L3 == 1) && (L2 == 1) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 4;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 1) && (L1 == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 5;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 1) && (L1 == 1) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 6;
  else if ((L4 == 0) && (L3 == 0) && (L2 == 0) && (L1 == 1) && (R1 == 0) && (R2 == 0) && (R3 == 0) && (R4 == 0)) Error = 7;
  else if ((L4 == 1) && (L3 == 1) && (L2 == 1) && (L1 == 1) && (R1 == 1) && (R2 == 1) && (R3 == 1) && (R4 == 1)) Error = 100;
  Error99Check=0;

}


void TracPID()  {
  int Output, LeftSpeed, RightSpeed, KpTemp;
  if(abs(Error)<2) KpTemp = 1; else KpTemp = Kp; 
  Output = (KpTemp*Error) + (Ki*SumError) + (Kd*(Error-PreError));
  LeftSpeed = LeftBaseSpeed + Output;
  RightSpeed = RightBaseSpeed - Output;
  if(LeftSpeed>MaxSpeed) LeftSpeed = MaxSpeed;
  else if(LeftSpeed<0) LeftSpeed = -MaxSpeed;//new pid
  if(RightSpeed>MaxSpeed) RightSpeed = MaxSpeed;
  else if(RightSpeed<0) RightSpeed = -MaxSpeed;//new pid
  motor(1,LeftSpeed); 
  motor(2,RightSpeed);
  PreError = Error;
  SumError += Error;
}


void TracJCStop() 
{  
  InitialSpeed();
  //TracSpeedTime(BaseSpeed,5000/BaseSpeed);
  CalError2();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalError2();
    }
  }
  //LR = 0;
}
/*void TracJC() 
{
  TracJCStop();
  Forward();
  if(BaseSpeed<=60)
  {
     while(Error>=100)
    {
      CalError2();
    }
    delay(2000/BaseSpeed);
  }
  else if(BaseSpeed<=65) delay(4500/BaseSpeed); 
  else if(BaseSpeed<=70) delay(4000/BaseSpeed); 
  else if(BaseSpeed<=80) delay(2500/BaseSpeed);
  else if(BaseSpeed<=90) delay(1000/BaseSpeed);
  //else  delay(500/BaseSpeed);
}*/

void TracJC() 
{
  TracJCStop();
  Forward();
  if(BaseSpeed<=60)
  {
     while(Error>=100)
    {
      CalError2();
    }
    delay(500/BaseSpeed);
  }
}

void TracJCSpeedTime(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStop();
  Forward();
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeed() 
{
  BaseSpeed = ACCSpeed;
  TracJCStop();
  Forward();
  while(Error>=100)
  {
    CalError2();
  }
  delay(5000/BaseSpeed);
  BaseSpeed = Speed;
  InitialSpeed();
}

void TracPIDTimer(int TracSpeed, int TracTime) {
  BaseSpeed = TracSpeed;
  InitialSpeed();
  StartTimer();
  CalError2();
  while(ReadTimer()<TracTime)
  {
    TracPID();
    delay(Kt);
    CalError2();
  }
  BaseSpeed = Speed;
  InitialSpeed();
}

void TurnLeft()   //เลี้ยวซ้าย
{
  MotorStop();
  sl(TurnSpeed);
  delay(350);
  MotorStop();
}
void TurnRight()   //เลี้ยวขวา
{
  MotorStop();
  sr(TurnSpeed);
  delay(350);
  MotorStop();
}
