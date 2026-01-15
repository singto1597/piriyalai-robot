void Auto()
{
  oled.clear();
  oled.textSize(2);
  oled.text(0,0,"    Can %d",CanNumber);
  oled.text(1,0,"  Auto Mode  ");
  oled.show();
  switch(CanNumber)
  {
    case 1 : Can1(); break;
    case 2 : Can2(); break;
    case 3 : Can3(); break;
    case 4 : Can4(); break;
    case 5 : Can5(); break;
    case 6 : Can6(); break;
    case 7 : Can7(); break;
  }
  CanNumber++;
}
