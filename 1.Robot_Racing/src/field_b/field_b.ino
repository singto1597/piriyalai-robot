#include<popx2.h>
#include <QTRSensors.h>     //ผนวก  Library QTRSensors
#include "robotdefine.h"     //ผนวกค่าจาก  file  robotdefine.h
#define STOP      { motorControl(0,0); }

//int leftValue, rightValue;
//int error, lastError;
//int pidValue;

char Speed, BaseSpeed, ACCSpeed, LeftBaseSpeed, RightBaseSpeed,  TurnSpeed, MaxSpeed;
char Error, PreError, Kp, Kd, Ki, Kt, KpChange; 
int RefL4, RefL3, RefL2, RefL1, RefR1, RefR2, RefR3, RefR4, SumError;
int L4, L3, L2, L1, R1, R2, R3, R4;
long Timer, Timer2;
char SW_OK,Error99Check=0,digital_sw=0;
long BaseTimer0, Timer0;

unsigned long LastTime = 0;
unsigned int Position;


void setup() {
  Speed = 40;
  ACCSpeed = 80;
  BaseSpeed = Speed;
  TurnSpeed= BaseSpeed;
  InitialSpeed();
  InitialRef();
  glcdClear();
  beep();
  glcdMode(2);
  initSystem();      //กำหนด่าเริ่มต้นการทำงาน motor
  //glcd(0,0,"SW_OK_Press");
  sw_OK_press();
  //sw1_press();
  //ShowAnalog();
  //ShowDigital();
  
  
  //TracPIDTimer(Speed, 3000);STOP//s60
  //TracPIDTimer(Speed, 2600);STOP//s70
  //TracPIDTimer(Speed, 2200);STOP//s80
  //TracPIDTimer(Speed, 1970);STOP//s90 //ปล่อยชิดขววานิดนึง
  
  /*RobotStart();
  TracPIDTimer(Speed, 1970);
  TracPIDTimer(ACCSpeed, 1000); 
  TracPIDTimer(Speed, 2070);
  TracPIDTimer(ACCSpeed, 1000); 
  TracJC();ForwardSpeedTime(ACCSpeed, 200);STOP*/ //ความเร็ว100noตะเกียบ
  
  /*RobotStart();
  TracPIDTimer(Speed, 2200);
  TracPIDTimer(ACCSpeed, 350);
  TracPIDTimer(60, 1800);
  TracPIDTimer(80, 2200);
  TracPIDTimer(ACCSpeed, 1000); 
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //ความเร็ว80,60มีตะเกียบ 7.58-7.78s
  
  /*RobotStart();
  TracPIDTimer(70, 400);
  TracPIDTimer(ACCSpeed, 1900);
  TracPIDTimer(60, 1800);
  TracPIDTimer(70, 400);
  TracPIDTimer(ACCSpeed, 1900);
  TracPIDTimer(ACCSpeed, 600); 
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //ความเร็ว100,60มีตะเกียบ 6.97s

  
  RobotStart();
  TracPIDTimer(60, 1000); //60 //1000
  TracPIDTimer(94, 10000);
  STOP //90Work

  //TracPIDTimer(60, 3000);
  //TracPIDTimer(100, 2000);STOP
  //TracPIDTimer(40, 2500); //80
  //TracPIDTimer(ACCSpeed, 1000); 
  //TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP  //ลู่Bไม่มีตะเกียบ6.94

  /*RobotStart();
  TracPIDTimer(70, 500);
  TracPIDTimer(ACCSpeed, 5000); 
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //ลู่Bไม่มีตะเกียบ5.92

  /*RobotStart();
  TracPIDTimer(60, 500);
  TracPIDTimer(ACCSpeed, 5000); 
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //ลู่Cไม่มีตะเกียบ5.58

  /*RobotStart();
  TracPIDTimer(ACCSpeed, 5000); 
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //ลู่Dไม่มีตะเกียบ5.38
  
  /*RobotStart();
  TracPIDTimer(70, 500);
  TracPIDTimer(ACCSpeed, 1900); 
  TracPIDTimer(50, 1900); 
  TracPIDTimer(ACCSpeed, 2500); 
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //B-ความเร็ว100,60มีตะเกียบ 7.04s


  /*RobotStart();
  TracPIDTimer(ACCSpeed, 2200);
  TracPIDTimer(50, 2500);
  TracPIDTimer(ACCSpeed, 2000);
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //D-ความเร็ว100,50มีตะเกียบ 6.66s
  
  /*RobotStart();
  TracPIDTimer(Speed, 1970);
  TracPIDTimer(ACCSpeed, 1200); 
  TracPIDTimer(60, 2000);
  TracPIDTimer(ACCSpeed, 750);
  TracPIDTimer(60, 300);
  TracPIDTimer(ACCSpeed, 750);
  TracJC();ForwardSpeedTime(ACCSpeed, 100);STOP*/ //A-ความเร็ว100,50มีสองตะเกียบ 
  /*
  RobotStart();
  TracPIDTimer(ACCSpeed, 1970);STOP*/
  //TracJC();ForwardSpeedTime(ACCSpeed, 300)STOP    //ใช้ตอนเข้าเส้นชัย

}

void loop() {
  //TracJCStop();
  //TracJCSpeed();
  

}

void initSystem() {
  for (int pins = 4; pins <= 7; pins++) {
    pinMode(pins, OUTPUT);
    digitalWrite(pins, LOW);
  }
}

void motorControl(int speedLeft, int speedRight) {
  bool LD, RD;
  LD = (speedLeft >= 0 ? false : true);
  RD = (speedRight >= 0 ? false : true);
  speedLeft = abs(speedLeft);
  speedRight = abs(speedRight);
  digitalWrite(dirA, LD);           //digital(5,LOW)    LOW =  เดินหน้า   HIGHT =  ถอยหลัง, 0 LOW False,  1 HIGHT True
  analogWrite(pwmA, speedLeft);
  digitalWrite(dirB, RD);
  analogWrite(pwmB, speedRight);

}


void Stop(int a) {
  motor_stop(ALL);
  delay(a);
}
