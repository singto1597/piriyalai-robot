#define BrakeSpeed 100
#define BrakeTime 30

void TurnLeft() {
    MotorStop();
    if(WheelDrive==0) sl(TurnSpeed);
    else SL(TurnSpeed);
    delay(3000/TurnSpeed);
    if(TurnSpeed>90)
    {
      if(WheelDrive==0) sl(90);
      else SL(90);
    }
    ConvertADC();
    if(TurnSpeed<=40) 
    {
      while((C==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=50) 
    {
      while((L1==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=60) 
    {
      while((L2==1)) {ConvertADC();}
    }
    else  
    {
      while((L3==1)) {ConvertADC();}
    }
    if((BrakeTime>0)&&(TurnSpeed>70)) Right(BrakeSpeed,BrakeTime);
    else  MotorStop();
}
void TurnRight() {
    MotorStop();
    if(WheelDrive==0) sr(TurnSpeed);
    else SR(TurnSpeed);
    delay(3000/TurnSpeed);
    if(TurnSpeed>90)
    {
      if(WheelDrive==0) sr(90);
      else SR(90);
    }
    ConvertADC();
    if(TurnSpeed<=40) 
    {
      while((C==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=50) 
    {
      while((R1==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=60) 
    {
      while((R2==1)) {ConvertADC();}
    }
    else 
    {
      while((R3==1)) {ConvertADC();}
    }
    if((BrakeTime>0)&&(TurnSpeed>70)) Left(BrakeSpeed,BrakeTime);
    else  MotorStop();
}
void UTurnLeft() {
    MotorStop();
    if(WheelDrive==0) sl(TurnSpeed);
    else SL(TurnSpeed);
    delay(20000/TurnSpeed); 
    if(TurnSpeed>70)
    {
      if(WheelDrive==0) sl(60);
      else SL(60);
    }
    ConvertADC();
    if(TurnSpeed<=40) 
    {
      while((C==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=50) 
    {
      while((L1==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=60) 
    {
      while((L2==1)) {ConvertADC();}
    }
    else 
    {
      while((L3==1)) {ConvertADC();}
    }
    if((BrakeTime>0)&&(TurnSpeed>70)) Right(BrakeSpeed,BrakeTime);
    else  MotorStop();
}
void UTurnRight() {
    MotorStop();
    if(WheelDrive==0) sr(TurnSpeed);
    else SR(TurnSpeed);
    delay(20000/TurnSpeed);
    if(TurnSpeed>70)
    {
      if(WheelDrive==0) sr(60);
      else SR(60);
    } 
    ConvertADC();
    if(TurnSpeed<=40) 
    {
      while((C==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=50) 
    {
      while((R1==1)) {ConvertADC();}
    }
    else if(TurnSpeed<=60) 
    {
      while((R2==1)) {ConvertADC();}
    }
    else 
    {
      while((R3==1)) {ConvertADC();}
    }
    if((BrakeTime>0)&&(TurnSpeed>70)) Left(BrakeSpeed,BrakeTime);
    else  MotorStop();
}

void Left(int Speed , int Time){
  MotorStop();
  if(WheelDrive==0) sl(Speed);
  else SL(Speed);
  delay(Time);
  MotorStop();
}
void Right(int Speed , int Time){
  MotorStop();
  if(WheelDrive==0) sr(Speed);
  else SR(Speed);
  delay(Time);
  MotorStop();
}
void TurnLeftDelay(int Speed , int Time){
  if(WheelDrive==0) tl(Speed);
  else TL(Speed);
  delay(Time);
}
void TurnRightDelay(int Speed , int Time){
  if(WheelDrive==0) tr(Speed);
  else TR(Speed);
  delay(Time);
}
void CurveRight(int MotorSpeed,int Time)  //โค้งทางขวาอ้อมสิ่งกีดขวาง
{
  MotorStop();
  Right(MotorSpeed,130);
  if(WheelDrive==0) fd2(MotorSpeed*0.58,MotorSpeed);
  else FD2(MotorSpeed*0.58,MotorSpeed);
  delay(900);
  ConvertADC();
  while(L1==0) {ConvertADC();}
  while(L1==1) {ConvertADC();}
  //ForwardSpeedTime(MotorSpeed,Time);
  delay(Time);
  TurnRight(); 
}
void CurveLeft(int MotorSpeed,int Time)  //โค้งทางซ้ายอ้อมสิ่งกีดขวาง
{
  MotorStop();
  Left(MotorSpeed,130);
  if(WheelDrive==0) fd2(MotorSpeed,MotorSpeed*0.58);
  else FD2(MotorSpeed,MotorSpeed*0.58);
  delay(900);
  ConvertADC();
  while(R1==0) {ConvertADC();}
  while(R1==1) {ConvertADC();}
  //ForwardSpeedTime(MotorSpeed,Time);
  delay(Time);
  TurnLeft(); 
}
