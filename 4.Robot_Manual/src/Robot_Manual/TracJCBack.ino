void TracJCStopBack() 
{  
  InitialSpeed();
  TracSpeedTimeBack(BaseSpeed,6000/BaseSpeed);
  CalErrorBack();
  while(Error<100)
  {
      TracPIDBack();
      StartTimer();
      while((ReadTimer()<KtB)&&(Error<100))
      {
        CalErrorBack();           
      }
  }
  ErrorClear=0;
}
void TracJCBack() 
{
  TracJCStopBack();
  Backward();
  if(BaseSpeed<=50) delay(8000/BaseSpeed);
  else if(BaseSpeed<=60) delay(5500/BaseSpeed); 
  else if(BaseSpeed<=70) delay(4000/BaseSpeed);
  else if(BaseSpeed<=80) delay(3000/BaseSpeed);
  else if(BaseSpeed<=90) delay(1500/BaseSpeed);
  else delay(800/BaseSpeed);
}
void TracSpeedTimeBack(int TracSpeed, int TracTime) {
  BaseSpeed = TracSpeed;
  InitialSpeed();
  StartTimer();
  CalErrorBack();
  while(ReadTimer()<TracTime)
  {
    if(Error>=99) Error = 0;
    TracPIDBack();
    delay(Kt);
    CalErrorBack();
  }
  ErrorClear=1;
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeedTimeBack(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStopBack();
  Backward();
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCStopBack0()
{
  //TracSpeedTimeBack(ACCSpeed,10000/ACCSpeed);
  if(BaseSpeed>=95) TracJCSpeedTimeBack(95,0);
  else TracJCBack();
}
void TracJCSpeedBack() 
{
  BaseSpeed = ACCSpeed;
  TracJCStopBack();
  Backward();
  while(Error>=100)
  {
    CalError();
  }
  delay(6000/BaseSpeed);
  BaseSpeed = Speed;
  ErrorClear=0;
  InitialSpeed();
}
