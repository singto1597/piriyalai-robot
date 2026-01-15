void Box2(){   //วางลูกบาศก์ที่ 2
  MaxBackward(70,250);
  MaxBackwardBalance(70,120);
  MotorStop();

  TurnRightTime(130);
  BackwardBalance(70,100);
  MaxForward(AccSpeed,400);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(70,580);
  ForwardBalance(SlowSpeed,280);

  MotorStop();
  TurnRightTime(120);
  MaxForward(AccSpeed,420);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,0);

  KickFront();
  MotorStop();
}
