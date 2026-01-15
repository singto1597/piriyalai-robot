int CheckColor() //ตรวจสอบสีพื้น 1:red ,2:Yellow ,3:Blue ,4:Green ,5:White ,6:Black ,7:ตะเกียบ
{ 
  //delay(1000);
  CheckColor0();
  /*if(FloorColor>0)    //ถอยหลังและเช็คอีกรอบ
  {
    BackwardSpeedTime(Speed,130);
    MotorStop();
    delay(500);
    CheckColor0();
    //if((Huskylens_ReadOneID(6)==6)&&(height<RefHeight)&&(width>120)) FloorColor=0; //มีเส้นดำคั่น 
    ForwardSpeedTime(Speed,60);
  }*/
  if(FloorColor>0) PutBoxColor(FloorColor);
  else if(FloorColor<0) //เจอสีเดิมวางไปแล้วเปลี่ยนโหมด
  {
    UTurnLeft(); 
    RobotMode = 4-RobotMode;
    AutoLane();
  }
  return(FloorColor);
}
void CheckColor0()
{
  /*int YcenterBlack=0;
  
  /*FloorColor=0;
  if((Huskylens_ReadOneID(6)==6)&&(height<RefHeight)&&(width>120)) YcenterBlack=yCenter; //มีเส้นดำคั่น 
  if((Huskylens_ReadOneID(1)==1)&&(width>Refwidth)&&(yCenter>=YcenterBlack)&&(yCenter>20)) FloorColor=1; //สีแดง
  else if((Huskylens_ReadOneID(2)==2)&&(width>Refwidth)&&(yCenter>=YcenterBlack)&&(yCenter>20)) FloorColor=2; //สีเหลือง
  else if((Huskylens_ReadOneID(3)==3)&&(width>Refwidth)&&(yCenter>=YcenterBlack)&&(yCenter>20)) FloorColor=3; //สีน้ำเงิน
  else if((Huskylens_ReadOneID(4)==4)&&(width>Refwidth)&&(yCenter>=YcenterBlack)&&(yCenter>20)) FloorColor=4; //สีเขียว
  */
  /***FloorColor=0;
  if((Huskylens_ReadOneID(1)==1)&&(width>Refwidth)&&(yCenter<YrefCenter)&&(yCenter>20)) //สีแดง
  { if(RedNumber==0) FloorColor=1; else FloorColor=-1;} 
  else if((Huskylens_ReadOneID(2)==2)&&(width>Refwidth)&&(yCenter<YrefCenter)&&(yCenter>20)) //สีเหลือง
  { if(YellowNumber==0) FloorColor=2; else FloorColor=-1;} 
  else if((Huskylens_ReadOneID(3)==3)&&(width>Refwidth)&&(yCenter<YrefCenter)&&(yCenter>20)) //สีน้ำเงิน
  { if(BlueNumber==0) FloorColor=3; else FloorColor=-1;} 
  else if((Huskylens_ReadOneID(4)==4)&&(width>Refwidth)&&(yCenter<YrefCenter)&&(yCenter>20)) //สีเขียว
  { if(GreenNumber==0) FloorColor=4; else FloorColor=-1;} 
  */
}
void PutBoxColor(int FloorColor)
{
  ForwardSpeedTime(50,500);
  switch(FloorColor)
  {
    case 1: KickRed(); RedNumber++; break;
    case 2: KickYellow(); YellowNumber++; break;
    case 3: KickBlue(); BlueNumber++; break;
    case 4: KickGreen(); GreenNumber++; break;
  }
  if((RedNumber>0)&&(YellowNumber>0)&&(BlueNumber>0)&&(GreenNumber>0)) //ครบ 4 สียกธง
  {
    ForwardSpeedTime(50,100);
    MotorStop();
    FlagUp();
    Finish();
  } 
  ForwardSpeedTime(50,100);
  MotorStop();
  BackwardSpeedTime(50,750);
  if(RobotMode==0) TurnLeft(); else TurnRight();
}
