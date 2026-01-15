void ForwardBalance(int MotorSpeed,int Time){ //เดินหน้าปรับจูน
  int Status=0;
  Forward(RobotSpeed,1);
  while(Status==0){
    Convert7Analog();
    if((L1==0)&&(R1==0)) Status=1;

    else if((L1==0)&&(R1==1)){ //เจอดำด้านซ้าย ขาวด้านขวา
      MotorStop();
      SL(SlowSpeed);
      while(R1==1) {Convert7Analog();}
      delay(30);
      Status=1;
    }

    else if((L1==1)&&(R1==0)){ //เจอขาวด้านซ้าย ดำด้านขวา
      MotorStop();
      SR(SlowSpeed);
      while(L1==1) {Convert7Analog();}
      delay(30);
      Status=1;
    }
  }
  MotorStop();
  Backward(MotorSpeed,1);
  delay(Time);
  MotorStop();
}
void MaxForwardBalance(int MotorSpeed,int Time){ //เดินหน้าปรับจูน
  int Status=0;
  Forward(70,1);

  while(Status==0){
    Convert7Analog();
    if((L1==0)&&(R1==0)) Status=1;

    else if((L1==0)&&(R1==1)){ //เจอดำด้านซ้าย ขาวด้านขวา
      MotorStop();
      SL(SlowSpeed);
      while(R1==1) {Convert7Analog();}
      delay(30);
      Status=1;
    }

    else if((L1==1)&&(R1==0)){ //เจอขาวด้านซ้าย ดำด้านขวา
      MotorStop();
      SR(SlowSpeed);
      while(L1==1) {Convert7Analog();}
      delay(30);
      Status=1;
    }
  }
  MotorStop();
  Backward(MotorSpeed,1);
  delay(Time);
  MotorStop();
}
void BackwardBalance(int MotorSpeed,int Time){ //ถอยหลังปรับจูน
  int Status=0;
  Backward(SlowSpeed,1);

  while(Status==0){
    Convert5AnalogBack();
    if((BL2==0)&&(BR2==0)) Status=1;

    else if((BL2==0)&&(BR2==1)){ //เจอดำด้านซ้าย ขาวด้านขวา
      MotorStop();
      motor(3,-SlowSpeed);
      motor(4,-SlowSpeed);
      while(BR2==1) {Convert5AnalogBack();}
      delay(50);
      Status=1;
    }

    else if((BL2==1)&&(BR2==0)){ //เจอขาวด้านซ้าย ดำด้านขวา
      MotorStop();
      motor(1,-SlowSpeed);
      motor(2,-SlowSpeed);
      while(BL2==1) {Convert5AnalogBack();}
      delay(50);
      Status=1;
    }
  }
  MotorStop();
  Forward(MotorSpeed,1);
  delay(Time);
  MotorStop();
}
void  MaxBackwardBalance(int MotorSpeed,int Time){ //ถอยหลังปรับจูน
  int Status=0;
  Backward(70,1);

  while(Status==0){
    Convert5AnalogBack();
    if((BL2==0)&&(BR2==0)) Status=1;

    else if((BL2==0)&&(BR2==1)){ //เจอดำด้านซ้าย ขาวด้านขวา
      MotorStop();
      motor(3,-SlowSpeed);
      motor(4,-SlowSpeed);
      while(BR2==1) {Convert5AnalogBack();}
      delay(50);
      Status=1;
    }
    
    else if((BL2==1)&&(BR2==0)){ //เจอขาวด้านซ้าย ดำด้านขวา
      MotorStop();
      motor(1,-SlowSpeed);
      motor(2,-SlowSpeed);
      while(BL2==1) {Convert5AnalogBack();}
      delay(50);
      Status=1;
    }
  }
  MotorStop();
  Forward(MotorSpeed,1);
  delay(Time);
  MotorStop();
}
