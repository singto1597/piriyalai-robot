void StartTimer0(){  //เริ่มจับเวลา Timer0
  BaseTimer0 = millis();  //อ่านเวลาปัจจุบันในหน่วง ms
  Timer0 = 0;
}

void ReadTimer0(){ //อ่านค่า Timer 0
  Timer0 = millis() - BaseTimer0;
}
