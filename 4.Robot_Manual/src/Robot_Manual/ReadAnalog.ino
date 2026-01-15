void Read7Analog() {
  L3 = analog(0);
  L2 = analog(1);
  L1 = analog(2);
  C = analog(3);
  R1 = analog(4);
  R2 = analog(5);
  R3 = analog(6);
}
void Read2AnalogBack() {
  BL1 = analog(7); 
  BR1 = analog(8);
}
int Sonar()
{
  int Sonar;
   
  //Sonar = (analog(8)/40); //ZX-sonar
  Sonar = analog(8);   //infrared
  Sonar -= 1150; 
  if(Sonar<=0) Sonar = 1;
  Sonar = 6000/Sonar;
  return(Sonar);
}
