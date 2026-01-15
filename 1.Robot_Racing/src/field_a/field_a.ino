#include<popx2.h>
#include "QTRSensors.h"
#include "robotdefine.h"
#define STOP      { motorControl(0,0); }

QTRSensorsRC qtr((unsigned char[]) {
  30, 29, 28, 27, 26, 25, 24, 18
}, NUM_SENSORS, TIMEOUT, EPIN);



int minValue[8] = {249, 162, 171, 123, 123, 171, 126, 210};
int maxValue[8] = {2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,};

int leftValue, rightValue;
int error, lastError;
int pidValue;

unsigned long LastTime = 0;
unsigned int Position;
unsigned int sensorValue[NUM_SENSORS];

int mode = 0;
const char* modeName[] = {"Read Sensor    ", "Sensor Monitor", "Check Motor    ", "Ready To Go    "};


void setup() {
  glcdClear();
  glcdMode(2);
  initSystem();      //กำหนด่าเริ่มต้นการทำงาน motor
  //glcd(0,0,"SW_OK_Press");
  //readSensor();    // อ่านค่า Sensor  ทำครั้งเดียว
  //sw_OK_press();
  //sw1_press();

  
}

void loop() {
  beep();
  
  while(1){
    if (knob() <= 500){

      glcd(15,0,"Read Sensor");
      if(!digitalRead(SWITCH) == 1){
        glcdClear();
        readSensor();
      }
    }
    else{
      glcd(15,0,"Ready to go");
      if(!digitalRead(SWITCH) == 1){
        beep();
        break;
      }
    }
  }
  
  /*
  while (1) {
    mode = map(knob(), 0, 1023, 0, 3); // เลือกโหมดจาก knob
    glcdClear();
    glcd(15,1, modeName[mode]);
  
    if (!digitalRead(SWITCH)) {
      beep();
      if (mode == 0) readSensor();
      else if (mode == 1) showSensor();
      else if (mode == 2) testMotor();
      else if (mode == 3) break; // เริ่มวิ่งจริง
    }
  }
  */
  glcdClear();
    
  setValueQTR();
  delay(100);
  PidTimer(100, 0.025, 0.30, 100, 0 );
  
  
  //PidTimer(140, 0.046, 0.48, 6800 , 0);
  PidTimer(200, 0.100, 0.58, 100 , 0);
  PidTimer(240, 0.100, 0.58, 200 , 0); //140 120
  PidTimer(140, 0.100, 0.65, 500 , 0);
  //ผ่านโค้ง 1
  
  
  
  PidTimer(200, 0.070, 0.56, 420 , 0);
  PidTimer(145, 0.052, 0.72, 3400 , 0); //3350
  //ผ่านโค้ง 5

  
  
  PidTimer(240, 0.070, 0.56, 180 , 0);
  
  PidTimer(140, 0.050, 0.60, 700 , 0);
  
  PidTimer(240, 0.070, 0.56, 220 , 0);
  
  PidTimer(120, 0.050, 0.60, 700 , 0);
  //ผ่านโค้ง 7
  PidTimer(145, 0.052, 0.72, 6000 , 0);
  /*
  PidTimer(200, 0.070, 0.56, 1500 , 0);
  PidTimer(140, 0.050, 0.60, 1500 , 0);
  //PidTimer(140, 0.040, 0.58, 600 , 0);
  //PidTimer(200, 0.062, 0.90, 2500 , 0); //700
  
  */
  STOP
  /*
  while(1){
    //stdPID(80, 0.025, 0.45);
    //stdPID(100, 0.060, 0.50 );
    //stdPID(120, 0.040, 0.50 );
    stdPID(140, 0.048, 0.60); 
    //stdPID(160, 0.050, 0.56 ); 
    //stdPID(160, 0.100, 0.56 ); 
    //stdPID(180, 0.100, 0.80 );
    //stdPID(200, 0.059, 0.50 );
    //stdPID(220, 0.088, 0.58 );
    //stdPID(254, 0.120, 0.58);
    //stdPID(250, 0.075, 0.50 );
  }
  */
}
