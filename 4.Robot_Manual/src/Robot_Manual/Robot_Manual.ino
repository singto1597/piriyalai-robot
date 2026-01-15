#include <POP32.h>

#include <WCX.h>
WCX mywcx;

  int Speed, SlowSpeed, ACCSpeed, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, DistanceRef;
  int Error, PreError, Kp, Kd, Ki, Kt,BackLeftBaseSpeed, BackRightBaseSpeed;
  int KpB,KdB,KtB,KiB;
  int RefL3, RefL2, RefL1, RefC, RefR1, RefR2, RefR3, RefBL1, RefBR1, SumError;
  int L3, L2, L1, C, R1, R2, R3, BL1, BR1;
  long Timer, Timer2, Timer3;
  int SW_OK_Status,Error99Check=0,digital_sw=0;
  int KnobBase;
  int CanStatus=0,CanNumber=1;
  
  #define No 0
  #define Yes 1

  #define Mode0 0
  #define Mode1 1
  #define Mode2 2
  #define Mode3 3
  #define Mode4 4

  #define WheelDrive  1   //0:ขับเคลื่อน 2 ล้อ , 1:ขับเคลื่อน 4 ล้อ
  #define SwitchTime  200 //เวลาในการตรวจสอบการกดสวิชในหน่วย ms

  int Mode=Mode0;                

  int PidStatus=0;    //0:กรณีโค้งน้อยๆ 1:กรณีโค้งเยอะๆ
  int ErrorClear=0;  //0:เคลียร์ Error , 1:ไม่ต้องเคลียร์ 

  int TuneBoxMode=1;       //0:ไม่จูนก่อนปล่อยบล๊อค 1:จูนก่อนปล่อยบล๊อค
  int BlackLine = 1;       //0:เส้นสีดำพื้นสีขาว 1:เส้นสีขาวพื้นสีดำ

  float pvYaw;
  uint8_t rxCnt = 0, rxBuf[8];
  int TurnStatus=1;   //0:เลี้ยวหน่วงเวลา 1:เลี้ยวใช้เข็มทิศ

void setup() {
  mywcx.begin();
  Speed =60;
  ACCSpeed =60;
  SlowSpeed = 40;
  BaseSpeed = Speed; 
  TurnSpeed = Speed;
  SonarSpeed = 40;
  DistanceRef = 4;
  InitialSpeed();
  InitialRef();
  ServoGripUp();
  ServoPut();
  beep(0);
  oled.clear();                 //เคลียร์หน้าจอ
  oled.mode(0);                 //หมุนหน้าจอ 0 องศา
  oled.textSize(1);             //กำหนดขนาดตัวอักษร
  oled.text(0,0,"  Ubon TP Robotics"); //กำหนดข้อความที่จะแสดง
  oled.text(1,0,"      Mix Robot   ");
  oled.text(2,0,"      Piriyalai  ");  
  oled.text(3,0,"     Speed = %d   ",Speed);
  oled.text(4,0,"     ACCSpeed=%d",ACCSpeed);
  oled.text(5,0,"     OK to Start ");
  ShowRobotMode();    //แสดงโหมดที่เลือกไว้ 
  oled.show();                  //แสดงบนหน้าจอ
  SW_OK_Status = No;
  KnobBase=knob();
  while(SW_OK_Status == No)  {  // waiting "OK" button
      if(Read_sw_OK()) {
        ////InitSerial1();
        StartTimer();
        Mode=Mode0; 
        SW_OK_Status = Yes;
        beep(1);
        while(Read_sw_OK())  {  //wait unpress OK button
        if(ReadTimer() >= 2000) {
          beep(2);
          delay(100);
          ServoGripDown();
          ServoGrip();
          delay(1000);
          ServoGripUp();
          ServoPut();
          Show9Analog();
          SW_OK_Status = No;
          }
        }
       }
       //else CheckKnobMode();  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่
       if(SW_A()) 
       {
          ////InitSerial1();
          StartTimer();
          beep(1);
          while(SW_A())  {}  //wait unpress SW A button
          if(ReadTimer() >= SwitchTime) Mode=Mode1;
          else  Mode=Mode2;
          SW_OK_Status = Yes;

       }
       if(SW_B()) 
       {
          ////InitSerial1();
          StartTimer();
          beep(1);
          while(SW_B())  {}  //wait unpress SW A button
          if(ReadTimer() >= SwitchTime) Mode=Mode3;
          else  Mode=Mode4;
          SW_OK_Status = Yes;
       }
  }
  ////zeroYaw();
  BaseSpeed = Speed;
  oled.clear();
  oled.textSize(2);
  oled.text(0,0,"  Starting   ");
  oled.text(1,0,"  Mode=%d   ",Mode);
  oled.show();
  StartTimer2();
  SelectSpeed();

  //ForwardSpeedTime(BaseSpeed,1500);     //เดินหน้า
  //BackwardSpeedTime(BaseSpeed,1500);    //ถอยหลัง
  //BlackLine = 0;                        //0:เส้นสีดำพื้นสีขาว 1:เส้นสีขาวพื้นสีดำ
  //TurnLeft();                           //เลี้ยวซ้าย
  //TurnRight();                          //เลี้ยวขวา
  //UTurnLeft();                          //กลับตัวด้านซ้าย
  //UTurnRight();                         //กลับตัวด้านขวา
  //Left(70,200);                         //เลี้ยวซ้ายแบบหน่วงเวลา
  //Right(70,200);                        //เลี้ยวขวาแบบหน่วงเวลา
  //TracJCStop();                         //เดินเช็ค 1 แยก เจอแยกหยุดทันที
  //TracJC();                             //เดินเช็ค 1 แยก เจอแยกเพื่อเตรียมเลี้ยว
  //TracJCSpeed();                        //เดินเช็ค 1 แยก เจอแยกเพื่อเตรียมตรงไป
  //TracJCR();                            //ใช้เซ็นเซอร์ขวาสุดในการเช็คแยก
  //TracJCL();                            //ใช้เซ็นเซอร์ซ้ายสุดในการเช็คแยก
  //TracJCRLorR();                        //ใช้เซ็นเซอร์ซ้ายหรือขวาสุดในการเช็คแยก
  //TracJCRight();                        //ใช้เซ็นเซอร์ 4 ตัวขวาสุดในการเช็คแยก
  //TracJCLeft();                         //ใช้เซ็นเซอร์ 4 ตัวซ้ายสุดในการเช็คแยก
  //TracJCStopBack();                     //เดินถอยหลังเช็ค 1 แยก เจอแยกหยุดทันที
  //TracJCBack();                         //เดินถอยหลังเช็ค 1 แยก เจอแยกเพื่อเตรียมเลี้ยว
  //TracJCSpeedBack();                    //เดินถอยหลังเช็ค 1 แยก เจอแยกเพื่อเตรียมถอยตรงไป
  //TracSonar();                          //เดินตามเส้นเช็ควัตถุใช้ infrared
  //TracSpeedTime(Speed,500);             //เดินตามเส้นแบบหน่วงเวลา
  //TracSpeedTimeBack(Speed,500);         //เดินถอยหลังตามเส้นแบบหน่วงเวลา
  //TracJCSpeedTime(Speed,20);            //เดินตามเส้นเช็คแยกแบบกำหนดความเร็วการเดินและเวลาในการเดินข้ามแยก
  //TracJCSpeedTimeBack(Speed,20);        //เดินถอยหลังตามเส้นเช็คแยกแบบกำหนดความเร็วการเดินและเวลาในการเดินข้ามแยก
  //ForwardJCStop();                      //เดินเช็ค 1 แยกไม่เช็คเส้น เจอแยกหยุดทันที
  //ForwardJC();                          //เดินเช็ค 1 แยกไม่เช็คเส้น เจอแยกเพื่อเตรียมเลี้ยว
  //CurveLeft(70,80);                     //โค้งอ้อมด้านซ้าย
  //CurveRight(70,80);                    //โค้งอ้อมด้านขวา
  //PutSwingNoGripUp();                   //ปล่อยเข้าช่องไม่ยกแขนขึ้น
  //PutSwing();                           //ปล่อยเข้าช่องพร้อมยกแขนขึ้น
  //RunImpact();                          //วิ่งเข้ากระแทก
  //Grip();                               //คีบกระป๋อง
  //Put();                                //วางกระป๋อง
  //Put0();                               //อ้าแขนนิดหน่อย
  //GripUp();                             //ยกแขนขึ้นสุด
  //GripDown();                           //ยกแขนลงล่างสุด
  //GripDown2();                          //ยกแขนลง 2 cm
  //GripDown3();                          //ยกแขนลง 3 cm
  //GripDown4();                          //ยกแขนลง 4 cm
  //GripDown5();                          //ยกแขนลง 5 cm
  //ShowYaw();
  //TurnLeftDegree(100,90,1); //เลี้ยวซ้ายใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  //TurnRightDegree(100,90,2); //เลี้ยวขวาใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  //CurveLeftDegree(100,90,1); //โค้งซ้ายใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  //CurveRightDegree(100,345,1); //โค้งขวาใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  //CurveLeftDegreeBack(100,90,1); //ถอยโค้งซ้ายใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  //CurveRightDegreeBack(100,270,1); //ถอยโค้งขวาใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  //FinishWaitOK();                 //หยุดและแสดงเวลา รอกดปุ่ม OK
  //TracDegreeSpeedTime(60,20,1000,0);       //เดินหน้า ความเร็ว 60 ทิศทาง 0 องศา เวลา 1000 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //TracDegreeSpeedTimeBack(60,0,1000,1);   //ถอยหลังความเร็ว 60 ทิศทาง 0 องศา เวลา 1000 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //SpinDegree(60,90,1);      //เลี้ยวความเร็ว 60 ทิศทาง 90 องศา 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ 
  //SpinDegreeBack(60,90,1);  //เลี้ยวหลังความเร็ว 60 ทิศทาง 90 องศา 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ 
  //TracJCDegree(60,0,100,0);       //เดินหน้า ความเร็ว 60 ทิศทาง 0 องศา เจอแยกถอยเวลา 100 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //TracJCDegreeBack(60,0,100,0); //ถอยหลังความเร็ว 60 ทิศทาง 0 องศา เจอแยกเดินเวลา 100 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //Finish();   //จบการทำงาน 
 }

void loop() {
  // put your main code here, to run repeatedly: 
  Remote();  
  Finish();
}
void ShowRobotMode()
{
  switch(TuneBoxMode)
  {
    case 0 : oled.text(6,0," 0:Normal Mode ");    //0:ก่อนปล่อยลูกบาศก์ไม่ต้องจูน  
            break;
    case 1 : oled.text(6,0," 1:Tune Mode ");      //1:จูนก่อนปล่อยลูกบาศก์
            break;
  }
}
void CheckKnobMode()  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนโหมดหรือไม่
{
  int Num,KnobDiv=500;
  
  Num = knob()-KnobBase;
  if(((Num>KnobDiv)||(Num<-KnobDiv))&&(knob()>1000)) //ปรับค่าความเร็วจาก knob
  {
    delay(50);
    Num = knob()-KnobBase;
    if(((Num>KnobDiv)||(Num<-KnobDiv))&&(knob()>1000)) //ปรับค่าความเร็วจาก knob
    {
      sound(10000,200);
      Num = abs(knob()-KnobBase);
      if((Num>1000)) //ปรับค่าโหมดจาก knob
      {
        TuneBoxMode = (TuneBoxMode+1)%2;
        ShowRobotMode();        
        oled.show();               //แสดงบนหน้าจอ
        KnobBase=knob();
      }
    }
  }
}
