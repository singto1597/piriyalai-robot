#include <POP32.h>
#include "Adafruit_TCS34725.h"
////////////////////////////////////////////////////////////
// our RGB -> eye-recognized gamma color
  byte gammatable[256];

static uint16_t color16(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t _color;
  _color = (uint16_t)(r & 0xF8) << 8;
  _color |= (uint16_t)(g & 0xFC) << 3;
  _color |= (uint16_t)(b & 0xF8) >> 3;
  return _color;
}
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
/////////////////////////////////////////////////////////////

int Speed,NewSpeed, SlowSpeed, ACCSpeed, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, DistanceRef;
int Error, PreError, Kp, Kd, Ki, Kt, KpB, KdB, KiB, KtB, BackLeftBaseSpeed, BackRightBaseSpeed, KpChange; 
int RefL3, RefL2, RefL1, RefC, RefR1, RefR2, RefR3, SumError, RefBL, RefBR;
int L3, L2, L1, C, R1, R2, R3, BL, BR;
long Timer, Timer1, Timer2, Timer3, Timer4;
int SW_OK_Status,digital_sw=0;
int RefLimitSwitch;
  
#define SW_pin 18
#define No 0
#define Yes 1

#define Mode1R 0
#define Mode1L 1
#define Mode2R 2
#define Mode2L 3
#define Mode3 4
  
int RobotMode=5;    //0:เซ็นเซอร์&กล้อง เช็คทีละ 1 ช่องแล้วเลี้ยวขวา 
                    //1:เซ็นเซอร์&กล้อง เช็คทีละ 1 ช่องแล้วเลี้ยวซ้าย 
                    //2:กล้องอย่างเดียว ยังไม่สมบูรณ์
                    //3:เซ็นเซอร์&กล้อง วิ่งตรงยาวเลี้ยวขวา แต่ยังเข้าช่องไม่ได้
                    //4:เซ็นเซอร์&กล้อง วิ่งตรงยาวเลี้ยวซ้าย แต่ยังเข้าช่องไม่ได้
                    //5:เซ็นเซอร์&RGB เช็คทีละ 1 ช่องแล้วเลี้ยวขวา        :กดสวิช A(สีส้ม) แป๊บเดียว
                    //6:เซ็นเซอร์&RGB เช็คทีละ 1 ช่องแล้วเลี้ยวซ้าย        :กดสวิช A(สีส้ม) แช่ไว้ 1 วินาที
                    //7:เซ็นเซอร์&RGB วิ่งตรงยาวเลี้ยวขวา แต่ยังเข้าช่องไม่ได้ :กดสวิช B(สีขาว) แป๊บเดียว
                    //8:เซ็นเซอร์&RGB วิ่งตรงยาวเลี้ยวซ้าย แต่ยังเข้าช่องไม่ได้ :กดสวิช B(สีขาว) แช่ไว้ 1 วินาที
/*************** กล้อง *******************/
#define XrefCenter  160  
#define YrefCenter  120//80
#define RefHeight   60
#define Refwidth  120
int xCenter,yCenter,width,height;
int xOrigin,yOrigin,xTarget,yTarget;
/**************************RGB*****************/
int RedNumber=0,YellowNumber=0,BlueNumber=0,GreenNumber=0;
int FloorColor,ColorCheck=0,BridgeStatus=0;
  
long RefBlue,RefGreen,RefWhite,RefBlack,RefYellow,RefRed;
#define Blue 0
#define Green 1
#define Black 2
#define White 3
#define Yellow 4
#define Red 5

int ColorLevel[6]={0,1,2,3,4,5}; //เก็บค่าลำดับของค่าสีต่างๆ Blue,Green,White,Black,Yellow,Red;
#define RGB_Mode  1  //0:เช็ค RGB แบบเดิมค่าสีต้องเรียง 1:เช็คแบบอัตโนมัติค่าสีไม่จำเป็นต้องเรียง 

int modeSelect = 0;
int knobValue = 0;

void setup() {

  Speed = 35;
  ACCSpeed =100;
  SlowSpeed = 50;
  NewSpeed = 42; //25
  BaseSpeed = Speed; 
  TurnSpeed = 100;
  InitialSpeed();
  InitialRef();
  if(RobotMode<5){ //ใช้กล้อง
    //InitialHuskyslens();      //initial กล้อง huskylens
    //Color_Recognition_mode();    //การจดจำสี
  }
  else{            //ใช้ RGB
    SetupTCS34725();
    delay(100); 
    ShowRGBColor();
    delay(1000);
  }
  beep(0);
  //TestServo();                  //ทดสอบชุดปล่อยและยกธง
  oled.clear();                 //เคลียร์หน้าจอ
  oled.mode(0);                 //หมุนหน้าจอ 0 องศา
  oled.dim(true);               //ปรับความสว่างปกติ
  oled.textSize(1);             //กำหนดขนาดตัวอักษร
  oled.text(0,0," PHIRIYALAI SCHOOL"); //กำหนดข้อความที่จะแสดง
  oled.text(1,0," High 4 Wheels POP32");
  oled.text(2,0,"      PR_ROBOT    ");
  oled.text(3,0,"     Speed = %d   ",Speed);
  oled.text(4,0,"     ACCSpeed=%d",ACCSpeed);
  oled.text(5,0,"       Mode = %d   ",RobotMode);
  oled.show();                  //แสดงบนหน้าจอ

  /*
  SW_OK_Status = No;
  while(SW_OK_Status == No)  {  // waiting "OK" button
      if(Read_sw_OK()) {
        SW_OK_Status = Yes;
        StartTimer();
        beep(1);
        while(Read_sw_OK())  {  //wait unpress OK button
        if(ReadTimer() >= 2000) {
          beep(2);
          TestServo();                  //ทดสอบชุดปล่อยและยกธง
          Show7Analog();
          SW_OK_Status = No;
          }
          else {SW_OK_Status = Yes;}   //ตามโหมดที่ตั้งไว้   
        }
       }
       if(SW_A()){ 
          StartTimer();
          beep(1);
          while(SW_A())  {}  //wait unpress SW A button
          if(ReadTimer() >= 1000) RobotMode=6; //6:เซ็นเซอร์&RGB เช็คทีละ 1 ช่องแล้วเลี้ยวซ้าย
          else  RobotMode=5;  //5:เซ็นเซอร์&RGB เช็คทีละ 1 ช่องแล้วเลี้ยวขวา
          SW_OK_Status = Yes;

       }
       if(SW_B()){
          StartTimer();
          beep(1);
          while(SW_B())  {}  //wait unpress SW A button
          if(ReadTimer() >= 1000) RobotMode=8; //8:เซ็นเซอร์&RGB วิ่งตรงยาวเลี้ยวซ้าย แต่ยังเข้าช่องไม่ได้
          else  RobotMode=7;  //7:เซ็นเซอร์&RGB วิ่งตรงยาวเลี้ยวขวา แต่ยังเข้าช่องไม่ได้
          SW_OK_Status = Yes;
       }
  }
  */

  while (1) {
    knobValue = knob();
    modeSelect = map(knobValue, 0, 1023, 0, 5); 
    oled.text(7,0,"   TESTMode = %d   ",modeSelect);
    oled.show();
    if (SW_B()) {
      StartTimer();
      beep(1);
        while (SW_B()) {
          if (ReadTimer() >= 2000) {   // กดค้าง >= 2 วินาที
            beep(2);
            TestServo();
            Show7Analog();
            break; // ออกจาก while(1)
          }
        }
      runSelectedMode(modeSelect);
      break;
    }
    if (SW_A()) {
      StartTimer();
      beep(1);
      while (SW_A()) {}
      if (ReadTimer() >= 1000) RobotMode = 6;
      else RobotMode = 5;
      break;
    }
    /*
    if (SW_B()) {
      StartTimer();
      beep(1);
      while (SW_B()) {}
      if (ReadTimer() >= 1000) RobotMode = 8;
      else RobotMode = 7;
      break;
    }*/
  }

  BaseSpeed = Speed;
  oled.clear();
  oled.textSize(2);
  oled.text(0,0,"  Starting   ");
  oled.text(1,0,"   Mode=%d   ",RobotMode);
  oled.show();
  StartTimer2();
  
  //ForwardSpeedTime(Speed,3000); Finish();//เดินหน้าด้วยความเร็ว 30% นาน 5000 ms(5 วินาที)
  //BackwardSpeedTime(Speed,3000); Finish();//ถอยหลังด้วยความเร็ว 30% นาน 5000 ms(5 วินาที)
  //TurnLeft();
  //TurnRight();
  //UTurnLeft();
  //UTurnRight();
  //Trac1BlockRGB(Speed,1250);

  //TracJCStop();
  //TracJC();
  //TracJCBlack();
  //ForwardSpeedTime(Speed,580);
  //TracFloorRGB(Speed,580);
  //TracSpeedTime(Speed,580);
  //CheckColor0();
  //delay(1000);
  /*FlagDown() ;
  delay(1000);
  FlagUp();*/
  //Finish();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Function();        //รวบรวมฟังก์ชันต่างๆ ที่ใช้ประจำ

  switch(RobotMode){
    //case 2: AutoCamera(); break;        //กล้องอย่างเดียว
    //case 3: AutoLane(); break;          //เซ็นเซอร์&กล้อง วิ่งตรงยาว 3:เลี้ยวขวา 4:เลี้ยวซ้าย
    //case 4: AutoLane(); break;          //เซ็นเซอร์&กล้อง วิ่งตรงยาว 3:เลี้ยวขวา 4:เลี้ยวซ้าย
    case 5: AutoRightLeftRGB(); break; //เซ็นเซอร์&RGB เช็คทีละ 1 ช่อง 5:เลี้ยวขวา,6:เลี้ยวซ้าย
    case 6: AutoRightLeftRGB(); break; //เซ็นเซอร์&RGB เช็คทีละ 1 ช่อง 5:เลี้ยวขวา,6:เลี้ยวซ้าย  
    case 7: AutoLaneRGB(); break;      //เซ็นเซอร์&RGB วิ่งตรงยาว 7:เลี้ยวขวา 8:เลี้ยวซ้าย
    case 8: AutoLaneRGB(); break;      //เซ็นเซอร์&RGB วิ่งตรงยาว 7:เลี้ยวขวา 8:เลี้ยวซ้าย
    //default: AutoRightLeft(); break;    //เซ็นเซอร์&กล้อง เช็คทีละ 1 ช่อง 0:เลี้ยวขวา,1:เลี้ยวซ้าย
    
  }
  Finish();
}
