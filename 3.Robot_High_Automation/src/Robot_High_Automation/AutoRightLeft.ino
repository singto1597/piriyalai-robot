/*void AutoRightLeft() //เซ็นเซอร์&กล้อง เช็คทีละ 1 ช่อง 0:เลี้ยวขวา,1:เลี้ยวซ้าย 
{
  if(Huskylens_ReadOneID(6)==6)
  {
    if(xCenter<XrefCenter) RobotMode = 1; //วนซ้าย
    else RobotMode = 0; //วนขวา
  } 
  while(1)
  {
    Trac1Block(Speed,620);
  }
}
void Trac1Block(int TracSpeed,int Time)
{
  BaseSpeed = TracSpeed;
  InitialSpeed();
  delay(100);
  if((Huskylens_ReadOneID(7)==7)&&(width>Refwidth)) //เช็คตะเกียบ 
  {
    ForwardSpeedTime(Speed,1300); //เดินข้ามตะเกียบ
    if(RobotMode==0) TurnRight(); else TurnLeft();
  }
  if(CheckColor()==0) TracFloor(TracSpeed,Time);  //ไม่เจอสีพื้น
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracFloor(int TracSpeed,int Time)
{
  int Status=0;
  
  StartTimer();
  ForwardSpeedTime(TracSpeed,1);
  while(Status==0)
  {
    Status=TracBalance();
    if((ReadTimer()>Time)&&(Status==0)) //ไม่เจอเส้นดำ
    {
      Status = 1; 
      if(BridgeStatus==2) //ขาลง
      {
          TracSpeedTime(Speed,450); MotorStop();
          BridgeStatus = 0;
      }
      else if(BridgeStatus==1) BridgeStatus=2; //ขาเลี้ยวบนสะพาน
      if(RobotMode==0) TurnRight(); else TurnLeft(); 
    }
    if(Status>=2)
    {
      MotorStop();
      BackwardSpeedTime(Speed,230);
      MotorStop();
      if(RobotMode==0) TurnLeft(); else TurnRight();
      if(Status==4) {BackwardSpeedTime(Speed,250); MotorStop();}
    }
  }
}*/
