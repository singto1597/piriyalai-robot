void Read7Analog(){  //อ่านค่าเซ็นเซอร์หน้า 7 ตัว
  L3 = analog(8); 
  L2 = analog(7);
  L1 = analog(6);
  C = analog(5);
  R1 = analog(4);
  R2 = analog(3);
  R3 = analog(2);
}

void Read5AnalogBack(){  //อ่านค่าเซ็นเซอร์หลัง 5 ตัว
  BL2 = analog(1);
  //BL1 = analog(9);
  //BC = analog(10);
  //BR1 = analog(11);
  BR2 = analog(0);
}

void Convert7Analog(){ //แปลงค่า analog หน้า เป็น digital 0:ดำ,1:ขาว
  Read7Analog();
  if(L3<RefL3) L3=0; else L3=1;
  if(L2<RefL2) L2=0; else L2=1; 
  if(L1<RefL1) L1=0; else L1=1; 
  if(C<RefC) C=0; else C=1; 
  if(R1<RefR1) R1=0; else R1=1; 
  if(R2<RefR2) R2=0; else R2=1; 
  if(R3<RefR3) R3=0; else R3=1;  
}

void Convert5AnalogBack(){ //แปลงค่า analog หลัง เป็น digital 0:ดำ,1:ขาว
  Read5AnalogBack();
  if(BL2<RefBL2) BL2=0; else BL2=1; 
  //if(BL1<RefBL1) BL1=0; else BL1=1; 
  //if(BC<RefBC) BC=0; else BC=1; 
  //if(BR1<RefBR1) BR1=0; else BR1=1; 
  if(BR2<RefBR2) BR2=0; else BR2=1;  
}
