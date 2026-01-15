void Box3(){   //วางลูกบาศก์ที่ 3
  MaxBackward(70,200);
  MaxBackwardBalance(70,120);
  MotorStop();

  TurnRightTime(130);
  BackwardBalance(70,310);
  MaxForward(AccSpeed,200);
  MotorStop();

  TurnRight();
  BackwardBalance(SlowSpeed,310);
  BackwardBalance(SlowSpeed,310);
  MaxForward(50,1100);
  TurnRightTime(50);
  ForwardBalance(SlowSpeed,310);
  
  MotorStop();

  TurnLeft();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  TurnLeftTime(125);
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,0);
  
  KickFront();
  MotorStop();
}
