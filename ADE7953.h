/******************************************************************************

  ProjectName: ADE7953-WattMeter                  ***** *****
  SubTitle   : ADE7953-WattMeter                 *     *     ************
                                                *   **   **   *           *
  Copyright by Pf@nne                          *   *   *   *   *   ****    *
                                               *   *       *   *   *   *   *
  Last modification by:                        *   *       *   *   ****    *
  - Pf@nne (pf@nne-mail.de)                     *   *     *****           *
                                                 *   *        *   *******
  Date    : 24.11.2016                            *****      *   *
  Version : alpha 0.100                                     *   *
  Revison :                                                *****

********************************************************************************/
#pragma once
//ESP8266
  #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino  
//Tools
  #include <Wire.h>                 //I²C

class ADE7953{

public:
  ADE7953();
  void Test();

private:

};

