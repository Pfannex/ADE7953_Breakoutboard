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
//  read RMS values 
//===============================================================================
double ADE7953::getIRMSA(){
  double dblIRMSA = double(read(IRMSA));
  dblIRMSA = dblIRMSA  / 26000;
  return dblIRMSA;
}
double ADE7953::getIRMSB(){
  double dblIRMSB = double(read(IRMSB));
  dblIRMSB = dblIRMSB / 26000;
  return dblIRMSB;
}
double ADE7953::getVRMS(){
  double dblVRMS = double(read(VRMS));
  dblVRMS = dblVRMS / 26000;
  return dblVRMS;
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

  Serial.println("start Register settings");
//REQUIRED REGISTER SETTING  
  write(unlock, 0xAD);
  write(Reserved1, 0x30);
  //pREG(unlock);pREG(Reserved);

//optional REGISTER SETTING  
  
  
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
  char chr[15];
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
//  ADE7953 read/write Register 
//===============================================================================
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

  //Serial.println(strRegVal);
  //Serial.println("REG / VAL");
  //Serial.println(strReg);
  //Serial.println(strVal);
  
  uint16_t reg = StrToInt(strReg);
  uint32_t val = StrToInt(strVal);
  
  //Serial.println("REG / VAL");
  //Serial.println(reg);
  //Serial.println(val);

  write(reg, val);
}

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


//===============================================================================
//  xxxxxxxxx 
//===============================================================================


void ADE7953::Test(){
  uint16_t reg = 0x0;
  Serial.println("startTest");

  reg = 0x004; pREG(reg);
  reg = 0x102; pREG(reg);
  reg = 0x203; pREG(reg);
  reg = 0x303; pREG(reg);
  reg = 0x28C; pREG(reg);

  reg = 0x28C; write(reg, 0xABCDEF); pREG(reg);  
  reg = 0x004; write(reg, 0xAB); pREG(reg);  
}


