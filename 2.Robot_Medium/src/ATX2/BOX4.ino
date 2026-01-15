void Box4(){   //วางลูกบาศก์ที่ 4
  MaxBackward(70,150);
  MaxBackwardBalance(70,170);
  MotorStop();

  TurnLeftTime(138);
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,365);
  MotorStop();
  
  TurnRightTime(127);
  MotorStop();
  MaxForward(AccSpeed,60);
  ForwardBalance(25,310); //CheckPoint2

  MotorStop();
  MaxBackward(70,250);
  MotorStop();
  MaxBackwardBalance(70,120);
  TurnRightTime(126);
  MotorStop();
  MaxForward(AccSpeed,180);
  MotorStop();
  TurnLeftTime(136);
  BackwardBalance(SlowSpeed,310);

  MaxForward(50,650);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  TurnLeftTime(128);
  MaxForward(AccSpeed,200);
  ForwardBalance(SlowSpeed,310);

  TurnLeft();
  BackwardBalance(SlowSpeed,310);
  MaxForward(70,510);
  MotorStop();

  TurnRightTime(121);
  BackwardBalance(SlowSpeed,310);

  MaxForward(AccSpeed,360);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,170);
  MotorStop();

  TurnRightTime(110);
  MaxForward(AccSpeed,95);
  ForwardBalance(SlowSpeed,310);
  MotorStop();

  UTurn();
  ForwardBalance(SlowSpeed,0);

  KickFront();
  MotorStop();
 
  
 
}
