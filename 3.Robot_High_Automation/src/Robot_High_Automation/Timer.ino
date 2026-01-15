int ReadZXSonar() {
  int Distance;
  Distance = (analog(7)/10);
  return Distance;
}
void StartTimer()  {
  Timer = millis();
}
long int ReadTimer()  {
  return(millis() - Timer);
}
void StartTimer1()  {
  Timer1 = millis();
}
long int ReadTimer1()  {
  return(millis() - Timer1);
}
void StartTimer2()  {
  Timer2 = millis();
}
long int ReadTimer2()  {
  return(millis() - Timer2);
}
void StartTimer3()  {
  Timer3 = millis();
}
long int ReadTimer3()  {
  return(millis() - Timer3);
}
void StartTimer4()  {
  Timer4 = millis();
}
long int ReadTimer4()  {
  return(millis() - Timer4);
}
