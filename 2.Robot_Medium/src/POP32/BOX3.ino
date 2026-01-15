void Box3(){ //วางลูกบาศก์ที่ 1
  /*UTurn();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  TurnLeft();
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,360);

  TurnRight();
  BackwardBalance(SlowSpeed,310);
  MaxForward(50,650);
  ForwardBalance(SlowSpeed,310);

  TurnLeft();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  TurnLeft();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,0);
  
  KickFront();
  MotorStop();*/
  MaxBackward(70,100);
  MaxBackwardBalance(70,170);
  MotorStop();

  MaxTurnRight();
  BackwardBalance(70,310);
  MaxForward(AccSpeed,400);
  MotorStop();

  MaxTurnRight();
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,400);;
  ForwardBalance(25,310);

  MaxTurnRight();
  BackwardBalance(SlowSpeed,200);
  MaxForward(AccSpeed,580);
  ForwardBalance(SlowSpeed,310);

  MaxTurnRight();
  ForwardBalance(SlowSpeed,250);
  
  KickFront();
  MotorStop();
  
  
}
