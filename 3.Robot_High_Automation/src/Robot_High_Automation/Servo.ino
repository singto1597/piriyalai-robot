void KickRed() 
{
  AO();
  servo(2,0);
  Impact();
  oled.text(3,0,"  Red   ");
  oled.show();
  delay(300);
  servo(2,90);
}
void KickYellow() 
{
  AO();
  servo(2,180);
  Impact();
  oled.text(3,0,"  Yellow   ");
  oled.show();
  delay(300); 
  servo(2,90);
}
void KickBlue() 
{
  AO();
  servo(1,0);
  Impact();
  oled.text(3,0,"  Blue   ");
  oled.show();
  delay(300);
  servo(1,90);
}
void KickGreen() 
{
  AO();
  servo(1,180);
  Impact();
  oled.text(3,0,"  Green   ");
  oled.show();
  delay(300);
  servo(1,90);
}
void FlagUp() 
{
  MotorStop();
  servo(5,20);
}
void FlagDown() 
{
  MotorStop();
  servo(5,130);
}
void Impact()
{
  delay(100);
  BackwardSpeedTime(Speed,50);
  MotorStop();
  ForwardSpeedTime(Speed,50);
  MotorStop();
}
void TestServo()
{
  FlagUp();
  KickRed();
  KickYellow();
  KickBlue();
  KickGreen();
  FlagDown();
}
