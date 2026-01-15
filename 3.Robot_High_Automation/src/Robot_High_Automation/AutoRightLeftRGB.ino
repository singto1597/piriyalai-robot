void AutoRightLeftRGB(){ //เซ็นเซอร์&กล้อง เช็คทีละ 1 ช่อง 5:เลี้ยวขวา,6:เลี้ยวซ้าย 
  while(1){
    Trac1BlockRGB(Speed,1350); //sp55 time560
  }
}

void Trac1BlockRGB(int TracSpeed,int Time){
  BaseSpeed = TracSpeed;
  InitialSpeed();
  TracFloorRGB(TracSpeed,Time);  //ไม่เจอสีพื้น
  BaseSpeed = Speed;
  InitialSpeed();
}

void TracFloorRGB(int TracSpeed,int Time){
  int Status=0;
  
  StartTimer();
  ForwardSpeedTime(TracSpeed,1);
  while(Status==0){ 
    Status=TracBalance();
    if((ReadTimer()>Time)&&(Status==0)){ //ไม่เจอเส้นดำ
      Status = 1; 
      CheckFloorRGB();
      ShowRGBColor();
      if(BridgeStatus==2){ //ขาลง
          TracSpeedTime(Speed,1050); MotorStop(); //450
          //TracFloorRGB(TracSpeed,Time);
          BridgeStatus = 0;
      }
      else if(BridgeStatus==1) BridgeStatus=2; //ขาเลี้ยวบนสะพาน
      if(RobotMode==5) TurnRight(); else TurnLeft(); 
    } 
    if(Status>=2){ //เจอเส้นดำ
      CheckFloorRGB();
      ShowRGBColor();
      BackwardSpeedTime(Speed,350);
      if((FloorColor!=White)&&(FloorColor!=Black)) BackwardSpeedTime(Speed,550);  //400 //650
      if(RobotMode==5) TurnLeft(); else TurnRight();
      if(Status==4) {/*BackwardSpeedTime(Speed,200);*/ MotorStop();}//200
    }
  }
}
void CheckFloorRGB(){
    //ForwardSpeedTime(SlowSpeed,20);
    MotorStop(); 
    delay(50);
    CheckColorRGB(); 
    delay(50);
    /*oled.clear();
    oled.text(1,1," %d ",ReadRGB());
    oled.show();
    delay(200);*/
    switch(FloorColor)
    {
      case Blue: 
      /* 
      oled.clear();
      oled.text(1,1," %d ",ReadRGB());
      oled.show();
      delay(200);*/
      BackwardSpeedTime(Speed,150); AO();
            KickBlue(); BlueNumber++; 
            //ForwardSpeedTime(SlowSpeed,30);
            //MotorStop();
            break;
      case Green: 
      /*oled.clear();
      oled.text(1,1," %d ",ReadRGB());
      oled.show();
      delay(200);*/
      BackwardSpeedTime(Speed,150); AO();
            KickGreen(); GreenNumber++; 
            //ForwardSpeedTime(SlowSpeed,30);
            //MotorStop();
            break;
      default: 
      /*oled.clear();
      oled.text(1,1," %d ",ReadRGB());
      oled.show();
      delay(200);*/
      //BackwardSpeedTime(Speed,300);
            MotorStop();
            CheckColorRGB();
            switch(FloorColor)
            {
              case Red: 
              /*oled.clear();
              oled.text(1,1," %d ",ReadRGB());
              oled.show();
              delay(200);*/
              //TurnLeft();
              BackwardSpeedTime(Speed,420); AO();                  
              KickRed(); RedNumber++; 
              BackwardSpeedTime(Speed,1050);
              UTurnLeft();
              break;
              case Yellow: 
              /*oled.clear();
              oled.text(1,1," %d ",ReadRGB());
              oled.show();
              delay(200);*/
              BackwardSpeedTime(Speed,420); AO();
                   KickYellow(); YellowNumber++; 
                   BackwardSpeedTime(Speed,1050);
                   UTurnLeft();
                   break;
              //default: 
            }      
            
    }
    if((RedNumber>0)&&(YellowNumber>0)&&(BlueNumber>0)&&(GreenNumber>0)){ //ครบ 4 สียกธง
      BackwardSpeedTime(50,50);
      MotorStop();
      FlagUp();
      Finish();
    } 
}
int CheckLimitSwitch(){  //เช็คการกด 0:ไม่กด , 1:กด
  if(analog(7)>RefLimitSwitch) //มีการกดสวิช
  {
    ForwardSpeedTime(SlowSpeed,50);
    if(analog(7)<RefLimitSwitch) //เจอตะเกียบ
    {
      ForwardSpeedTime(SlowSpeed-5,1700); MotorStop(); 
      return(1);
    }
    else 
    {
      if(BridgeStatus==0) //ขาขึ้นสะพาน
      {
          TracSpeedTime(Speed,2350); 
          BridgeStatus = 1;
          return(3);
      }
      else //ขาลงสะพาน
      {
        while(analog(7)>RefLimitSwitch) {} 
        ForwardSpeedTime(SlowSpeed-10,100); 
        BridgeStatus = 0; 
        return(4);   
      }
    }
  }
  else return(2);
}
