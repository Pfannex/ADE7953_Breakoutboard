/******************************************************************************

  ProjectName: ESP8266 Basic template             ***** *****
  SubTitle   : WebServer Header                  *     *     ************
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

  #include <Arduino.h>
  #include <ESP8266WiFi.h>			//https://github.com/esp8266/Arduino	

  #include <ESP8266WebServer.h>
  #include <WiFiClient.h> 
  #include <DNSServer.h>
  #include <ESP8266HTTPUpdateServer.h>
  #include <ESP8266httpUpdate.h>

  #include "ESP8266_Basic_data.h"
  #include <functional>
  typedef std::function<void(void)> CallbackFunction;
  
  #define GPIO2 2

class ESP8266_Basic_webServer{
public:
  ESP8266_Basic_webServer();
  void start();
  void handleClient();
  
  void set_cfgPointer(CFG *p);  
  //void set_sensorPointer(TDS18B20_Sensors *p, THTU21_Sensors *q, TBMP180_Sensors *r);  
  void set_saveConfig_Callback(CallbackFunction c);
  void updateFirmware();
  
private:
  ESP8266WebServer webServer;
  ESP8266HTTPUpdateServer httpUpdater;
  CallbackFunction saveConfig_Callback;
  CFG *cfg;
  //ADE7953CFG *ADE7953cfg;
  TDS18B20_Sensors *DS18B20_Sensors; 
  THTU21_Sensors *HTU21_Sensors; 
  TBMP180_Sensors *BMP180_Sensors; 
  
  //Page controls----------------
  void rootPageHandler();
  void ADE7953PageHandler();

  void wlanPageHandler();
  void gpioPageHandler();
  void cfgPageHandler();
  void handleNotFound();

  //helpers----------------------------
  String IPtoString(IPAddress ip);
};

