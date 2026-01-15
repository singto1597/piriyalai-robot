void MotorStop(){  //มอเตอร์หยุดทั้ง 4 ล้อ
  AO();
  delay(10);
}

void TuneMotor(int MotorSpeed){  //ปรับจูนมอเตอร์
  if(MotorSpeed<=25){
    LeftSpeed = MotorSpeed-0; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  
  else if(MotorSpeed<=35){
    LeftSpeed = MotorSpeed-3.5; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-1; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  
  else if(MotorSpeed<=40){
    LeftSpeed = MotorSpeed-2; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-2; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  
  else if(MotorSpeed<=50){
    LeftSpeed = MotorSpeed-2; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-2; //เอียงซ้าย
  }
  
  else if(MotorSpeed<=60){
    LeftSpeed = MotorSpeed-0.5; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-1; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  
  else if(MotorSpeed<=70){
    LeftSpeed = MotorSpeed-2; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  
  else if(MotorSpeed<=80){  //ความเร็วมากกว่าเท่ากับ 80
    LeftSpeed = MotorSpeed-0; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  
   else if(MotorSpeed<=90){
    LeftSpeed = MotorSpeed-0; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-3; //เอียงซ้าย
  }
  
  else{  //ความเร็วมากกว่า 90
    LeftSpeed = MotorSpeed-4.4; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }  
}

void Forward(int MotorSpeed,int Time){ //เดินหน้า
  TuneMotor(MotorSpeed);
  FD2(LeftSpeed,RightSpeed);
  delay(Time);
}

void Backward(int MotorSpeed,int Time){ //ถอยหลัง
  TuneMotor(MotorSpeed);
  BK2(LeftSpeedBack,RightSpeedBack);
  delay(Time);
}

void TurnLeft(){   //เลี้ยวซ้าย
  MotorStop();
  SL(TurnSpeed);
  delay(132);
  MotorStop();
}

void TurnRight(){   //เลี้ยวขวา
  MotorStop();
  SR(TurnSpeed);
  delay(132);
  MotorStop();
}

void MaxTurnRight(){   //เลี้ยวขวา
  MotorStop();
  SR(TurnSpeed);
  delay(127);
  MotorStop();
}

void TurnRightTime(int Time){   //เลี้ยวซ้าย
  MotorStop();
  SR(TurnSpeed);
  delay(Time);
  MotorStop();
}

void TurnLeftTime(int Time){   //เลี้ยวซ้าย
  MotorStop();
  SL(TurnSpeed);
  delay(Time);
  MotorStop();
}

void UTurn(){   //เลี้ยวขวา
  MotorStop();
  SR(TurnSpeed);
  delay(228);
  MotorStop();
}

void UTurnTime(int Time){   //เลี้ยวขวา
  MotorStop();
  SR(TurnSpeed);
  delay(Time);
  MotorStop();
}

void MaxForward(int MotorSpeed, int Time) {
  Forward(MoveSpeed,100);
  TuneMotor(MotorSpeed);
  FD2(LeftSpeed,RightSpeed);
  delay(Time);
  Forward(RobotSpeed,100);
}

void MaxBackward(int MotorSpeed, int Time){
  Backward(MoveSpeed,100);
  TuneMotor(MotorSpeed);
  BK2(LeftSpeedBack,RightSpeedBack);
  delay(Time);
  Backward(RobotSpeed,200);
}
