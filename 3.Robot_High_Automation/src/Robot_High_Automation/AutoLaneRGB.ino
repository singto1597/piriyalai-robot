void AutoLaneRGB()  //เซ็นเซอร์&RGB วิ่งตรงยาว 7:เลี้ยวขวา  8:เลี้ยวซ้าย
{
  int Status;
 
  while(1)
  {
    Status = 0;
    ForwardSpeedTime(Speed,1);
    while(Status==0)  //ทางหลัก
    {
      Status=TracBalance();
      if(Status>=2)
      {
        CheckFloorRGB();
        if((FloorColor!=White)&&(FloorColor!=Black))  //เจอพื้นที่วาง
        {
          BackwardSpeedTime(50,200); 
          if(RobotMode==8) UTurnLeft(); else UTurnRight();
          BackwardBalance(350);
          if((RedNumber>1)||(YellowNumber>1)||(BlueNumber>1)||(GreenNumber>1)) //สีเดิมวางไปแล้ว
          { 
            ForwardSpeedTime(Speed,500);
            if(RobotMode==8) TurnLeft(); else TurnRight();
            //RobotMode = 13-RobotMode; //วนตรงข้ามจากเดิม
            RobotMode = RobotMode-2;  //วนทางเดิมแต่ทีละช่อง
            if(BackwardBalance(400)==4) //ไม่มีเส้นให้จูน
            {
              MotorStop();
              ForwardSpeedTime(SlowSpeed,400);
            }
            else // มีเส้นให้จูน
            {
              MotorStop();
              ForwardSpeedTime(SlowSpeed,200); 
            }
            AutoRightLeftRGB();
          }
        }
        else  //ไม่เจอพื้นที่วาง
        {
          if(RobotMode==7) TurnRight(); else TurnLeft();
          BackwardBalance(400); 
          //if(TracLane1Block(Speed,600)==2)  //ขวาเจอทางตันให้กลับหลังหัน
          if(TracLane1Block(Speed,400)==2)  //ขวาเจอทางตันให้กลับหลังหัน
          {
            MotorStop();
            BackwardSpeedTime(Speed,230);
            if(RobotMode==7) UTurnRight(); else UTurnLeft();
            BackwardBalance(400);
            //if(TracLane1Block(Speed,600)==2)  //ขวาเจอทางตันด้านที่ 3 ให้ย้อนกลับ
            if(TracLane1Block(Speed,400)==2)  //ขวาเจอทางตันด้านที่ 3 ให้ย้อนกลับ
            {
              MotorStop();
              BackwardSpeedTime(Speed,230);
              if(RobotMode==7) TurnLeft(); else TurnRight();
              BackwardBalance(400);
            }
          }
        }
      }
    }    
  } 
}
