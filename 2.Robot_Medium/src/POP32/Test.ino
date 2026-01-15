void test() {
  MaxBackward(70,120);
  MotorStop();
  
  TurnRight();
  BackwardBalance(SlowSpeed,310);
  MotorStop();

  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  TurnLeftTime(135);
  MaxForward(AccSpeed,180);
  ForwardBalance(SlowSpeed,310);
  ForwardBalance(SlowSpeed,320);

  TurnLeftTime(135);
  MaxForward(AccSpeed,620);

  MotorStop();
  
  
  
}
