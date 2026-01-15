/*#include <DFRobot_HuskyLens.h>
#include <HUSKYLENS.h>
#include <HUSKYLENSMindPlus.h>
#include <HuskyLensProtocolCore.h>*/

/***************************************************
 HUSKYLENS An Easy-to-use AI Machine Vision Sensor
 ****************************************************/
/*#define XrefCenter  160   
#define YrefCenter  120
int xCenter,yCenter,width,height;
int xOrigin,yOrigin,xTarget,yTarget;*/

/*HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);


void InitialHuskyslens() {
    Serial.begin(115200);
  
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
        beep(3);
    }
} 
int Face_Recognition_mode()   //การจดจำใบหน้า
{
    huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION); //Switch the algorithm to Face Recognition
}
int Object_Recognition_mode()   //การจดจำวัตถุ
{
    huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION); //Switch the algorithm to Object Recognition
}
int Color_Recognition_mode()    //การจดจำสี
{
    huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION); //Switch the algorithm to Color Recognition
}
int Tag_Recognition_mode()    //การจดจำแท็ก
{
    huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION); //Switch the algorithm to Tag Recognition
}
int Object_Tracking_mode()    //การติดตามวัตถุ
{
    huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING); //Switch the algorithm to object tracking.
}
int Line_Tracking_mode()        //การติดตามเส้น
{
    huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING); //Switch the algorithm to line tracking.
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
      xCenter=result.xCenter;
      yCenter=result.yCenter;
      width=result.width;
      height=result.height;
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
      xOrigin=result.xOrigin;
      yOrigin=result.yOrigin;
      xTarget=result.xTarget;
      yTarget=result.yTarget;
    }
    else{
        Serial.println("Object unknown!");
    }
}
int Huskylens_ReadOneID(int ID) {   //อ่านแค่ 1 ID
    ClearBuffer();
    if (!huskylens.request(ID)) {Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));}
    else if(!huskylens.isLearned()) {Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));}
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));    //ไม่ตรงกับที่กำหนดไว้
    else
    {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
      return(result.ID);
    }
    return(-1); //ไม่ตรง ID
}
int Huskylens_ReadAllID(int Number) {   //อ่านทุก ID 
    
    int ID;
    for(ID=(Number-1); ID>=0; ID--)
    {
      ClearBuffer();
      if (!huskylens.request(ID)) {Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));}
      else if(!huskylens.isLearned()) {Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));}
      else if(!huskylens.available()) {} //Serial.println(F("No block or arrow appears on the screen!"))    //ไม่ตรงกับที่กำหนดไว้
      else
      {
        HUSKYLENSResult result = huskylens.read();
        printResult(result);
        return(result.ID);
      }
    }
    Serial.println(F("No block or arrow appears on the screen!"));
    return(-1); //ไม่ตรง ID
}
void ClearBuffer()
{
  xCenter=0;
  yCenter=0;
  width=0;
  height=0;
  xOrigin=0;
  yOrigin=0;
  xTarget=0;
  yTarget=0;
}*/
