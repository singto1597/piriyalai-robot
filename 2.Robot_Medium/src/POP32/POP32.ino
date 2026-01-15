#include <POP32.h> //เพิ่มไลบราลี
int L3,L2,L1,C,R1,R2,R3;  //ประกาศตัวแปรเซ็นเซอร์หน้า 7 ตัว
int BL2,BL1,BC,BR1,BR2;  //ประกาศตัวแปรเซ็นเซอร์หลัง 5 ตัว

int RefL3=2000, RefL2=2000, RefL1=2000, RefC=2000, RefR1=2000, RefR2=2000, RefR3=2000;
int RefBL2=2000, RefBL1=2000, RefBC=2000, RefBR1=2000, RefBR2=2000;

int RobotSpeed=40;
int SlowSpeed=25;
int AccSpeed=95;
int TurnSpeed=100;
int MoveSpeed=50;
int BackSpeed=85;

int LeftSpeed,RightSpeed,LeftSpeedBack,RightSpeedBack;
int Kp=10,Ki=0,Kd=30,Error,PreError,Integral;
long BaseTimer0,Timer0;
void setup() {
  beep(0);  //เสียงบี๊บ
  //KickFront();
  //KickBSack();
  //ShowAnalog(); //แสดงค่าเซ็นเซอร์
  servo(1,140); 
  //sw_ok_press();  //รอจนกว่าจะมีการกดปุ่ม sw ok
  while(!SW_A() && !SW_OK()){}
  //beep(0);
  delay(100);
  //MaxForward(AccSpeed,120);
  //MaxForward(AccSpeed,540);
  //MaxBackward(70,200);

  //BackwardBalance(SlowSpeed,310);
  //ForwardBalance(RobotSpeed,155);

  //ForwardBalance(SlowSpeed,380);

  //TurnLeft();
  //TurnRight();
  //UTurn();

  //TurnLeftTime(137);

  //ForwardBalance(70,350);

  //TrackJCBalance(60,310);

  Box1();
  Box2();
  Box3();
  Box4();
  //Box5();

  //test();
  //TrackSpeedTimer(50,1000);
  //KickFront();
  MotorStop();
}

void loop() {
  // put your main code here, to run repeatedly:

} 
