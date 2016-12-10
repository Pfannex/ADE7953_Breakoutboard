/******************************************************************************

  ProjectName: ADE7953-WattMeter                  ***** *****
  SubTitle   : Library Routines                  *     *     ************
                                                *   **   **   *           *
  Copyright by Pf@nne                          *   *   *   *   *   ****    *
                                               *   *       *   *   *   *   *
  Last modification by:                        *   *       *   *   ****    *
  - Pf@nne (pf@nne-mail.de)                     *   *     *****           *
                                                 *   *        *   *******
  Date    : 03.12.2016                            *****      *   *
  Version : alpha 0.200                                     *   *
  Revison :                                                *****

********************************************************************************/
#include "ADE7953.h"

ADE7953::ADE7953(){
}
//===============================================================================
//  FileSystem
//===============================================================================

//ADE7953 config-File-Control
//===> read from ADE7953_json <-------------------------------------------------
bool ADE7953::read_ADE7953_json(){
  bool readOK = false;
  
  File ADE7953;
  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("");
  Serial.println("mounting FS...for ADE7953");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/ADE7953.json")) {
      //file exists, reading and loading
      Serial.println("reading ADE7953");
      ADE7953 = SPIFFS.open("/ADE7953.json", "r");
      if (ADE7953) {
        Serial.println("opened ADE7953");
        size_t size = ADE7953.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        ADE7953.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        //json.printTo(Serial);
        if (json.success()) {
          Serial.println("json read ADE7953");
          
          //Get Data from File
          ADE7953_json.AIGAINjson  = json["AIGAIN"];
          ADE7953_json.BIGAINjson  = json["BIGAIN"];
          ADE7953_json.AVGAINjson  = json["AVGAIN"];
          ADE7953_json.CFMODEjson  = json["CFMODE"];
          ADE7953_json.CF1DENjson  = json["CF1DEN"];
          ADE7953_json.CF2DENjson  = json["CF2DEN"];
          ADE7953_json.AIRMSOSjson = json["AIRMSOS"];
          ADE7953_json.BIRMSOSjson = json["BIRMSOS"];
          ADE7953_json.VRMSOSjson  = json["VRMSOS"];
          //strcpy(ADE7953.Field_01, json["Field_01"]);
      
          Serial.print("AIGAIN  = ");Serial.println(ADE7953_json.AIGAINjson);
          Serial.print("BIGAIN  = ");Serial.println(ADE7953_json.BIGAINjson);
          Serial.print("AVGAIN  = ");Serial.println(ADE7953_json.AVGAINjson);
          Serial.print("CFMODE  = 0b");Serial.println(ADE7953_json.CFMODEjson, BIN);
          Serial.print("CF1DEN  = ");Serial.println(ADE7953_json.CF1DENjson);
          Serial.print("CF2DEN  = ");Serial.println(ADE7953_json.CF2DENjson);
          Serial.print("AIRMSOS = ");Serial.println(ADE7953_json.AIRMSOSjson);
          Serial.print("BIRMSOS = ");Serial.println(ADE7953_json.BIRMSOSjson);
          Serial.print("VRMSOS  = ");Serial.println(ADE7953_json.VRMSOSjson);
          readOK = true;

        }else{
          Serial.println("failed to load json ADE7953");
        }
      }
    }else{
    Serial.println("ADE7953 does not exist");
  }
  } else {
    Serial.println("failed to mount FS");
  }
  ADE7953.close();
  //end read  
  return readOK;
};

//===> write to ADE7953_json <--------------------------------------------------
void ADE7953::write_ADE7953_json(){

  SPIFFS.begin();
  //save the custom parameters to FS
  Serial.println("saving ADE7953.json");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  //Serial.println("bevor write_cfgFile ");
  //json.printTo(Serial);

  json["AIGAIN"]  = ADE7953_json.AIGAINjson;
  json["BIGAIN"]  = ADE7953_json.BIGAINjson;
  json["AVGAIN"]  = ADE7953_json.AVGAINjson;
  json["CFMODE"]  = ADE7953_json.CFMODEjson;
  json["CF1DEN"]  = ADE7953_json.CF1DENjson;
  json["CF2DEN"]  = ADE7953_json.CF2DENjson;
  json["AIRMSOS"] = ADE7953_json.AIRMSOSjson;
  json["BIRMSOS"] = ADE7953_json.BIRMSOSjson;
  json["VRMSOS"]  = ADE7953_json.VRMSOSjson;
  //json["Field_02"] = myFile.Field_02;

  File ADE7953 = SPIFFS.open("/ADE7953.json", "w");
  if (!ADE7953) {
    Serial.println("failed to open ADE7953 for writing");
    //Serial.print("format file System.. ");
    //SPIFFS.format();
    //Serial.println("done");
    //write_cfgFile();
 }

  //json.printTo(Serial);
  json.printTo(ADE7953);
  ADE7953.close();
  //end save

}
//===============================================================================
//  read RMS values 
//===============================================================================
double ADE7953::getIRMSA(){
  return double(read(IRMSA)) / 26000;
}
double ADE7953::getIRMSB(){
  return double(read(IRMSB)) / 26000;
}
double ADE7953::getVRMS(){
  return double(read(VRMS)) / 26000;
}
//===============================================================================
//  read instantaneous values 
//===============================================================================
double ADE7953::getV(){
  int int_dblV = read(V);

  int Bitdepth = 0xFFFFFF;

  if (int_dblV >= Bitdepth/2){
    int_dblV = (Bitdepth - int_dblV +1) * -1;
  } 
  double dblV = int_dblV / 13000;
  return dblV;
}

//===============================================================================
//  ADE7953 Setup 
//===============================================================================
//initialisation
bool ADE7953::init(){
  int timeout = 0;
  bool check = true;
  
  pinMode(ADE7953_RESET, OUTPUT);
  pinMode(ADE7953_IRQ, INPUT);
//Reset ADE
  digitalWrite(ADE7953_RESET, LOW);
  delay(100);
  digitalWrite(ADE7953_RESET, HIGH);
  
//ADE7953 POWER-UP PROCEDURE
  Serial.print("init running");
  while (digitalRead(ADE7953_IRQ)){
    timeout++;
    Serial.print(".");
    if (timeout > 50){
      check = false;
      Serial.println("ADE7953.init TIMEOUT!!!!");
      while (1){}
    }
  }
  Serial.println("");
  Serial.println("ADE7953.init OK");
  
  read_ADE7953_json();
  
  Serial.println("start Register settings");
//REQUIRED REGISTER SETTING  
  write(unlock, 0xAD);
  write(Reserved1, 0x30);
  //pREG(unlock);pREG(Reserved1);

//optional REGISTER SETTING  
  write(AIGAIN, ADE7953_json.AIGAINjson);      //Gain IA
  write(BIGAIN, ADE7953_json.BIGAINjson);      //Gain IB
  write(AVGAIN, ADE7953_json.AVGAINjson);      //Gain V
  write(AIRMSOS,ADE7953_json.AIRMSOSjson);     //Offset IA
  write(BIRMSOS,ADE7953_json.BIRMSOSjson);     //Offset IB
  write(VRMSOS, ADE7953_json.VRMSOSjson);      //Offset V

  write(CFMODE,ADE7953_json.CFMODEjson);       //set CF1->IRMSA & CF2->IRMSB 
  write(CF1DEN,ADE7953_json.CF1DENjson);       //CF1 IA 
  write(CF2DEN,ADE7953_json.CF2DENjson);       //CF2 IB 
 
  return true;
}

//===============================================================================
//  helpers 
//===============================================================================
//printout register values
void ADE7953::pREG(uint16_t reg){
  uint32_t val = read(reg);
  byte bval = val;
  
  Serial.printf("< 0x%03X >-------------------------------\r\n", reg);
  Serial.printf(" HEX | 0x%06X\r\n", val);
  Serial.print(" BIN | "); Serial.println(strBIN(val));
  Serial.printf(" DEC | %d\r\n", val);
}
//get BIN string of register values
String ADE7953::strBIN(uint32_t val){
  String strVal = "";
  int pos = 0;
  for (unsigned int mask = 0x800000; mask; mask >>= 1) {
    strVal += mask&val?'1':'0';
    pos++;
    if (pos == 4) strVal += "_"; if (pos == 8) strVal += " ";
    if (pos == 12) strVal += "_"; if (pos == 16) strVal += " ";
    if (pos == 20) strVal += "_";
  }
  return strVal;
}
long int ADE7953::StrToInt(String str){
  char chr[50];
  long int val;
  
  if (str.indexOf("0b") == 0){
    str = str.substring(2);
    strcpy(chr, str.c_str());
    val = strtol(chr, 0, 2); 
  }else if (str.indexOf("0x") == 0){
    str = str.substring(2);
    strcpy(chr, str.c_str());
    val = strtol(chr, 0, 16);   
  }else{
    val = str.toInt();
  }
  return val;
}

//===============================================================================
//  ADE7953 read/write Register / Bit
//===============================================================================
//write-------------------------------------------------------------
void ADE7953::write(uint16_t reg, uint32_t val){
  int count = 0;
  
  if (reg < 0x100 | reg > 0x3FF) {count = 1;}        //8Bit inkl. 0x702/0x800
  else if (reg < 0x200){count = 2;}                  //16Bit 
  else if (reg < 0x300){count = 3;}                  //24Bit
  else if (reg < 0x400){count = 4;}                  //32Bit
  
  Wire.beginTransmission(I2Caddr); 
  Wire.write(reg >> 8); 
  Wire.write(reg);  
  for (int i = 0; i<count; i++){
    Wire.write(val >> (count-1-i)*8);               //write MSB first
  } 
  Wire.endTransmission(); 
}

void ADE7953::write(String strRegVal){
  int pos = strRegVal.indexOf(",");
  String strReg = strRegVal.substring(0, pos);
  String strVal = strRegVal.substring(pos+1);
  
  uint16_t reg = StrToInt(strReg);
  long int val = StrToInt(strVal);

  write(reg, val);
}

void ADE7953::writeBit(uint16_t reg, uint32_t pos, bool val){
  uint32_t RegVal = read(reg);
  
  bitWrite(RegVal, pos, val);  
  write(reg, RegVal);  
}
void ADE7953::writeBit(String strRegPosVal){
  String tmp = "";
  String strReg = "";
  String strPos = "";
  String strVal = "";
  
  int Kpos = strRegPosVal.indexOf(",");
  strReg = strRegPosVal.substring(0, Kpos);
  tmp = strRegPosVal.substring(Kpos+1);
  Kpos = tmp.indexOf(",");
  strPos = tmp.substring(0, Kpos);
  strVal = tmp.substring(Kpos+1);

  writeBit(StrToInt(strReg), StrToInt(strPos), StrToInt(strVal));
}
//read-------------------------------------------------------------
uint32_t ADE7953::read(uint16_t reg){
  int count = 0;
  uint32_t val = 0x00;
  
  if (reg < 0x100 | reg > 0x3FF) {count = 1;}        //8Bit inkl. 0x702/0x800
  else if (reg < 0x200){count = 2;}                  //16Bit 
  else if (reg < 0x300){count = 3;}                  //24Bit
  else if (reg < 0x400){count = 4;}                  //32Bit
  
  Wire.beginTransmission(I2Caddr);  
  Wire.write(reg >> 8); 
  Wire.write(reg); 
  Wire.endTransmission();     

  Wire.beginTransmission(I2Caddr); 
  Wire.requestFrom(I2Caddr, count);
  for (int i = 0; i<count; i++){
    if (i>0) val = val << 8; 
    val += Wire.read();                              //read MSB first
  }
  Wire.endTransmission(); 
  return val;
}
uint32_t ADE7953::read(String strReg){
  uint32_t readReg = 0;
  uint16_t reg = StrToInt(strReg);
  readReg = read(reg);
  return readReg;
}

bool ADE7953::readBit(uint16_t reg, uint32_t pos){
  return bitRead(read(reg), pos);
}
bool ADE7953::readBit(String strRegPos){
  int Kpos = strRegPos.indexOf(",");
  String strReg = strRegPos.substring(0, Kpos);
  String strPos = strRegPos.substring(Kpos+1);
  
  uint16_t reg = StrToInt(strReg);
  uint32_t pos = StrToInt(strPos);
  
  return bitRead(read(reg), pos);
}


//===============================================================================
//  xxxxxxxxx 
//===============================================================================


void ADE7953::Test(){
  pREG(CFMODE);
 
}


