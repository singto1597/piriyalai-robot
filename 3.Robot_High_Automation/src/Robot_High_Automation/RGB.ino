/////////// RGB Function ////////////////////////////
void SetupTCS34725()
{
  delay(100);
  Serial.begin(115200); 
  oled.text(0, 0, "Color Sensor Test!");

  if (tcs.begin()) {
    oled.text(1, 0, "Found sensor!");
  } else {
    oled.text(1, 0, "No TCS34725 found!");
    //while (1); // halt!
  }
  oled.show();
  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
  tcs.setGain(TCS34725_GAIN_4X);
}
uint16_t ReadRGB()
{
  uint16_t clear, red, green, blue;

  delay(60);  // takes 50ms to read

  tcs.getRawData(&red, &green, &blue, &clear);

  /*Serial.print("C:\t"); Serial.print(clear);
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.print(blue);
    Serial.println();*/

  // Figure out some basic hex code for visualization

  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  uint16_t _color = color16((int)r, (int)g, (int)b);
  return (_color);
}
void ShowRGB()
{
  long RGBColor = ReadRGB();
  oled.clear();
  oled.text(0, 0, "RGB=%l", RGBColor);
  oled.show();
}
void ShowRGBColor()
{
  int ColorRGB= ReadRGB();//CheckColorRGB();
  oled.clear();
   oled.text(0, 0, "Color=%d    ",ColorRGB);
   oled.show();
}
int CheckColorRGB()
{
  if(RGB_Mode==0) return(CheckColorRGBNornal());
  else return(CheckColorRGB_Auto());
}
int CheckColorRGBNornal()
{
  long RGBColor = ReadRGB();
  //glcdClear();
  if (RGBColor < (RefBlue+500)&&RGBColor > (RefBlue-500) )
  {
    FloorColor = Blue; //น้ำเงิน
    //glcd(0,0,"CanColor=Blue");
  }
  else if (RGBColor < (RefGreen+500)&&RGBColor > (RefGreen-500))
  {
    FloorColor = Green; //เขียว
    //glcd(0,0,"CanColor=Green");
  }
  else if (RGBColor < (RefBlack + RefWhite) / 2)
  {
    FloorColor = Black; //ดำ
    //glcd(0,0,"CanColor=Black");
  }
  else if (RGBColor < (RefWhite + RefYellow) / 2)
  {
    FloorColor = White; //ขาว
    //glcd(0,0,"CanColor=White");
  }
  else if (RGBColor < (RefYellow + RefRed) / 2)
  {
    FloorColor = Yellow; //เหลือง
    //glcd(0,0,"CanColor=Yellow");
  }
  else
  {
    FloorColor = Red; //แดง
    //glcd(0,0,"CanColor=Red");
  }
  return (FloorColor);
}
/////////////////////////////////////////////
void CheckColorLevel()  //เช็คลำดับค่าสี Blue,RGreen,White,Black,Yellow,Red;
{
  int Number;
  
  Number = 0;
  ColorLevel[Number] = 0;  //Blue
  if(RefBlue>RefGreen) ColorLevel[Number]++;
  if(RefBlue>RefBlack) ColorLevel[Number]++; 
  if(RefBlue>RefWhite) ColorLevel[Number]++;
  if(RefBlue>RefYellow) ColorLevel[Number]++;
  if(RefBlue>RefRed) ColorLevel[Number]++;
  Number = 1;
  ColorLevel[Number] = 0;  //Green
  if(RefGreen>RefBlue) ColorLevel[Number]++;
  if(RefGreen>RefBlack) ColorLevel[Number]++; 
  if(RefGreen>RefWhite) ColorLevel[Number]++;
  if(RefGreen>RefYellow) ColorLevel[Number]++;
  if(RefGreen>RefRed) ColorLevel[Number]++;
  Number = 2;
  ColorLevel[Number] = 0;  //Black
  if(RefBlack>RefBlue) ColorLevel[Number]++;
  if(RefBlack>RefGreen) ColorLevel[Number]++; 
  if(RefBlack>RefWhite) ColorLevel[Number]++;
  if(RefBlack>RefYellow) ColorLevel[Number]++;
  if(RefBlack>RefRed) ColorLevel[Number]++;
  Number = 3;
  ColorLevel[Number] = 0;  //White
  if(RefWhite>RefBlue) ColorLevel[Number]++;
  if(RefWhite>RefGreen) ColorLevel[Number]++; 
  if(RefWhite>RefBlack) ColorLevel[Number]++;
  if(RefWhite>RefYellow) ColorLevel[Number]++;
  if(RefWhite>RefRed) ColorLevel[Number]++;
  Number = 4;
  ColorLevel[Number] = 0;  //Yellow
  if(RefYellow>RefBlue) ColorLevel[Number]++;
  if(RefYellow>RefGreen) ColorLevel[Number]++; 
  if(RefYellow>RefBlack) ColorLevel[Number]++;
  if(RefYellow>RefWhite) ColorLevel[Number]++;
  if(RefYellow>RefRed) ColorLevel[Number]++;
  Number = 5;
  ColorLevel[Number] = 0;  //Red
  if(RefRed>RefBlue) ColorLevel[Number]++;
  if(RefRed>RefGreen) ColorLevel[Number]++; 
  if(RefRed>RefBlack) ColorLevel[Number]++;
  if(RefRed>RefWhite) ColorLevel[Number]++;
  if(RefRed>Yellow) ColorLevel[Number]++;
}
int CheckColorRGB_Auto()
{
  int i,ColorMin,ColorMax;
  long RefMin,RefMax,RGBRef;
  long RGBColor = ReadRGB();

  CheckColorLevel();
  for(i=0; i<5; i++)
  {
    if(ColorLevel[0]==i)  //เจออันแรก
    {
      RefMin = RefBlue;
      ColorMin = Blue;
    }
    else if(ColorLevel[1]==i)  //เจออันแรก
    {
      RefMin = RefGreen;
      ColorMin = Green;
    }
    else if(ColorLevel[2]==i)  //เจออันแรก
    {
      RefMin = RefBlack;
      ColorMin = Black;
    }
    else if(ColorLevel[3]==i)  //เจออันแรก
    {
      RefMin = RefWhite;
      ColorMin = White;
    }
    else if(ColorLevel[4]==i)  //เจออันแรก
    {
      RefMin = RefYellow;
      ColorMin = Yellow;
    }
    else if(ColorLevel[5]==i)  //เจออันแรก
    {
      RefMin = RefRed;
      ColorMin = Red;
    }
    if(ColorLevel[0]==i+1)  //เจออันแรก
    {
      RefMax = RefBlue;
      ColorMax = Blue;
    }
    else if(ColorLevel[1]==i+1)  //เจออันแรก
    {
      RefMax = RefGreen;
      ColorMax = Green;
    }
    else if(ColorLevel[2]==i+1)  //เจออันแรก
    {
      RefMax = RefBlack;
      ColorMax = Black;
    }
    else if(ColorLevel[3]==i+1)  //เจออันแรก
    {
      RefMax = RefWhite;
      ColorMax = White;
    }
    else if(ColorLevel[4]==i+1)  //เจออันแรก
    {
      RefMax = RefYellow;
      ColorMax = Yellow;
    }
    else if(ColorLevel[5]==i+1)  //เจออันแรก
    {
      RefMax = RefRed;
      ColorMax = Red;
    }
    FloorColor = ColorMin;
    if(RGBColor < (RefMin + RefMax) / 2) return(FloorColor);
  }
  FloorColor = ColorMax;
  return(FloorColor);
}
