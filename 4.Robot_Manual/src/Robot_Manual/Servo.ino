void ServoGrip()
{
  servo(1,45);
}
void ServoPut0() //อ้าแขนน้อยๆให้บอลหล่น
{
  servo(1,70);
}
void ServoPut()
{
  servo(1,130);
}
void ServoGripUp()
{
  servo(2,20);
}
void ServoGripDown() //ยกแขนลงต่ำสุด
{
  servo(2,135);
}
void ServoGripDown2() //ยกแขนลง 2 cm
{
  servo(2,115);
}
void ServoGripDown3() //ยกแขนลง 3 cm
{
  servo(2,110);
}
void ServoGripDown4() //ยกแขนลง 4 cm
{
  servo(2,97);
}
void ServoGripDown5() //ยกแขนลง 5 cm
{
  servo(2,87);
}
void Grip()
{
  OffMotor();
  ServoGrip();
  delay(300); 
}
void Put()
{
  OffMotor();
  ServoPut();
  delay(200);   
}
void GripUp()
{
  OffMotor(); 
  ServoGripUp();
  delay(300);
}
void GripDown()
{
  OffMotor(); 
  ServoGripDown();
  delay(300);
}
void GripDown2()
{
  OffMotor(); 
  ServoGripDown2();
  delay(300);
}
void GripDown3()
{
  OffMotor(); 
  ServoGripDown3();
  delay(300);
}
void GripDown4()
{
  OffMotor(); 
  ServoGripDown4();
  delay(300);
}
void GripDown5()
{
  OffMotor(); 
  ServoGripDown5();
  delay(300);
}
void PutSwingNoGripUp()   //ปล่อยเข้าช่องไม่ยกแขนขึ้น
{
  ServoGripDown();
  delay(60);
  Put();
}
void PutSwing()         //ปล่อยเข้าช่องพร้อมยกแขนขึ้น
{
  PutSwingNoGripUp();
  GripUp(); 
}
void RunImpact()    //วิ่งเข้ากระแทก
{
  ServoGripDown();
  ServoGrip();
  BackwardSpeedTime(Speed,100);
  TracSpeedTime(Speed,300);
  BackwardSpeedTime(Speed,150);
  ServoGripUp(); 
  ServoPut();
}
void Put0()
{
  OffMotor();
  ServoPut0();
  delay(370);
}
