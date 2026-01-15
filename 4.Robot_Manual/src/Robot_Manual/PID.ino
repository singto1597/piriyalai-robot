void CalError()
{
  CalError7Sensor(); 
}
void ConvertADC()
{
  Read7Analog();
  if(L3<RefL3) L3 = (0+BlackLine)%2; else L3 = (1+BlackLine)%2;  //0:ดำ 1:ขาว
  if(L2<RefL2) L2 = (0+BlackLine)%2; else L2 = (1+BlackLine)%2;  
  if(L1<RefL1) L1 = (0+BlackLine)%2; else L1 = (1+BlackLine)%2; 
  if(C<RefC) C = (0+BlackLine)%2; else C = (1+BlackLine)%2; 
  if(R1<RefR1) R1 = (0+BlackLine)%2; else R1 = (1+BlackLine)%2; 
  if(R2<RefR2) R2 = (0+BlackLine)%2; else R2 = (1+BlackLine)%2;
  if(R3<RefR3) R3 = (0+BlackLine)%2; else R3 = (1+BlackLine)%2;
}
void CalError7Sensor() {
  ConvertADC();
  if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==0)) Error = 6;  
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==0)) Error = 5;  
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==1)) Error = 4; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==0)&&(R3==1)) Error = 3; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==1)&&(R3==1)) Error = 2; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==0)&&(R1==0)&&(R2==1)&&(R3==1)) Error = 1; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==0)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 0; 
  else if((L3==1)&&(L2==1)&&(L1==0)&&(C==0)&&(R1==1)&&(R2==1)&&(R3==1)) Error = -1;
  else if((L3==1)&&(L2==1)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = -2;
  else if((L3==1)&&(L2==0)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = -3; 
  else if((L3==1)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = -4; 
  else if((L3==0)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = -5; 
  else if((L3==0)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = -6; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)&&(Error99Check==1))  Error = 99;      //white all
  else if((L3==0)&&(L2==0)&&(L1==0)&&(C==0)&&(R1==0)&&(R2==0)&&(R3==0)) Error = 100;   //Left and Right Junction 
  else if((L3==0)&&(L2==0)&&(L1==0)&&(C==0)/*&&(R1==0)*/) Error = 101;                             //Left Junction 
  else if(/*(L1==0)&&*/(C==0)&&(R1==0)&&(R2==0)&&(R3==0)) Error = 102;
  Error99Check=0;
}

void TracPID()  {
  int Output, LeftSpeed, RightSpeed, KpTemp;
  if(abs(Error)<2) KpTemp=1; else KpTemp=Kp;
  Output = (KpTemp*Error) + (Ki*SumError) + (Kd*(Error-PreError));
  LeftSpeed = LeftBaseSpeed + Output;
  RightSpeed = RightBaseSpeed - Output;
  if(LeftSpeed>MaxSpeed) LeftSpeed = MaxSpeed;
  else 
  {
    if(PidStatus!=0) {if(LeftSpeed<-MaxSpeed) LeftSpeed = -MaxSpeed;}
    else if(LeftSpeed<0) LeftSpeed = 0;//new pid
  }
  if(RightSpeed>MaxSpeed) RightSpeed = MaxSpeed;
  else 
  {
    if(PidStatus!=0) {if(RightSpeed<-MaxSpeed) RightSpeed = -MaxSpeed;}
    else if(RightSpeed<0) RightSpeed = 0;//new pid
  }
  if(WheelDrive==0)
  {
    motor(1,LeftSpeed); 
    motor(2,RightSpeed);
  }
  else
  {
    motor(1,LeftSpeed);
    motor(2,LeftSpeed); 
    motor(3,RightSpeed);
    motor(4,RightSpeed);
  }
  PreError = Error;
  SumError += Error;
}
void CalErrorBack()
{
  CalErrorBack2Sensor(); 
}
void ConvertADCBack()
{
  Read2AnalogBack();
  if(BL1<RefBL1) BL1 = (0+BlackLine)%2; else BL1 = (1+BlackLine)%2;  //0:ดำ 1:ขาว
  if(BR1<RefBR1) BR1 = (0+BlackLine)%2; else BR1 = (1+BlackLine)%2; 
}
void CalErrorBack2Sensor() {
  ConvertADCBack();
  if((BL1==1)&&(BR1==0)) Error = 1; 
  else if((BL1==1)&&(BR1==1)) Error = 0;  
  else if((BL1==0)&&(BR1==1)) Error = -1; 
  else if((BL1==0)&&(BR1==0)) Error = 100; 
}
void TracPIDBack()  {
  int Output, LeftSpeed, RightSpeed;
  Output = (KpB*Error) + (KiB*SumError) + (KdB*(Error-PreError));
  LeftSpeed = BackLeftBaseSpeed + Output;
  RightSpeed = BackRightBaseSpeed - Output;
  if(LeftSpeed>MaxSpeed) LeftSpeed = MaxSpeed;
  else 
  {
    if(PidStatus!=0) {if(LeftSpeed<-MaxSpeed) LeftSpeed = -MaxSpeed;}
    else if(LeftSpeed<0) LeftSpeed = 0;//new pid
  }
  if(RightSpeed>MaxSpeed) RightSpeed = MaxSpeed;
  else 
  {
    if(PidStatus!=0) {if(RightSpeed<-MaxSpeed) RightSpeed = -MaxSpeed;}
    else if(RightSpeed<0) RightSpeed = 0;//new pid
  }
  if(WheelDrive==0)
  {
    motor(1,-LeftSpeed); 
    motor(2,-RightSpeed);
  }
  else
  {
    motor(1,-LeftSpeed);
    motor(2,-LeftSpeed); 
    motor(3,-RightSpeed);
    motor(4,-RightSpeed);
  }
  PreError = Error;
  SumError += Error;
}
