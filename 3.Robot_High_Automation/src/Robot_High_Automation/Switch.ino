char Read_sw_OK()  {
  if (SW_OK()) return(1);     //press sw OK
  //else if(digitalRead(18)==0) {digital_sw = 1; return(1);}  //press digital sw 
  else return(0);
}
void sw_ok_unpress()  {
  while(Read_sw_OK()) {delay(10);}
}
void Wait_sw_ok_press()  {
  while(Read_sw_OK()==0) {delay(10);}
}

void runSelectedMode(int mode) {
  switch (mode) {
    case 0: // เดินหน้า
      ForwardSpeedTime(Speed, 1600);
      Finish();
      break;
    case 1: // ถอยหลัง
      BackwardSpeedTime(Speed, 1600);
      Finish();
      break;
    case 2: // เลี้ยวซ้าย
      TurnLeft();
      Finish();
      break;
    case 3: // เลี้ยวขวา
      TurnRight();
      Finish();
      break;
    case 4: // U-Turn ซ้าย
      UTurnLeft();
      Finish();
      break;
    case 5: // U-Turn ขวา
      UTurnRight();
      Finish();
      break;
  }
}