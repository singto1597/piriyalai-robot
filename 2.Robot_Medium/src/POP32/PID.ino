void CalError(){ //คำนวณ error
  Convert7Analog();
  if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==0)) Error=-1;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==0)) Error=-2;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==1)) Error=-3;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==0)&&(R3==1)) Error=-4;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==1)&&(R3==1)) Error=-5;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=0;
  else if((L3==0)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=1;
  else if((L3==0)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=2;
  else if((L3==1)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=3;
  else if((L3==1)&&(L2==0)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=4;
  else if((L3==1)&&(L2==1)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=5;
  else if(C==0) Error=100;
//else if((L3==0)&&(L2==0)&&(L1==0)) Error=101;
//else if((R1==0)&&(R2==0)&&(R3==0)) Error=102;
}

void TrackPID(int MotorSpeed){ //เคลื่อนที่ตามช่องแบบ PID
  int Output,LeftOutput,RightOutput,MaxSpeed=100;
  
  TuneMotor(MotorSpeed);
  Output = (Kp*Error)+(Ki*Integral)+Kd*(Error-PreError);
  LeftOutput = LeftSpeed+Output;
  RightOutput = RightSpeed-Output;
  if(LeftOutput>MaxSpeed) LeftOutput = MaxSpeed;
  if(LeftOutput<-MaxSpeed) LeftOutput = -MaxSpeed; 
  if(RightOutput>MaxSpeed) RightOutput = MaxSpeed;
  if(RightOutput<-MaxSpeed) RightOutput = -MaxSpeed; 
  motor(1,LeftOutput);
  motor(2,LeftOutput);
  motor(3,RightOutput);
  motor(4,RightOutput);
  PreError = Error;
  Integral += Error;
}

void TrackJC(int MotorSpeed,int Time){  //เจอแยกแล้วหยุด
  int Status=0;
  Error=0;
  PreError=0;
  Integral=0;
  while(Status==0)
  {
    TrackPID(MotorSpeed);
    CalError();
    if(Error>=100) Status=1;
  }
  MotorStop();
  Backward(MotorSpeed,1);
  delay(Time);
  MotorStop();
}

void TrackJCBalance(int MotorSpeed,int Time){  //เจอแยกแล้วหยุดปรับจูน
  int Status=0;
  Error=0;
  PreError=0;
  Integral=0;
  while(Status==0)
  {
    TrackPID(MotorSpeed);
    CalError();
    if(Error>=100) Status=1;
  }
  MotorStop();
  Backward(MotorSpeed,100);
  MotorStop();
  ForwardBalance(SlowSpeed,0);
  MotorStop();
  Backward(SlowSpeed,50);
  delay(Time);
  MotorStop();
}

void TrackSpeedTimer(int MotorSpeed,int Time){  //แทกตามเวลาที่กำหนด
  int Status=0;
  Error=0;
  PreError=0;
  Integral=0;
  StartTimer0();
  while(Status==0){
    TrackPID(MotorSpeed);
    CalError();
    ReadTimer0();
    if(Timer0>=Time) Status=1;
  }
}
