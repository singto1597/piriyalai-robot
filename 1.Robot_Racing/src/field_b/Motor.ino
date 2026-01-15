void RobotStart() 
{
  fd2(50, 50);
  delay(100);
  //ForwardSpeedTime(50,100);
  ForwardSpeedTime(Speed,10000/Speed);
}


void TuneMotor(int MotorSpeed)    //ปรัับจูนมอเตอร์
{
  if(MotorSpeed<=60)
  {
    LeftBaseSpeed = MotorSpeed-0;       //เอียงขวา
    RightBaseSpeed = MotorSpeed-1;       //เอียงซ้าย

  }
  else  // Speed > 60
  {
    LeftBaseSpeed = MotorSpeed-0;       //เอียงขวา   June Speed 100
    RightBaseSpeed = MotorSpeed-2;       //เอียงซ้าย

  }
}

void Forward2(int MotorSpeed, int Time)  //เดินหน้า
{
  TuneMotor(MotorSpeed);
  fd2(LeftBaseSpeed,RightBaseSpeed);
  delay(Time);
}

void Forward()  //เดินหน้า
{
  fd2(LeftBaseSpeed,RightBaseSpeed);
}

void ForwardSpeedTime(int MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
}

void MotorStop()
{
  ao();
  delay(100);
  
}
