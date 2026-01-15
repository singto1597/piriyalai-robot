void Box2(){ //วางลูกบาศก์ที่ 2
  /*UTurn();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,375);

  TurnLeftTime(137);
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,400);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(70,400);
  ForwardBalance(SlowSpeed,310);

  TurnRightTime(140);
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,420);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,0);

  KickFront();
  MotorStop();*/
  MaxBackward(70,45);
  TurnLeftTime(127);
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,250);
  MaxForwardBalance(40,310);

  MaxTurnRight();
  MaxForward(AccSpeed,165);
  MaxForwardBalance(25,310);
  MaxTurnRight();
  MaxForward(AccSpeed,100);
  MaxForwardBalance(25,310);

  KickFront();
  MotorStop();
  

  
}
