void TracJCStop() //เดินถึงเส้นและออกจากฟังก์ชัน
{  
  InitialSpeed();
  CalError();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalError();
    }
  }
}
void TracJC() //เดินถึงเส้นที่ไม่ใช่ขอบและถอยแบบจูน
{
  TracJCStop(); 
  ForwardSpeedTime(SlowSpeed,1);
  CalError();
  while((abs(Error)>1)) {CalError();}
  delay(20);
  MotorStop();
  BackwardBalanceF();
  BackwardSpeedTime(SlowSpeed,70);
}
void TracJC0() //เดินถึงเส้นและถอยแบบไม่จูน
{
  TracJCStop();
  MotorStop();
  BackwardSpeedTime(SlowSpeed,150);
}
void TracJC1() //เดินถึงเส้นจูนและถอยแบบไม่จูน
{
  TracJCBlack();
  MotorStop();
  BackwardSpeedTime(SlowSpeed,1);
  CalError();
  while(Error==0) {CalError();}
  delay(10);
  while(Error!=0) {CalError();}
  delay(100);
}
void TracJCBlack() //วิ่งเข้าหลุมดำหรือพื้นที่วางสีเขียว
{
  TracJCStop();
  ConvertADC();
  if((L3==0)&&(R3==1)) //เจอดำข้างซ้าย
  {
      AO(); 
      motor(1,-SlowSpeed); motor(2,-SlowSpeed);
      motor(3,SlowSpeed); motor(4,SlowSpeed);
      while(R3==1) {ConvertADC();}
      delay(50);
  }
  else if((L3==1)&&(R3==0))  //เจอดำข้างขวา
  {
      AO(); 
      motor(1,SlowSpeed); motor(2,SlowSpeed);
      motor(3,-SlowSpeed); motor(4,-SlowSpeed);
      while(L3==1) {ConvertADC();}
      delay(50);
   }
  MotorStop();
}
void TracJCSlowStop() 
{
  BaseSpeed = SlowSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeedTime(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStop();
  Forward();
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracSpeedTime(int TracSpeed, int TracTime) {
  BaseSpeed = TracSpeed;
  InitialSpeed();
  StartTimer3();
  CalError();
  while(ReadTimer3()<TracTime)
  {
    TracPID();
    delay(Kt);
    CalError();
  }
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeedStop() 
{
  BaseSpeed = ACCSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
