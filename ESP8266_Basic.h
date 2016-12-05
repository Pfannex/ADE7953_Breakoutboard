/******************************************************************************

  ProjectName: ESP8266 Basic template             ***** *****
  SubTitle   : Basic Header                      *     *     ************
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
/*
ToDo
FS Abfrage ob Feld vorhanden, sonst ggf. format
Wenn cfg und WiFi.SSID() gleich dann ohne Vorgabe starten, soll schneller gehen 
WEB config with password
Erledigt: Reset nach nicht ge�nderter Config wird nicht durchgef�hrt
WEB-Status Tabelle rechts
TopicTree 
Erledigt: OTA WEB
OTA Arduino
Erledigt: OTA onDemand
*/  
  

#pragma once

//FileSystem
  #include <FS.h>                   	//this needs to be first, or it all crashes and burns...
  #include <ArduinoJson.h>          	//https://github.com/bblanchon/ArduinoJson
 
//ESP8266
  #include <ESP8266WiFi.h>			    //https://github.com/esp8266/Arduino	
  #include <EEPROM.h>

  #include <ESP8266WebServer.h>
  #include <WiFiClient.h> 
  #include <DNSServer.h>
  
//MQTT Client
  #include <PubSubClient.h>
  
//ESP8266_Basic
  #include "ESP8266_Basic_webServer.h"
  #include "ESP8266_Basic_data.h"
  
  #include "ADE7953.h"

//Bus
  //1Wire direct
  //#include "OneWire.h"
  //#include <DallasTemperature.h> 
  //I2C
  #include <Wire.h>              
  //#include <Adafruit_BMP085.h>   //Temperature / Pressure
  //#include "Adafruit_HTU21DF.h"  //Temperature / Humidity

//MySQL
  #include <MySQL_Connection.h>
  #include <MySQL_Cursor.h>

//===> GPIO <--------------------------------------------------------------
//1Wire
  //#define oneW 2
//I2C
  #define I2C_SDA 4
  #define I2C_SCL 5
  //#define MUX         0x70  //Multiplexer Address

class ESP8266_Basic{

public:
  ESP8266_Basic();
  void start_WiFi_connections();
  void handle_connections();
  void cfgChange_Callback();
  void mqttBroker_Callback(char* topic, byte* payload, unsigned int length);
  void setCallback(MQTT_CALLBACK_SIGNATURE);


  bool pub(int e1, char* Payload);
  bool pub(int e1, int e2, char* Payload);
  bool pub(int e1, int e2, int e3, char* Payload);
  
  //AktSen
  void handle_Measurement();
  void run_I2C();
  //TDS18B20_Sensors DS18B20_Sensors;
  //THTU21_Sensors HTU21_Sensors;
  //TBMP180_Sensors BMP180_Sensors;

  ADE7953 ADE;
 
private:
  WiFiClient wifi_client;
  PubSubClient mqtt_client;
  File cfgFile;
  ESP8266_Basic_webServer webServer;  
  
  //AktSen
  long lastMeasure_time;
  long updateMeasure_time = 5000;
  //void run_oneWire();
  //void scanI2C();
  //void mux(byte channel);  
  //bool HTU21_begin();
  //bool BMP180_begin();
  
  //WiFi-Manager-Control---------------
  void startConfigServer();
  void startAccessPoint();
  
  bool start_WiFi();  
  bool start_MQTT();
  bool WIFI_reconnect;
  
  //Config-Control---------------------
  void read_cfg();
  bool read_cfgFile();
  void write_cfg();
  void write_cfgFile();
  void resetSettings();  
  bool config_running;
  CFG cfg;
  
  //MyData-Control---------------------
  bool read_MyFile();
  void write_MyFile();
  MyFile myFile;
  
  //MQTT-Control-----------------------
  Topics topic;
  String buildE1(int e1);
  String buildE2(int e1, int e2);
  String buildE3(int e1, int e2, int e3);
  //String buildE4(int e1, int e2, int e3, int e4);
  //bool pub(int e1, int e2, int e3, int e4, char* Payload);
  TdissectResult dissectPayload(String subTopic, String subValue);
  
  void pubConfig();
  
  //MySQL-Control---------------------
  void start_MySQL();
  
  //helpers----------------------------
  void checkFlash();
  String IPtoString(IPAddress ip);
  IPAddress charToIP(char* IP);
  void printCFG();    
};
