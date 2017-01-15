/******************************************************************************

  ProjectName: ADE7953-WattMeter                  ***** *****
  SubTitle   : Library Header                    *     *     ************
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
#pragma once
//FileSystem
  #include <FS.h>                   //this needs to be first, or it all crashes and burns...
  #include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
//ESP8266
  #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino  
//Tools
  #include <Wire.h>                 //I²C
//ADE7953  
  #include "ADE7953_REG.h"          //ADE7953 Registers

  #define I2Caddr 0x38
  #define ADE7953_RESET 2           //GPIO RESET ADE7953
  #define ADE7953_IRQ 13            //GPIO IRQ ADE7953

class ADE7953{
public:
  ADE7953();
  bool init();
  void write(uint16_t reg);
  void write(uint16_t reg, uint32_t val);
  void write(String strRegVal);
  void writeBit(uint16_t reg, uint32_t pos, bool val);
  void writeBit(String strRegPosVal);
  uint32_t read(uint16_t reg);
  uint32_t read(String strReg);
  bool readBit(uint16_t reg, uint32_t pos);
  bool readBit(String strRegPos);
  
  double getIRMSA();
  double getIRMSArel();
  double getIRMSB();
  double getIRMSBrel();
  double getVRMS();
  double getVRMSrel();
  double getPFA();
  double getPFB();
  double getANGLE_A();
  double getANGLE_B();
  double getPERIOD();
  double getFREQ();
  double getP_A();
  double getP_Arel();
  double getQ_A();
  double getQ_Arel();
  double getS_A();
  double getS_Arel();
  double getP_B();
  double getP_Brel();
  double getQ_B();
  double getQ_Brel();
  double getS_B();
  double getS_Brel();
  String getVwave(int samples);

  void pREG(uint16_t reg);
  long int StrToInt(String str); 
  long int uint24Tolong32(uint32_t val); 
  long int uint16Tolong32(uint16_t val);
  String getRegName(uint16_t regNumber); 
  void Test();
  String formatDouble(double value, int dec);

//ADE7953 config-File-Control
  bool read_ADE7953_json();
  void write_ADE7953_json();
  void setDefault();

private:
  String strBIN(uint32_t val);
  double getFullScaleInput(int PGA);
  

};





