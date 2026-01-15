void ShowAnalog(){
  glcdClear();
  glcdFillScreen(GLCD_BLUE);
  glcdMode(3);
  setTextSize(1);
  Read7Analog();
  Read5AnalogBack();
  glcd(0,0,"L3=%d ",L3);
  glcd(1,0,"L2=%d ",L2);
  glcd(2,0,"L1=%d ",L1);
  glcd(3,0," C=%d ",C);
  glcd(4,0,"R1=%d ",R1);
  glcd(5,0,"R2=%d ",R2);
  glcd(6,0,"R3=%d ",R3);

  glcd(0,15,"BL2=%d ",BL2);
  //glcd(1,15,"BL1=%d ",BL1);
  //glcd(2,15,"BC=%d ",BC);
  //glcd(3,15,"BR1=%d ",BR1);
  glcd(4,15,"BR2=%d ",BR2);

}
