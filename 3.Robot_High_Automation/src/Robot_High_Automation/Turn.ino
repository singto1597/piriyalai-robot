void TurnLeft() {
  Left(TurnSpeed , 24400/TurnSpeed);   //22000 //16800
}
void TurnRight() {
  Right(TurnSpeed , 24400/TurnSpeed);   //21000 //16800
}
void UTurnLeft() {
  Left(TurnSpeed , 36000/TurnSpeed);     //38000
}
void UTurnRight() {
  Right(TurnSpeed , 36000/TurnSpeed);   //38000
}
void Left(int Speed , int Time){
  MotorStop();
  SL(Speed);
  delay(Time);
  MotorStop();
}
void Right(int Speed , int Time){
  MotorStop();
  SR(Speed);
  delay(Time);
  MotorStop();
}
void TurnLeftDelay(int Speed , int Time){
  TL(Speed);
  delay(Time);
}
void TurnRightDelay(int Speed , int Time){
  TR(Speed);
  delay(Time);
}
