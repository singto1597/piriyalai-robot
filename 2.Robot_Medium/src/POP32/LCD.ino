void ShowAnalog(){ //แสดงค่าเซ็นเซอร์
  oled.clear();  //เคลียร์หน้าจอ
  //oled.(GLCD_BLUE);  //กำหนดสีพื้นหลัง
  //oled.color(GLCD_RED); //กำหนดสีตัวอักษร
  oled.textSize(1); //กำหนดขนาดตัวอักษร
  oled.mode(0);  //กำหนดทิศทางของจอ
  oled.dim(true);
  
  Read7Analog();
  Read5AnalogBack();
  oled.text(0,0,"L3=%d",L3);
  oled.text(1,0,"L2=%d",L2); 
  oled.text(2,0,"L1=%d",L1);
  oled.text(3,0,"C=%d",C);
  oled.text(4,0,"R1=%d",R1);
  oled.text(5,0,"R2=%d",R2);
  oled.text(6,0,"R3=%d",R3);

  oled.text(0,10,"BL2=%d",BL2); 
  //oled.text(9,0,"BL1=%d",BL1);
  //oled.text(10,0,"BC=%d",BC);
  //oled.text(11,0,"BR1=%d",BR1);
  oled.text(1,10,"BR2=%d",BR2);
  oled.show();
  beep();
}
