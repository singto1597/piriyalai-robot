int TracBalance()
{
  int Status=0,TimeBalance=500;
    CheckLimitSwitch();
    delay(Kt);
    CalError();
    //if(C==0)  //เจอดำตรงกลาง
    if((L1==0)&&(R1==0)) //เจอดำทั้งสองข้าง
    {
      delay(5);
      CalError();
      //if(C==0) Status = 2; //เจอดำตรงกลาง 
      if((L1==0)&&(R1==0)) Status = 2; //เจอดำทั้งสองข้าง
      //else ForwardSpeedTime(Speed,1000);
    }
    else if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      //delay(5);
      CalError();
      //if(C==0) Status = 2;  //เจอดำตรงกลาง 
      if((L1==0)&&(R1==0)) Status = 2; //เจอดำทั้งสองข้าง
      else if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
      {
        Status = 2;
        AO(); 
        motor(1,-NewSpeed); motor(2,-NewSpeed);
        motor(3,NewSpeed); motor(4,NewSpeed);
        StartTimer4();
        while(R3==1) 
        {
          ConvertADC(); 
          if(ReadTimer4()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
          {
            MotorStop();
            R3=0;
            Status = 4;
            motor(1,NewSpeed); motor(2,NewSpeed);
            motor(3,-NewSpeed); motor(4,-NewSpeed);
            delay(TimeBalance-50);
            MotorStop();
          }
        }
        delay(50);//50
      }
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      delay(5);
      CalError();
      //if(C==0) Status = 2;  //เจอดำตรงกลาง 
      if((L1==0)&&(R1==0)) Status = 2; //เจอดำทั้งสองข้าง
      else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
      {
        Status = 2;
        AO(); 
        motor(1,NewSpeed); motor(2,NewSpeed);
        motor(3,-NewSpeed); motor(4,-NewSpeed);
        StartTimer4(); 
        while(L3==1) 
        {
          ConvertADC(); 
          if(ReadTimer4()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
          {
            MotorStop();
            L3=0;
            Status = 4;
            motor(1,-NewSpeed); motor(2,-NewSpeed);
            motor(3,NewSpeed); motor(4,NewSpeed);
            delay(TimeBalance-50);
            MotorStop();
          }
        }
        delay(50); //50
      } 
    }
    else TracPID();
    return(Status);
}
int BackwardBalance(int Time)  //ถอยหลังปรับสมดุล
{
  int Status=0,TimeBalance=400;
  StartTimer();
  BackwardSpeedTime(SlowSpeed,1);
  
  while(Status==0)
  {
    ConvertADCBack();
    if((BL==0)&&(BR==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      motor(1,SlowSpeed); motor(2,SlowSpeed);
      motor(3,-SlowSpeed); motor(4,-SlowSpeed);
      StartTimer1();
      while(BR==1) 
      {
        ConvertADCBack(); 
        if(ReadTimer1()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
        {
          MotorStop();
          BR=0;
          Status = 4;
          motor(1,-SlowSpeed); motor(2,-SlowSpeed);
          motor(3,SlowSpeed); motor(4,SlowSpeed);
          delay(TimeBalance/2);
          MotorStop();
        }
      }
      delay(30);
    }
    else if((BL==1)&&(BR==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      motor(1,-SlowSpeed); motor(2,-SlowSpeed);
      motor(3,SlowSpeed/2); motor(4,SlowSpeed/2);
      StartTimer1();
      while(BL==1) 
      {
        ConvertADCBack(); 
        if(ReadTimer1()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
        {
          MotorStop();
          BL=0;
          Status = 4;
          motor(1,SlowSpeed); motor(2,SlowSpeed);
          motor(3,-SlowSpeed); motor(4,-SlowSpeed);
          delay(TimeBalance/2);
          MotorStop();
        }
      }
      delay(30);
    }
    else if((BL==0)&&(BR==0)) Status=3; //เจอดำทั้งสองข้าง
    if(ReadTimer()>Time) Status=4;  //หมดเวลาถอยหลัง
  }
  MotorStop();
  return(Status);
}
void BackwardBalanceF()  //ถอยหลังปรับสมดุลใช้เซ็นเซอร์หน้า
{
  int Status=0;
  BackwardSpeedTime(SlowSpeed,1);
  
  while(Status==0)
  {
    ConvertADC();
    if((L3==0)&&(R3==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      motor(1,SlowSpeed/2); motor(2,SlowSpeed/2);
      motor(3,-SlowSpeed); motor(4,-SlowSpeed);
      while(R3==1) {ConvertADC();}
      delay(30);
    }
    else if((L3==1)&&(R3==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      motor(1,-SlowSpeed); motor(2,-SlowSpeed);
      motor(3,SlowSpeed/2); motor(4,SlowSpeed/2);
      while(L3==1) {ConvertADC();}
      delay(30);
    }
    else if((L3==0)&&(R3==0)) Status=3; //เจอดำทั้งสองข้าง
  }
  //MotorStop();
  BackwardSpeedTime(SlowSpeed,1);
  ConvertADC();
  while(C==0) {ConvertADC();}
}
void ForwardBalanceB()  //เดินหน้าปรับสมดุลใช้เซ็นเซอร์หลัง
{
  int Status=0;
  ForwardSpeedTime(SlowSpeed,1);
  
  while(Status==0)
  {
    ConvertADCBack();
    if((BL==0)&&(BR==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      motor(1,-SlowSpeed/2); motor(2,-SlowSpeed/2);
      motor(3,SlowSpeed); motor(4,SlowSpeed);
      while(BR==1) {ConvertADCBack();}
      delay(20);
    }
    else if((BL==1)&&(BR==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      motor(1,SlowSpeed); motor(2,SlowSpeed);
      motor(3,-SlowSpeed/2); motor(4,-SlowSpeed/2);
      while(BL==1) {ConvertADCBack();}
      delay(20);
    }
    else if((BL==0)&&(BR==0)) Status=3; //เจอดำทั้งสองข้าง
  }
  ForwardSpeedTime(SlowSpeed,1);
  ConvertADCBack();
  while((BL==0)||(BR==0)) {ConvertADCBack();}
}
