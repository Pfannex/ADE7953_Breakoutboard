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
  void write(uint16_t reg, uint32_t val);
  void write(String strRegVal);
  uint32_t read(uint16_t reg);
  uint32_t read(String strReg);
  void pREG(uint16_t reg);
  long int StrToInt(String str);
  //void setBit(int nr, int val);
  //void setBit(int first, int last, String strRegVal);
  //void toggleBit(int nr);
  //MQTT inst
  
  double getIRMSA();
  double getIRMSB();
  double getVRMS();
  double getV();
  
  void Test();

private:
  String strBIN(uint32_t val);

};

