void ConvertADC()
{
  Read7Analog();
  if(L3<RefL3) L3 = 0;else L3 = 1;    //0:ดำ 1:ขาว
  if(L2<RefL2) L2 = 0;else L2 = 1;
  if(L1<RefL1) L1 = 0;else L1 = 1;
  if(C<RefC) C = 0;else C = 1;
  if(R1<RefR1) R1 = 0;else R1 = 1;
  if(R2<RefR2) R2 = 0;else R2 = 1;
  if(R3<RefR3) R3 = 0;else R3 = 1; 
}
void CalError() {
  ConvertADC();
  if(C==0) Error = 100;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==0)) Error = -1;  
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==0)) Error = -2;  
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==1)) Error = -3; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==0)&&(R3==1)) Error = -4; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==1)&&(R3==1)) Error = -5; 
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 0;
  else if((L3==1)&&(L2==1)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 5;
  else if((L3==1)&&(L2==0)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 4; 
  else if((L3==1)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 3; 
  else if((L3==0)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 2; 
  else if((L3==0)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error = 1; 
}
void TracPID()  {
  int Output, LeftOutput, RightOutput;

  Output = (Kp*Error) + (Ki*SumError) + (Kd*(Error-PreError));
  LeftOutput = LeftBaseSpeed + Output;
  RightOutput = RightBaseSpeed - Output;
  if(LeftOutput>MaxSpeed) LeftOutput = MaxSpeed;
  else if(LeftOutput<-MaxSpeed) LeftOutput = -MaxSpeed;//new pid
  if(RightOutput>MaxSpeed) RightOutput = MaxSpeed;
  else if(RightOutput<-MaxSpeed) RightOutput = -MaxSpeed;//new pid
  motor(1,LeftOutput);
  motor(2,LeftOutput);
  motor(3,RightOutput);
  motor(4,RightOutput);
  PreError = Error;
  SumError += Error;
}

void ConvertADCBack()
{
  Read2BackAnalog();
  if(BL<RefBL) BL = 0;else BL = 1;    //0:ดำ 1:ขาว
  if(BR<RefBR) BR = 0;else BR = 1;
}
