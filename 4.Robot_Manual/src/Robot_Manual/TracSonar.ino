void TracSonar() {

  BaseSpeed = SonarSpeed;
  InitialSpeed();
   while(Sonar()>DistanceRef)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Sonar()>DistanceRef))  
    {
      CalError();
    }
  }
  OffMotor();
  BaseSpeed = Speed;
  InitialSpeed();
}
