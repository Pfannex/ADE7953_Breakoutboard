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
  #include <NTPClient.h>
  #include <WiFiUdp.h>
  
//MQTT Client
  #define MQTT_MAX_PACKET_SIZE 1280
  #include <PubSubClient.h>
  
//ESP8266_Basic
  #include "ESP8266_Basic_webServer.h"
  #include "ESP8266_Basic_data.h"
  
  #include "ADE7953.h"

//Bus
  //I2C
  #include <Wire.h>              
  #include <brzo_i2c.h>
  #include <Adafruit_NeoPixel.h>
//Sensoren
  #include <Adafruit_BMP085.h>

//MySQL
  //#include <MySQL_Connection.h>
  //#include <MySQL_Cursor.h>

// Timer
  extern "C" { 
  #include "user_interface.h" 
  }
  void tick(void *pArg);
  
//Peripherals
  #define BTIME 5000
  typedef struct { 
   int S;           // mode S 0 or 1  
   int L;           // mode L 0 or 1
   unsigned long t; // time of last change
   int state;       // button down 0 or 1
   int idle;        // state lasts longer than >= BTIME
  } buttonMode_t;
  typedef enum ledMode_t { OFF, ON, BLINK };

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

  //void adeCallback();
  void setADECallback(ADE_CALLBACK_SIGNATURE);
  void ade_Callback(char* sample, uint16_t instREG);


  bool pub(int e1, char* Payload);
  bool pub(int e1, int e2, char* Payload);
  bool pub(int e1, int e2, int e3, char* Payload);

  //Timer
  void setup_Timer();
  void timerCallback();

  //Peripherals
  void setup_Peripherals();
  void handle_Peripherals();
  void switchRelay(int state);
 
  //AktSen
  void handle_Measurement();
  void run_I2C();

  ADE7953 ADE;
//BMP180 Luftdruck
  Adafruit_BMP085 bmp;
  
  WiFiUDP ntpUDP;
  NTPClient timeClient;
 
private:
  WiFiClient wifi_client;
  PubSubClient mqtt_client;
  File cfgFile;
  ESP8266_Basic_webServer webServer;  

  //Timer ------------------------------
  // see http://bienonline.magix.net/public/esp8266-timing.html
  os_timer_t timer;
  #define TIMER_T 20  // timer fires every 20 ms
  long ticks= 0;         // timer ticks are incremented every TIMER_T ms

  //Peripherals------------------------
  // see https://github.com/esp8266/Arduino/blob/master/doc/reference.md

  //#define LED2_PIN 1  //Tx
  //#define LED3_PIN 3  //Rx
  

  #define DEBOUNCETIME 50
  int buttonPinState[17];                 // the last pin state
  unsigned long lastDebounceTime[17];     // when the pin state changed last
  int getButtonPinState(int buttonPin);
  
  #define BUTTON_PIN 12 // Arduino Pin 12 = = IO12 = Physical Pin 6 = NodeMCU/WeMos Pin D6
  buttonMode_t currentButtonMode;
  unsigned long buttonChangeTime= 0;      
  void printButtonMode(String msg, buttonMode_t mode);
  void setButtonMode(buttonMode_t mode);
  void onSetButtonMode(buttonMode_t oldMode, buttonMode_t newMode);
  
  #define LED_PIN 15 // Arduino Pin 15 = IO15 = Physical Pin 16 = NodeMCU/WeMos Pin D8

  Adafruit_NeoPixel WS_LED = Adafruit_NeoPixel(2, LED_PIN, NEO_GRB + NEO_KHZ800);
  
  ledMode_t currentLedMode;
  void Led(int on);
  #define BLINK_T 5  // in multiples of TIMER_T

  #define RELAY_PIN 14 // Arduino Pin 14 = IO14 = Physical Pin 5 = NodeMCU/WeMos Pin D5
  void Relay(int on);

  //AktSen
  long lastMeasure_time;
  long updateMeasure_time = 5000;
  
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
  //void start_MySQL();
  
  //helpers----------------------------
  void checkFlash();
  String IPtoString(IPAddress ip);
  IPAddress charToIP(char* IP);
  void printCFG();    
};
