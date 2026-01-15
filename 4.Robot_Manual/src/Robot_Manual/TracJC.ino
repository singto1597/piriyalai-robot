void TracJCStop() 
{  
  InitialSpeed();
  TracSpeedTime(BaseSpeed,5000/BaseSpeed);
  CalError();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    CalError();
    while((ReadTimer()<Kt)&&(Error<99))
    {
      CalError();
    }
  }
  ErrorClear=0;
}
void TracJC() 
{
  TracJCStop();
  TuneJC();
}
void TuneJC()
{
  Forward();
  if(BaseSpeed<=50) delay(5000/BaseSpeed);
  else if(BaseSpeed<=60) delay(4000/BaseSpeed); 
  else if(BaseSpeed<=70) delay(2000/BaseSpeed);
  else if(BaseSpeed<=80) delay(1000/BaseSpeed);
  else if(BaseSpeed<=90) delay(500/BaseSpeed);
  //else if(BaseSpeed<=100) delay(500/BaseSpeed);
}
void TracJCStraight() 
{
  TracJC();
  ForwardDelay(5000/BaseSpeed);
}
void TracJCSlowStop() 
{
  BaseSpeed = SlowSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSlow() {
  TracJCSlowStop();
  Forward();
  while(Error>=100)
  {
    CalError();
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
  int TempSpeed = BaseSpeed;
  BaseSpeed = ACCSpeed;
  TracJCStop();
  Forward();
  //delay(1000/BaseSpeed);
  //while(Error>=100)
  //{
  //  CalError();
  //}
  delay(5000/BaseSpeed);
  BaseSpeed = TempSpeed;
  InitialSpeed();
}
void TracSpeedTime(int TracSpeed, int TracTime) {
  int TempSpeed = BaseSpeed;
  BaseSpeed = TracSpeed;
  InitialSpeed();
  StartTimer();
  CalError();
  while(ReadTimer()<TracTime)
  {
    if(Error>=99) Error = 0;
    TracPID();
    delay(Kt);
    CalError();
  }
  ErrorClear=1;
  BaseSpeed = TempSpeed;
  InitialSpeed();
}
void TracJCSpeedStop() 
{
  BaseSpeed = ACCSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeedStop99() 
{
  BaseSpeed = ACCSpeed;
  InitialSpeed();
  CalError();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<99))
    {
      Error99Check = 1;
      CalError();
    }
  }
  ErrorClear=0;
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCStop99() 
{
  InitialSpeed();
  CalError();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<99))
    {
      Error99Check = 1;
      CalError();
    }
  }
  ErrorClear=0;
}
void TracJCStopLorR() //ใช้เซ็นเซอร์ซ้ายหรือขวาในการเช็คแยก
{  
  InitialSpeed();
  TracSpeedTime(BaseSpeed,10000/BaseSpeed);
  CalError();
  while((L3==1)&&(R3==1))
  {
    TracPID();
    StartTimer();
    CalError();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalError();
    }
    if(Error>=99) Error = 0;
  }
  ErrorClear=0;
}
void TracJCLorR()     //ใช้เซ็นเซอร์ซ้ายหรือขวาในการเช็คแยก
{
  TracJCStopLorR();
  TuneJC();
}
void TracJCSpeedLorR()  //ใช้เซ็นเซอร์ซ้ายหรือขวาในการเช็คแยก
{
  BaseSpeed = ACCSpeed;
  TracJCStopLorR();
  Forward();
  while(Error>=100)
  {
    CalError();
  }
  delay(3000/BaseSpeed);
  BaseSpeed = Speed;
  ErrorClear=0;
  InitialSpeed();
}
void TracJCStopL() //ใช้เซ็นเซอร์ซ้ายในการเช็คแยก
{  
  InitialSpeed();
  TracSpeedTime(BaseSpeed,10000/BaseSpeed);
  CalError();
  while((L3==1))
  {
    TracPID();
    StartTimer();
    CalError();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalError();
    }
    if(Error>=99) Error = 0;
  }
  ErrorClear=0;
}
void TracJCL()     //ใช้เซ็นเซอร์ซ้ายในการเช็คแยก
{
  TracJCStopL();
  TuneJC();
}
void TracJCStopR() //ใช้เซ็นเซอร์ขวาในการเช็คแยก
{  
  InitialSpeed();
  TracSpeedTime(BaseSpeed,10000/BaseSpeed);
  CalError();
  while((R3==1))
  {
    TracPID();
    StartTimer();
    CalError();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalError();
    }
    if(Error>=99) Error = 0;
  }
  ErrorClear=0;
}
void TracJCR()     //ใช้เซ็นเซอร์ขวาในการเช็คแยก
{
  TracJCStopR();
  TuneJC();
}
void TracJCStopLeft() 
{  
  InitialSpeed();
  //TracSpeedTime(BaseSpeed,5000/BaseSpeed);
  CalError();
  while(Error!=101)
  {
    if(Error>99) Error=0;
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error!=101))
    {
      CalError();
    }
  }
  ErrorClear = 0;
}
void TracJCLeft() 
{
  TracJCStopLeft();
  TuneJC();
}
void TracJCStopRight() 
{  
  InitialSpeed();
  //TracSpeedTime(BaseSpeed,5000/BaseSpeed);
  CalError();
  while(Error!=102)
  {
    if(Error>99) Error=0;
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error!=102))
    {
      CalError();
    }
  }
  ErrorClear = 0;
}
void TracJCRight() 
{
  TracJCStopRight();
  TuneJC();
}
void ForwardJCStop() 
{  
  InitialSpeed();
  ForwardSpeedTime(BaseSpeed,5000/BaseSpeed);
  CalError();
  while(Error<99)
  {
    CalError();
  }
  ErrorClear=0;
}
void ForwardJC() 
{
  ForwardJCStop();
  TuneJC();
}
