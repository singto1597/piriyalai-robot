/*void CalErrorCamera() //คำนวณ Error วิ่งตามช่องโดยใช้กล้อง -:ซ้าย ,+:ขวา
{
  if((Huskylens_ReadOneID(6)==6)&&(height>40)) //เจอเส้นสีดำ
  {
    if(xCenter>XrefCenter) Error = (xCenter-300)/2; //เส้นอยู่ทางขวา
    else Error = (xCenter)/4; //เส้นอยู่ทางซ้าย
    //else Error = 35; //เส้นอยู่ทางซ้าย
  }
  //else Error = 35;
}
void AutoCamera()   //วิ่งตามช่องใช้กล้องอย่างเดียว
{
  MaxSpeed = BaseSpeed;
  Ki = 0;
  Error = 0;
  PreError = 0;
  Kp = 2;       //forward PID
  Kd = 25;
  while(1)
  {
    if(Huskylens_ReadOneID(6)==6) //เจอเส้นสีดำ
    {
      if((width>120)&&(height<80))  //เจอเส้นดำตัด
      {
        ForwardSpeedTime(SlowSpeed,1);
        while(yCenter<100)
        {
          Huskylens_ReadOneID(6);
        }
        delay(150);
        TurnRight();
        BackwardSpeedTime(SlowSpeed,200);
        MotorStop();
        if((Huskylens_ReadOneID(6)==6)&&(width>XrefCenter+20)&&(height<80)&&(yCenter>100))  //เจอเส้นดำตัด
        {
          ForwardSpeedTime(SlowSpeed,200);
          UTurnRight();
          BackwardSpeedTime(SlowSpeed,200);
          MotorStop();
          if((Huskylens_ReadOneID(6)==6)&&(width>XrefCenter+20)&&(height<80)&&(yCenter>100))  //เจอเส้นดำตัด
          {
            ForwardSpeedTime(SlowSpeed,200);
            TurnLeft();
          }
          else  //เจอช่องว่าง
          {
            ForwardSpeedTime(Speed,300);
          }
        }
        else    //เจอช่องว่าง
        {
          ForwardSpeedTime(Speed,300); 
        }
      }
    }
    CalErrorCamera();
    TracPID();
  }
}*/
