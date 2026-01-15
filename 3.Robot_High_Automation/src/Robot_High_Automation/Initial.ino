 void InitialRef() {
  RefL3 = 3134;
  RefL2 = 2930;
  RefL1 = 2881;
  RefC = 3144;
  RefR1 = 2754;
  RefR2 = 3018;
  RefR3 = 2636;
  RefBL = 2500;
  RefBR = 2500;

  RefBlue = 10833;
  RefGreen = 13288;
  RefBlack = 21193;
  RefWhite = 19145;
  RefYellow = 27396;
  RefRed = 45413;

  RefLimitSwitch = 4000;
}
void InitialSpeed() 
{
  //MaxSpeed = BaseSpeed;
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;
  if(BaseSpeed<=50)
  {
    LeftBaseSpeed = BaseSpeed-6;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-5;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 20;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 15;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed-6;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-3;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 18;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 18;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=70)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 21;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 21;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed-6;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 24;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 24;       //backward PID
    KdB = 30;
    KtB = 8;
  }
  else if(BaseSpeed<=90)
  {
    LeftBaseSpeed = BaseSpeed-6;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 27;       //forward PID
    Kd = 35;
    Kt = 10;
    KpB = 27;       //backward PID
    KdB = 35;
    KtB = 10;
  }
  else
  {
    LeftBaseSpeed = BaseSpeed-6;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 30;       //forward PID
    Kd = 50;
    Kt = 10;
    KpB = 30;       //backward PID
    KdB = 50;
    KtB = 5;
  }
}  
