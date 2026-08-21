// Driver_Stopwatch.ino
// นาฬิกาจับเวลา (millis) 5 ตัว ใช้แยกนับเวลาในแต่ละส่วนของ logic

// นาฬิกาหลัก (ใช้ทั่วไป: การเลือกโหมด, เวลาวิ่งแต่ละจังหวะ)
void startStopwatch()       { stopwatchMs  = millis(); }
long int stopwatchElapsed() { return (millis() - stopwatchMs); }

// นาฬิกา 1 (ใช้ใน backwardAlign)
void startStopwatch1()       { stopwatch1Ms = millis(); }
long int stopwatchElapsed1() { return (millis() - stopwatch1Ms); }

// นาฬิกา 2 (ใช้จับเวลารวมของการวิ่ง)
void startStopwatch2()       { stopwatch2Ms = millis(); }
long int stopwatchElapsed2() { return (millis() - stopwatch2Ms); }

// นาฬิกา 3 (ใช้ใน followLineFor)
void startStopwatch3()       { stopwatch3Ms = millis(); }
long int stopwatchElapsed3() { return (millis() - stopwatch3Ms); }

// นาฬิกา 4 (ใช้ใน followLineAndAlign)
void startStopwatch4()       { stopwatch4Ms = millis(); }
long int stopwatchElapsed4() { return (millis() - stopwatch4Ms); }
