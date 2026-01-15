void InitialRef() {
  RefL4 = 450;
  RefL3 = 450;
  RefL2 = 450;
  RefL1 = 450;
  RefR1 = 450;
  RefR2 = 450;
  RefR3 = 450;
  RefR4 = 450;

}
void InitialSpeed() 
{
  MaxSpeed = BaseSpeed;   
  //MaxSpeed = 100;
  Ki = 0;
  Error = 0;
  PreError = 0;
  if(BaseSpeed<=50)
  {
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    Kp = 10;       //forward PID
    Kd = 30;
    Kt = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed-0; //-1
    RightBaseSpeed = BaseSpeed-2;
    Kp = 8;       //forward PID
    Kd = 30;
    Kt = 10;

  }
  else if(BaseSpeed<=70)
  {
    LeftBaseSpeed = BaseSpeed-0; //-2
    RightBaseSpeed = BaseSpeed-2;
    Kp = 10;       //forward PID
    Kd = 35;
    Kt = 10;

  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed-0; //-2
    RightBaseSpeed = BaseSpeed-2;
    Kp = 15;       //forward PID
    Kd = 40;
    Kt = 10;

  }
  else if(BaseSpeed<=90)
  {
    LeftBaseSpeed = BaseSpeed-4; //-4
    RightBaseSpeed = BaseSpeed-0;
    Kp = 18;       //forward PID
    Kd = 50;
    Kt = 10;

  }
  else //94
  {
    LeftBaseSpeed = BaseSpeed-0; //-6
    RightBaseSpeed = BaseSpeed-2; //-0
    Kp = 30;       //forward PID
    Kd = 60;
    Kt = 10;

  }
}  
