void Box4(){ //วางลูกบาศก์ที่ 1
  /*UTurn();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,340);

  TurnRight();
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,360);
  MotorStop();
  
  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310); //CheckPoint2

  UTurn();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,155);
  ForwardBalance(SlowSpeed,310);

  TurnLeft();
  MaxForward(AccSpeed,180);
  MotorStop();
  TurnLeft();
  BackwardBalance(SlowSpeed,310);

  MaxForward(50,650);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  TurnLeftTime(136);
  MaxForward(AccSpeed,200);
  ForwardBalance(SlowSpeed,310);

  TurnLeft();
  MaxForward(70,550);
  MotorStop();

  TurnRight();
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,360);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,185);

  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,310);

  UTurn();
  ForwardBalance(SlowSpeed,0);

  KickFront();
  MotorStop();*/
  MaxBackward(BackSpeed,50);
  MaxBackwardBalance(SlowSpeed,170);
  MotorStop();

  MaxTurnRight();
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,380);
  MotorStop();
  
  MaxTurnRight();
  MotorStop();
  MaxForward(AccSpeed,150);
  MaxForwardBalance(SlowSpeed,310); 

  TurnLeftTime(120);
  ForwardBalance(SlowSpeed,310); 
  TurnLeftTime(127);
  ForwardBalance(SlowSpeed,310); //CheckPoint

  BackwardBalance(SlowSpeed,170);
  TurnLeftTime(130);
  BackwardBalance(SlowSpeed,310);
  MaxForward(AccSpeed,400);
  MaxForwardBalance(50,150); 

  KickFront();
  MotorStop();
  
  
}
