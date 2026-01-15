void Box1(){   //วางลูกบาศก์ที่ 1
  MaxForward(AccSpeed,480);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,280);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,120);
  ForwardBalance(SlowSpeed,310);

  TurnRight();
  MaxForward(AccSpeed,155);

  TurnLeftTime(128);
  MaxForward(AccSpeed,360);
  MotorStop();
  ForwardBalance(70,390);
  TurnLeftTime(111);
  
  MaxForward(AccSpeed,320);
  ForwardBalance(SlowSpeed,400);

  TurnRight();
  MaxForward(AccSpeed,120);
  ForwardBalance(SlowSpeed,310);

  
  TurnRight();
  MaxForward(AccSpeed,90);
  ForwardBalance(SlowSpeed,0);

  KickFront();
  MotorStop();
 
}
