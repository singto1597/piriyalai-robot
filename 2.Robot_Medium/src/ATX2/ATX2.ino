#include<ATX2.h>
int L3,L2,L1,C,R1,R2,R3;      //Front Sensor  7  pcs
int BL2,BL1,BC,BR1,BR2;      //Back Sensor  5  pcs
int RefL3=650, RefL2=650, RefL1=650, RefC=650, RefR1=650, RefR2=700, RefR3=650;
int RefBL2=700, RefBL1=650, RefBC=650, RefBR1=650, RefBR2=650;

int RobotSpeed=40;
int SlowSpeed=25;
int AccSpeed=95;
int TurnSpeed=100;
int MoveSpeed=50;
int BackSpeed=85;

int LeftSpeed, RightSpeed, LeftSpeedBack, RightSpeedBack;
int Kp = 6, Ki = 0, Kd = 30, Error, PreError, Integral;
long BaseTimer0, Timer0;

void setup() {
  XIO();        //ประกาศ IO
  beep(0);      //เสียงบี๊บ
  servo(4,140);
  ShowAnalog();
  sw_ok_press();    //รอจนกว่าจะมีการกดปุ่ม sw ok
  beep(0);
  delay(100);
 
  //Box1();
  //Box2();
  //Box3();
  //Box4();
  //Box5();
  TrackSpeedTimer(70, 700);
  //MaxBackward(70,250);
  //KickFront();
  MotorStop();
  

}


void loop() {
  // put your main code here, to run repeatedly:
/*sw_ok_press();
beep(0);
delay(500);
ForWard(RobotSpeed,500);
TurnLeft();*/
}
