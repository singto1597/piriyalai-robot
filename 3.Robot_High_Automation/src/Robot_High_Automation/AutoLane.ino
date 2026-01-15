#define ColorYcenter 70

void AutoLane()  //เซ็นเซอร์&กล้อง วิ่งตรงยาว 3:เลี้ยวขวา 4:เลี้ยวซ้าย
{
 /* int Status;
  if(Huskylens_ReadOneID(6)==6)
  {
    if(xCenter<XrefCenter) RobotMode = 4; //วนซ้าย
    else RobotMode = 3; //วนขวา
  }  
  while(1)
  {
    Status = 0;
    ForwardSpeedTime(Speed,1);
    while(Status==0)  //ทางหลัก
    {
      if((Huskylens_ReadOneID(7)==7)&&(width>Refwidth)&&(yCenter>YrefCenter)) //เช็คตะเกียบ 
      {
        ForwardSpeedTime(Speed,800);  //เดินข้ามตะเกียบ
      }
      if(ColorCheck==0)
      {
        CheckColorLane();
        if(FloorColor>0) PutBoxColorLane(FloorColor);
        else if(FloorColor==-1) //สีเดิมวางไปแล้ว
        { 
          if(RobotMode==4) UTurnLeft(); else UTurnRight();
          BackwardBalance(400);
          //RobotMode = 4-RobotMode; //วนตรงข้ามจากเดิม
          RobotMode = RobotMode-3;  //วนทางเดิมแต่ทีละช่อง
          AutoRightLeft();
        }
      }
      Status=TracBalance();
      if(Status==2) //เจอเส้นดำทางแยก
      {
        ColorCheck=0;
        MotorStop();
        BackwardSpeedTime(Speed,230);
        if(RobotMode==3) TurnRight(); else TurnLeft();
        BackwardBalance(400); 
        if(TracLane1Block(Speed,600)==2)  //ขวาเจอทางตันให้กลับหลังหัน
        {
          MotorStop();
          BackwardSpeedTime(Speed,230);
          if(RobotMode==3) UTurnRight(); else UTurnLeft();
          BackwardBalance(400);
          if(TracLane1Block(Speed,600)==2)  //ขวาเจอทางตันด้านที่ 3 ให้ย้อนกลับ
          {
            MotorStop();
            BackwardSpeedTime(Speed,230);
            if(RobotMode==3) TurnLeft(); else TurnRight();
            BackwardBalance(400);
          }
        }
      }
    }   

    
  }
  */
}
int TracLane1Block(int TracSpeed,int Time)
{
  int Status=0;
  
  StartTimer();
  ForwardSpeedTime(TracSpeed,1);
  while(Status==0)
  {
    CheckLimitSwitch();
    CalError();
    if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      AO(); 
      motor(1,-SlowSpeed); motor(2,-SlowSpeed);
      motor(3,SlowSpeed); motor(4,SlowSpeed);
      while(R3==1) {ConvertADC();}
      delay(50);
      Status = 2;
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      AO(); 
      motor(1,SlowSpeed); motor(2,SlowSpeed);
      motor(3,-SlowSpeed); motor(4,-SlowSpeed);
      while(L3==1) {ConvertADC();}
      delay(50);
      Status = 2;
    }
    else if(C==0)  //เจอดำตรงกลาง
    {
      Status = 2;
    }
    else if(ReadTimer()>Time) //ไม่เจอเส้นดำ
    {
      Status = 1; 
    }
    else TracPID();
  }
  return(Status);
}
/*void CheckColorLane()
{
  int YcenterColor;
  FloorColor=0;
  if((Huskylens_ReadOneID(1)==1)&&(width>Refwidth)&&(yCenter>ColorYcenter)) //สีแดง
  { 
    YcenterColor = yCenter;
    MotorStop(); delay(100);
    if((Huskylens_ReadOneID(6)==6)&&(height<RefHeight)&&(width>120)&&(yCenter>YcenterColor)) ColorCheck=1; //มีเส้นดำคั่น
    else if(RedNumber==0) FloorColor=1; else FloorColor=-1;
  } 
  else if((Huskylens_ReadOneID(2)==2)&&(width>Refwidth)&&(yCenter>ColorYcenter)) //สีเหลือง
  { 
    YcenterColor = yCenter;
    MotorStop(); delay(100);
    if((Huskylens_ReadOneID(6)==6)&&(height<RefHeight)&&(width>120)&&(yCenter>YcenterColor)) ColorCheck=1; //มีเส้นดำคั่น
    else if(YellowNumber==0) FloorColor=2; else FloorColor=-1;
  } 
  else if((Huskylens_ReadOneID(3)==3)&&(width>Refwidth)&&(yCenter>ColorYcenter)) //สีน้ำเงิน
  {     
    YcenterColor = yCenter;
    MotorStop(); delay(100);
    if((Huskylens_ReadOneID(6)==6)&&(height<RefHeight)&&(width>120)&&(yCenter>YcenterColor)) ColorCheck=1; //มีเส้นดำคั่น
    else if(BlueNumber==0) FloorColor=3; else FloorColor=-1;
  } 
  else if((Huskylens_ReadOneID(4)==4)&&(width>Refwidth)&&(yCenter>ColorYcenter)) //สีเขียว
  {     
    YcenterColor = yCenter;
    MotorStop(); delay(100);
    if((Huskylens_ReadOneID(6)==6)&&(height<RefHeight)&&(width>120)&&(yCenter>YcenterColor)) ColorCheck=1; //มีเส้นดำคั่น
    else if(GreenNumber==0) FloorColor=4; else FloorColor=-1;
  } 
}
void PutBoxColorLane(int FloorColor)
{ 
  ForwardSpeedTime(50,200);
  switch(FloorColor)
  {
    case 1: KickRed(); RedNumber++; break;
    case 2: KickYellow(); YellowNumber++; break;
    case 3: KickBlue(); BlueNumber++; break;
    case 4: KickGreen(); GreenNumber++; break;
  }
  if((RedNumber>0)&&(YellowNumber>0)&&(BlueNumber>0)&&(GreenNumber>0)) //ครบ 4 สียกธง
  {
    FlagUp();
    Finish();
  } 
  BackwardSpeedTime(50,200); 
  if(RobotMode==4) UTurnLeft(); else UTurnRight();
  BackwardBalance(300);
}*/
