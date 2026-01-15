int ManualSpeed = 60;
int ManualTurnSpeed = 60;
/*
void Remote()
{
  oled.textSize(3);
  oled.clear();
  oled.text(0, 0, "S=%d  ", ManualSpeed);
  oled.text(1, 0, "T=%d  ", ManualTurnSpeed);
  oled.show();
  while(1)
  {
    mywcx.getButton();
    if(mywcx.R2)  //เปลี่ยนโหมดเป็นอัตโนมัติ
    {
      StartTimer();
      while(mywcx.R2){}
      if(ReadTimer() >= 1000){
        Auto();
      }
      
      oled.textSize(3);
      oled.clear();
      oled.text(0, 0, "S=%d  ", ManualSpeed);
      oled.text(1, 0, "T=%d  ", ManualTurnSpeed);
      oled.show();
      while(mywcx.getButton());
    }
    else if(mywcx.LU)  //เดินหน้า
    {
      ForwardSpeedTime(ManualSpeed,1);
      while(mywcx.getButton());
    }
    else if(mywcx.LD)  //ถอยหลัง
    {
      BackwardSpeedTime(ManualSpeed,1);
      while(mywcx.getButton());
    }
    else if(mywcx.LL)  //เลี้ยวซ้าย
    {
      SL(ManualTurnSpeed);
      while(mywcx.getButton());
    }
    else if(mywcx.LR)  //เลี้ยวขวา
    {
      SR(ManualTurnSpeed);
      while(mywcx.getButton());
    }
    else if(mywcx.LT)  //เลี้ยวซ้ายช้า
    {
      SL(20);
      while(mywcx.getButton());
    }
    else if(mywcx.RT)  //เลี้ยวขวาช้า
    {
      SR(20);
      while(mywcx.getButton());
    }
    else if(mywcx.RU)  //ยกแขนขึ้น
    {
      ServoGripUp();
      while(mywcx.getButton());
    }
    else if(mywcx.RD)  //ยกแขนลง
    {
      ServoGripDown();
      while(mywcx.getButton());
    }
    else if(mywcx.RL)  //คีบ
    {
      ServoGrip();
      while(mywcx.getButton());
    }
    else if(mywcx.RR)  //ปล่อย
    {
      ServoPut();
      while(mywcx.getButton());
    }
    else if(mywcx.R1)  //เดินช้าๆ
    {
      ForwardSpeedTime(30,1);
      while(mywcx.getButton());
    }
    else  if(mywcx.L1) //เพิ่มความเร็วตอนวิ่ง
    {
      ManualSpeed += 5;
      ManualSpeed = constrain(ManualSpeed, 5, 100);
      oled.text(0, 0, "S=%d  ", ManualSpeed);
      oled.display();
      beep();
      //delay(250);
      while(mywcx.getButton());
    }
    else if(mywcx.L2) //ลดความเร็วตอนวิ่ง
    {
      ManualSpeed -= 5;
      ManualSpeed = constrain(ManualSpeed, 5, 100);
      oled.text(0, 0, "S=%d  ", ManualSpeed);
      oled.display();
      beep();
      //delay(250);
      while(mywcx.getButton());
    }
    else MotorStop();
  }
}
*/

void Remote()
{
  oled.textSize(3);
  oled.clear();
  oled.text(0, 0, "S=%d  ", ManualSpeed);
  oled.text(1, 0, "T=%d  ", ManualTurnSpeed);
  oled.show();

  while (1) {
    mywcx.getButton();

    // === นับจำนวนปุ่มที่กด ===
    int pressedCount = 0;
    if (mywcx.LU) pressedCount++;
    if (mywcx.LD) pressedCount++;
    if (mywcx.LL) pressedCount++;
    if (mywcx.LR) pressedCount++;

    if (mywcx.LT) pressedCount++;
    if (mywcx.RT) pressedCount++;

    // === โหมดหลายปุ่ม ===
    if (pressedCount >= 2) {
      if (mywcx.LU && mywcx.RT) {
        // เดินหน้า + เลี้ยวขวา
        FD2(ManualSpeed, ManualSpeed / 6); // ซ้ายเร็วกว่า
      }
      else if (mywcx.LU && mywcx.LT) {
        // เดินหน้า + เลี้ยวซ้าย
        FD2(ManualSpeed / 2, ManualSpeed); // ขวาเร็วกว่า
      }
      else if (mywcx.LD && mywcx.RT) {
        // ถอยหลัง + เลี้ยวขวา
        BK2(ManualSpeed, -ManualSpeed / 6);
      }
      else if (mywcx.LD && mywcx.LT) {
        // ถอยหลัง + เลี้ยวซ้าย
        BK2(ManualSpeed / 2, -ManualSpeed);
      }

    }

    // === โหมดปกติ (ปุ่มเดียว) ===
    else {
      if (mywcx.LU) ForwardSpeedTime(ManualSpeed,1);
      else if (mywcx.LD) BackwardSpeedTime(ManualSpeed,1);
      else if (mywcx.LL) SL(ManualTurnSpeed);
      else if (mywcx.LR) SR(ManualTurnSpeed);
      else if (mywcx.LT) SL(20);
      else if (mywcx.RT) SR(20);
      else if (mywcx.R1) ForwardSpeedTime(30,1);
      else MotorStop();
    }

    // === ส่วนอื่น ๆ เช่น แขน, เพิ่มลดสปีด ===
    if (mywcx.RU) ServoGripUp();
    if (mywcx.RD) ServoGripDown();
    if (mywcx.RL) ServoGrip();
    if (mywcx.RR) ServoPut();

    if (mywcx.L1) {
      ManualSpeed = constrain(ManualSpeed + 5, 5, 100);
      oled.text(0, 0, "S=%d  ", ManualSpeed);
      oled.show();
      beep();
    }
    if (mywcx.L2) {
      ManualSpeed = constrain(ManualSpeed - 5, 5, 100);
      oled.text(0, 0, "S=%d  ", ManualSpeed);
      oled.show();
      beep();
    }
    if(mywcx.R2)  //เปลี่ยนโหมดเป็นอัตโนมัติ
    {
      Auto();
      while(mywcx.getButton());
      oled.textSize(3);
      oled.clear();
      oled.text(0, 0, "S=%d  ", ManualSpeed);
      oled.text(1, 0, "T=%d  ", ManualTurnSpeed);
      oled.show();
    }

    //delay(20); // กัน loop เร็วเกิน
  }
}
