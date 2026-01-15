#include <SoftwareSerial.h>
//#include <ReceiveOnlySoftwareSerial.h>
// Set up a new SoftwareSerial object
class WCX{
  private:
    unsigned long lastTime;
    unsigned long SampleTime = 100;
    SoftwareSerial *_Serial_WCX; 
   public:
    bool LU = 0;
    bool LL = 0;
    bool LR = 0;
    bool LD = 0;
    bool LT = 0;
    bool L1 = 0;
    bool L2 = 0;
    bool RU = 0;
    bool RL = 0;
    bool RR = 0;
    bool RD = 0;
    bool RT = 0;
    bool R1 = 0;
    bool R2 = 0;
    uint16_t rawData = 0;
    bool getButton();
    void begin(uint8_t intRx);
};
  void WCX::begin(uint8_t intRx) {
  	_Serial_WCX = new SoftwareSerial(intRx,intRx+1);
    _Serial_WCX->begin(9600);
  }
  bool WCX::getButton() {
    if(_Serial_WCX->available()>2){
      while (_Serial_WCX->available() > 2){ 
        byte buf[2];
        _Serial_WCX->readBytes(buf,2);
        if(buf[0] & 0x80 ){
          byte swap = buf[0];
          buf[0] = buf[1];
          buf[1] = swap;
        }
          uint16_t value = (buf[1]<<8 | buf[0]);
          rawData = value;
          if(value != 0x0000){
            if ((value & 0x4000) == 0) {LT=0;} else {LT=1;}
            if ((value & 0x2000) == 0) {L2=0;} else {L2=1;}
            if ((value & 0x1000) == 0) {L1=0;} else {L1=1;}
            if ((value & 0x0800) == 0) {LU=0;} else {LU=1;}
            if ((value & 0x0400) == 0) {LL=0;} else {LL=1;}
            if ((value & 0x0200) == 0) {LR=0;} else {LR=1;}
            if ((value & 0x0100) == 0) {LD=0;} else {LD=1;}

            if ((value & 0x40) == 0) {RT=0;} else {RT=1;}
            if ((value & 0x20) == 0) {R2=0;} else {R2=1;}
            if ((value & 0x10) == 0) {R1=0;} else {R1=1;}
            if ((value & 0x08) == 0) {RU=0;} else {RU=1;}
            if ((value & 0x04) == 0) {RR=0;} else {RR=1;}
            if ((value & 0x02) == 0) {RL=0;} else {RL=1;}
            if ((value & 0x01) == 0) {RD=0;} else {RD=1;}
            
          }else{
            LT=0;L2=0;L1=0;LU=0;LR=0;LL=0;LD=0;
            RT=0;R2=0;R1=0;RU=0;RR=0;RL=0;RD=0;
          }
        while (_Serial_WCX->available()>2){_Serial_WCX->read();}
        lastTime = millis();
        if (value!=0x8000){ 
          return 1; 
        }else{
          LT=0;L2=0;L1=0;LU=0;LR=0;LL=0;LD=0;
          RT=0;R2=0;R1=0;RU=0;RR=0;RL=0;RD=0;
          rawData = 0;
          return 0; 
        }
    }
    }else{
      unsigned long timeChange = (millis() - lastTime);
      if (timeChange >= SampleTime) {
		LT=0;L2=0;L1=0;LU=0;LR=0;LL=0;LD=0;
        RT=0;R2=0;R1=0;RU=0;RR=0;RL=0;RD=0;
        rawData = 0;
        return 0;
        //value = 0;
      }else{
        return 1;
      }
    }
  }
