void InitialRef() {
  RefL3 = 2622;
  RefL2 = 3063;
  RefL1 = 2869;     
  RefC = 2765;
  RefR1 = 2952;     
  RefR2 = 3134;
  RefR3 = 2738;
  
  RefBL1 = 2673;    
  RefBR1 = 2643;    
}
void InitialSpeed() 
{
  //MaxSpeed = BaseSpeed;
  MaxSpeed = 100;
  Ki = 0;
  if(ErrorClear==0)
  {
    Error = 0;
    PreError = 0;
  }
  KiB = 0;
  if(BaseSpeed<=50)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 12;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 12;       //Backward PID
    KdB = 60;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 17;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 15;       //Backward PID
    KdB = 80;
    KtB = 10;
  }
  else if(BaseSpeed<=70)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 20;       //forward PID
    Kd = 50;
    Kt = 10;
    KpB = 16;       //Backward PID
    KdB = 100;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 25;       //forward PID
    Kd = 60;
    Kt = 10;
    KpB = 20;       //Backward PID
    KdB = 120;
    KtB = 10;
  }
  else if(BaseSpeed<=90)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 30;       //forward PID
    Kd = 70;
    Kt = 10;
    KpB = 25;       //Backward PID
    KdB = 140;
    KtB = 10;
  }
  else
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp =35;       //forward PID
    Kd = 80;
    Kt = 10;
    KpB = 30;       //Backward PID
    KdB = 160;
    KtB = 15;
  }
 } 
