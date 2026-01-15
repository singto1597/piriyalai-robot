void ShowSonar()
{
  oled.clear();
  oled.text(0,0,"Sonar=%d",Sonar());
  oled.show();                  //แสดงบนหน้าจอ
}
