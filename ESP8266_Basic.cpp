/******************************************************************************

  ProjectName: ESP8266 Basic template             ***** *****
  SubTitle   : Basic routines                    *     *     ************
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
#include "ESP8266_Basic.h"

//===> variables <---------------------------------------------------------

//BMP180 Luftdruck
  //Adafruit_BMP085 bmp;

//CLASS ESP8266_Basic################################################################
ESP8266_Basic::ESP8266_Basic() : webServer(), 
                                 mqtt_client(wifi_client),
                                 timeClient(ntpUDP, "europe.pool.ntp.org", 3600,1000){
                                 // By default 'time.nist.gov' is used with 60 seconds update interval and
                                 // no offset
                                 // You can specify the time server pool and the offset, (in seconds)
                                 // additionaly you can specify the update interval (in milliseconds).
                                 // NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

  //Callbacks								 
  //ADE.set_Callback(std::bind(&ESP8266_Basic::adeCallback, this));  
  ADE.setADECallback(std::bind(&ESP8266_Basic::ade_Callback, this, std::placeholders::_1, std::placeholders::_2));
  
  webServer.set_saveConfig_Callback(std::bind(&ESP8266_Basic::cfgChange_Callback, this));
  mqtt_client.setCallback(std::bind(&ESP8266_Basic::mqttBroker_Callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}
//===> ADE Callback <---------------------------------------------------
//void ESP8266_Basic::adeCallback(){
  //Serial.print("ADE Callback -> "); Serial.println("xx");
 
//}



//===============================================================================
//  incomming subscribe 
//===============================================================================
//===> incomming subscribe <---------------------------------------------------
void ESP8266_Basic::mqttBroker_Callback(char* topic, byte* payload, unsigned int length) {

  char value[500] = "";
  char chr[500] = "";
  int samples = 50;
  double inst[samples];
  String str = "";
  String attr[10];

  int attrCount = 0;  
  for (int i = 0; i < length; i++) {
    value[i] = payload[i];
    char x = payload[i];
    String y = String(x);
    if (y == "," ){
      attrCount++;     
    }else{
      attr[attrCount] += (char)payload[i];
    }
  }

  TdissectResult dissectResult;    
  dissectResult = dissectPayload(topic, value);
  
  Serial.println("##incoming subscribe##########");
  //Serial.print("incoming subscribe - LEN: ");
  //Serial.print(length);
  //Serial.print(" | ");
  Serial.println(topic);
  //Serial.print(" | ");
  Serial.println(value);
  Serial.println("");
  //Serial.print("path: ");Serial.println(dissectResult.itemPath);*/

  if (dissectResult.found){
    
//201 ADE7953.read
    if (dissectResult.itemPath == "2/0/1"){
      String strReg = "0x";
      strReg += String(ADE.StrToInt(value), HEX);
      strcpy(chr, strReg.c_str());
      pub(2,0, chr);
      String str = ADE.getRegName(ADE.StrToInt(value));      
      strcpy(chr, str.c_str());
      pub(2,0,5, chr);
      
      uint32_t reg = ADE.read(String(value));
      str = "0x";
      str += String(reg, HEX);
      strcpy(chr, str.c_str());
      pub(2,0,0, chr);
      str = String(reg, BIN);
      strcpy(chr, str.c_str());
      pub(2,0,1, chr);
      str = String(reg);
      strcpy(chr, str.c_str());
      pub(2,0,2, chr);
    }
    
//202 ADE7953.write
    if (dissectResult.itemPath == "2/0/2"){   
      //Serial.println("Write to ADE");
            
      ADE.write(String(value));
      
      String strReg = "0x";
      int pos = String(value).indexOf(",");
      strReg += String(ADE.StrToInt(String(value).substring(0, pos)), HEX);
      
      strcpy(chr, strReg.c_str());
      pub(2,0, chr);
      String str = ADE.getRegName(ADE.StrToInt(value));      
      strcpy(chr, str.c_str());
      pub(2,0,5, chr);

      
      uint32_t reg = ADE.read(String(value));      
      str = "0x";
      str += String(reg, HEX);
      strcpy(chr, str.c_str());
      pub(2,0,0, chr);
      str = String(reg, BIN);
      strcpy(chr, str.c_str());
      pub(2,0,1, chr);
      str = String(reg);
      strcpy(chr, str.c_str());
      pub(2,0,2, chr);
    }

//203 ADE7953.readBit
    if (dissectResult.itemPath == "2/0/3"){               
      bool val = ADE.readBit(String(value));

      String strReg = "0x";
      int pos = String(value).indexOf(",");
      strReg += String(ADE.StrToInt(String(value).substring(0, pos)), HEX);
      strcpy(chr, strReg.c_str());
      pub(2,0, chr);
      String str = ADE.getRegName(ADE.StrToInt(value));      
      strcpy(chr, str.c_str());
      pub(2,0,5, chr);

      strReg = String(value).substring(pos+1);
      strcpy(chr, strReg.c_str());
      pub(2,0,3, chr);
      
      strReg = String(val);
      strcpy(chr, strReg.c_str());
      pub(2,0,4, chr);

      pub(2,0,0, "");
      
      uint32_t reg = ADE.read(ADE.StrToInt(String(value)));
      str = "0b";
      str = String(reg, BIN);
      strcpy(chr, str.c_str());     
      pub(2,0,1, chr);
      
      pub(2,0,2, "");
    }
    
//204 ADE7953.writeBit
    if (dissectResult.itemPath == "2/0/4"){   
      ADE.writeBit(String(value));

      String strReg = "0x";
      int pos = String(value).indexOf(",");
      strReg += String(ADE.StrToInt(String(value).substring(0, pos)), HEX);
      strcpy(chr, strReg.c_str());
      pub(2,0, chr);
      String str = ADE.getRegName(ADE.StrToInt(value));      
      strcpy(chr, str.c_str());
      pub(2,0,5, chr);

      uint32_t reg = ADE.read(ADE.StrToInt(strReg));
      str = "0x";
      str += String(reg, HEX);
      strcpy(chr, str.c_str());
      pub(2,0,0, chr);
      str = String(reg, BIN);
      strcpy(chr, str.c_str());
      pub(2,0,1, chr);
      str = String(reg);
      strcpy(chr, str.c_str());
      pub(2,0,2, chr);      
    }
    
//205 ADE7953.init
    if (dissectResult.itemPath == "2/0/5"){         
      ADE.init();
    }
    
//206 ADE7953.updateTime
    if (dissectResult.itemPath == "2/0/6"){         
      //Write Field_01
      strcpy(myFile.Field_01, value);
      write_MyFile();
      updateMeasure_time = String(value).toInt();
      Serial.print("UpdateMesure_time = "); Serial.println(value);
    }

//207 ADE7953.saveConfig
    if (dissectResult.itemPath == "2/0/7"){         
      ADE.write_ADE7953_json();
    }

//208 ADE7953.setDefault
    if (dissectResult.itemPath == "2/0/8"){         
      ADE.setDefault();
    }

//209 ADE7953.resetEnergy
    if (dissectResult.itemPath == "2/0/9"){
      
      if (attr[0] == "WA"){
        ADE.energy[0] = attr[1].toInt();   //negativ -> 2er komplement!
      }
      if (attr[0] == "WbA"){
        ADE.energy[1] = attr[1].toInt();
      }
      if (attr[0] == "WsA"){
        ADE.energy[2] = attr[1].toInt();
      }
      if (attr[0] == "WB"){
        ADE.energy[3] = attr[1].toInt();
      }
      if (attr[0] == "WbB"){
        ADE.energy[4] = attr[1].toInt();
      }
      if (attr[0] == "WsB"){
        ADE.energy[5] = attr[1].toInt();
      }
    }
    

//210 ADE7953.get_VINST
    if (dissectResult.itemPath == "2/1/0"){  
      if (ADE.getVRMSrel() > 1){
        ADE.getWave(V);
        pub(2,1,34, "triggered"); 
      } 
    }
//211 ADE7953.get_IAINST
    if (dissectResult.itemPath == "2/1/1"){   
      if (ADE.getVRMSrel() > 1){
        ADE.getWave(IA);
        pub(2,1,34, "triggered");  
      }
    }
//212 ADE7953.get_IBINST
    if (dissectResult.itemPath == "2/1/2"){   
      if (ADE.getVRMSrel() > 1){
        ADE.getWave(IB);
        pub(2,1,34, "triggered"); 
      } 
    }
    
//213 getWaves
    if (dissectResult.itemPath == "2/1/3"){ 
      if (ADE.getVRMSrel() > 1){
        ADE.getWave(V);  
        ADE.getWave(IA);  
        ADE.getWave(IB);  
        pub(2,1,34, "triggered");
      }
    }
    
//40 Relais/set|on:off
    if (dissectResult.itemPath == "4/0"){ 
      if ((attr[0] == "set_on") | (attr[0] == "on")) switchRelay(1);
      if (attr[0] == "set_off" | (attr[0] == "off")) switchRelay(0);      
    }

//41 Relais/getStatus
    if (dissectResult.itemPath == "4/1"){ 
      if (digitalRead(RELAY_PIN)){
        delay(2000);
        pub(3,0, "on");
      }else{
        delay(2000);
        pub(3,0, "off");
      }
    }
//xx
  
  
  }
}
void ESP8266_Basic::ade_Callback(char* sample, uint16_t instREG) {
  if (instREG == V) pub(2,1,17, sample);  
  if (instREG == IA) pub(2,1,15, sample);  
  if (instREG == IB) pub(2,1,16, sample);  
}
//===============================================================================
//  AktSen Control 
//===============================================================================
//===> updateMeasurement <-----------------------------------------------------
void ESP8266_Basic::handle_Measurement(){

  //timeClient.update();
  ADE.updateEnergy();

  if (mqtt_client.connected()){
    long now = millis();
    if (now - lastMeasure_time > ADE.read(updateTimeMQTT)) {
      lastMeasure_time = now;
      //run_oneWire();
      //run_I2C();

      char chr[50];
      String strVal = ADE.formatDouble(ADE.getVRMS(),5);
      strcpy(chr, strVal.c_str());
      pub(2,1,0, chr);
      strVal = String(ADE.getVRMSrel());
      strcpy(chr, strVal.c_str());
      pub(2,1,18, chr);
     
      strVal = ADE.formatDouble(ADE.getIRMSA(),5);
      strcpy(chr, strVal.c_str());
      pub(2,1,1, chr);
      strVal = String(ADE.getIRMSArel());
      strcpy(chr, strVal.c_str());
      pub(2,1,19, chr);

      strVal = ADE.formatDouble(ADE.getIRMSB(),5);
      strcpy(chr, strVal.c_str());
      pub(2,1,2, chr);
      strVal = String(ADE.getIRMSBrel());
      strcpy(chr, strVal.c_str());
      pub(2,1,20, chr);

      strVal = String(ADE.getPFA());
      strcpy(chr, strVal.c_str());
      pub(2,1,3, chr);
      strVal = String(ADE.getPFB());
      strcpy(chr, strVal.c_str());
      pub(2,1,4, chr);
      strVal = String(ADE.getANGLE_A());
      strcpy(chr, strVal.c_str());
      pub(2,1,5, chr);
      strVal = String(ADE.getANGLE_B());
      strcpy(chr, strVal.c_str());
      pub(2,1,6, chr);
      strVal = String(ADE.getPERIOD(), 5);
      strcpy(chr, strVal.c_str());
      pub(2,1,7, chr);
      strVal = String(ADE.getFREQ(), 5);
      strcpy(chr, strVal.c_str());
      pub(2,1,8, chr);
      
      strVal = ADE.formatDouble(ADE.getP_A(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,9, chr);
      strVal = String(ADE.getP_Arel());
      strcpy(chr, strVal.c_str());
      pub(2,1,21, chr);
      
      strVal = ADE.formatDouble(ADE.getQ_A(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,10, chr);
      strVal = String(ADE.getQ_Arel());
      strcpy(chr, strVal.c_str());
      pub(2,1,22, chr);
      
      strVal = ADE.formatDouble(ADE.getS_A(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,11, chr);
      strVal = String(ADE.getS_Arel());
      strcpy(chr, strVal.c_str());
      pub(2,1,23, chr);
      
      strVal = ADE.formatDouble(ADE.getP_B(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,12, chr);
      strVal = String(ADE.getP_Brel());
      strcpy(chr, strVal.c_str());
      pub(2,1,24, chr);
      
      strVal = ADE.formatDouble(ADE.getQ_B(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,13, chr);
      strVal = String(ADE.getQ_Brel());
      strcpy(chr, strVal.c_str());
      pub(2,1,25, chr);
      
      strVal = ADE.formatDouble(ADE.getS_B(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,14, chr);
      strVal = String(ADE.getS_Brel());
      strcpy(chr, strVal.c_str());
      pub(2,1,26, chr);

      //Energy
      for (int i=0; i<6; i++){
        strVal = String(ADE.energy[i],7);
        strcpy(chr, strVal.c_str());
        pub(2,1,27+i, chr);
      }


/*      
      strVal = ADE.formatDouble(ADE.getW_A(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,27, chr);
      strVal = ADE.formatDouble(ADE.getWb_A(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,28, chr);
      strVal = ADE.formatDouble(ADE.getWs_A(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,29, chr);
      
      strVal = ADE.formatDouble(ADE.getW_B(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,30, chr);
      strVal = ADE.formatDouble(ADE.getWb_B(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,31, chr);
      strVal = ADE.formatDouble(ADE.getWs_B(),7);
      strcpy(chr, strVal.c_str());
      pub(2,1,32, chr);
*/

      strVal = timeClient.getFormattedTime();
      strcpy(chr, strVal.c_str());
      pub(2,1,33, chr);

      //temperature & pressure from BMP180
      strVal = bmp.readTemperature();
      strcpy(chr, strVal.c_str());
      pub(2,1,35, chr);
      strVal = bmp.readPressure();
      strcpy(chr, strVal.c_str());
      pub(2,1,36, chr);

    }
  }
}
//===> run I2C <-----------------------------------------------------
void ESP8266_Basic::run_I2C(){
  int nDevices = 0;
  int mDevices = 0;
  String str; char chr[15];
 
  brzo_i2c_setup(I2C_SDA, I2C_SCL, 2000);
       
  //pinMode(3, OUTPUT); //RxD
  //pinMode(1, OUTPUT); //TxD
  //Wire.begin(3, 1);   //RxD,TxD
  bmp.begin();

}

//===============================================================================
//  MQTT Control 
//===============================================================================
//===> publish Topics <--------------------------------------------------------
bool ESP8266_Basic::pub(int e1, char* Payload){
  String strTopic = buildE1(e1);
  mqtt_client.publish(strTopic.c_str(), Payload); 
  mqtt_client.loop();
}
bool ESP8266_Basic::pub(int e1, int e2, char* Payload){
  String strTopic = buildE2(e1, e2);
  mqtt_client.publish(strTopic.c_str(), Payload); 
  mqtt_client.loop();
}
bool ESP8266_Basic::pub(int e1, int e2, int e3, char* Payload){
  String strTopic = buildE3(e1, e2, e3);
  mqtt_client.publish(strTopic.c_str(), Payload); 
  mqtt_client.loop();
}
/*
bool ESP8266_Basic::pub(int e1, int e2, int e3, int e4, char* Payload){
  String strTopic = buildE4(e1, e2, e3, e4);
  mqtt_client.publish(strTopic.c_str(), Payload); 
  mqtt_client.loop();
}
*/
//===> build Topics <----------------------------------------------------------
String ESP8266_Basic::buildE1(int e1){
  String strTopic = cfg.mqttDeviceName;
  strTopic += "/";
  strTopic += topic.pub.E1.item[e1];
  return strTopic;
}
String ESP8266_Basic::buildE2(int e1, int e2){
  String strTopic = buildE1(e1);
  strTopic += "/";
  strTopic += topic.pub.E2.item[e1][e2];
  return strTopic;
}
String ESP8266_Basic::buildE3(int e1, int e2, int e3){
  String strTopic = buildE2(e1, e2);
  strTopic += "/";
  strTopic += topic.pub.E3.item[e1][e2][e3];
  return strTopic;
}
/*
String ESP8266_Basic::buildE4(int e1, int e2, int e3, int 43){
  String strTopic = buildE1(e1);
  strTopic += "/";
  strTopic += buildE2(e1, e2);
  strTopic += "/";
  strTopic += buildE3(e1, e2, e3);
  strTopic += "/";
  strTopic += topic.pub.E4.item[e1][e2][e3][e4];
  return strTopic;
}
*/



//===> dissect incomming subscribe <-------------------------------------------
TdissectResult ESP8266_Basic::dissectPayload(String subTopic, String subValue){
  TdissectResult dissectResult;   
  String Topics[4];
  for (int i = 0; i < 4; i++) {
    Topics[i] = "";
  }
 
  String str = subTopic;
  if (str.startsWith("/")) str.remove(0, 1); 
  if (str.endsWith("/")) str.remove(str.length()-1,str.length()); 
  dissectResult.topic = str;
  dissectResult.value = subTopic;
   
  int index = -1;
  int i = 0;
  do{
   index = str.indexOf("/");
   if (index != -1){
      Topics[i] = str.substring(0, index);	  
	  str.remove(0, index +1); 
	  i++;
	  if (str.indexOf("/") == -1 and str.length() > 0){    //best of the rest
	    index = -1;
		Topics[i] = str;
		i++;
	  }
	}else{
	}
  } while (index != -1); 
  int depth = i;
  
  //find item index
  String itemPath = "";
  if (depth > 1 and Topics[1] != ""){
    for (int i = 0; i < topic.sub.E1.count; i++) {
	  if (topic.sub.E1.item[i] != NULL){
	    if (strcmp(topic.sub.E1.item[i], Topics[1].c_str()) == 0){
          dissectResult.E1 = i;
		  itemPath = String(i);
		  dissectResult.found = true;
		  break;
        }else dissectResult.found = false;
	  }
    }
  }	
  if (depth > 2 and Topics[2] != ""){
    for (int i = 0; i < topic.sub.E2.count; i++) {
	  if (topic.sub.E2.item[dissectResult.E1][i] != NULL){
	    if (strcmp(topic.sub.E2.item[dissectResult.E1][i], Topics[2].c_str()) == 0){
          dissectResult.E2 = i;
		  itemPath += "/";
		  itemPath += String(i);
		  dissectResult.found = true;
		  break;
        }else dissectResult.found = false;
	  }
    }
  }	
  if (depth > 3 and Topics[3] != ""){
    for (int i = 0; i < topic.sub.E3.count; i++) {
	  if (topic.sub.E3.item[dissectResult.E1][dissectResult.E2][i] != NULL){
	    if (strcmp(topic.sub.E3.item[dissectResult.E1][dissectResult.E2][i], Topics[3].c_str()) == 0){
          dissectResult.E3 = i;
		  itemPath += "/";
		  itemPath += String(i);
		  dissectResult.found = true;
		  break;
        }else dissectResult.found = false;
	  }
    }
  }	
  dissectResult.itemPath = itemPath;
  
  return dissectResult; 
}

//===> publish WiFi Configuration <-------------------------------------------------
void ESP8266_Basic::pubConfig(){
  pub(0,0,0, cfg.webUser);
  pub(0,0,1, cfg.webPassword);
  pub(0,1,0, cfg.apName);
  pub(0,1,1, cfg.apPassword);
  pub(0,2,0, cfg.wifiSSID);
  pub(0,2,1, cfg.wifiPSK);
  pub(0,2,2, cfg.wifiIP);
  pub(0,3,0, cfg.mqttServer);
  pub(0,3,1, cfg.mqttPort);
  pub(0,4,0, cfg.updateServer);
  pub(0,4,1, cfg.filePath);
  //pub(0,3,2, cfg.mqttDeviceName);  
}

//===============================================================================
//  Public WiFi-Manager-Control 
//===============================================================================

//===> Start WiFi Connection <-------------------------------------------------
void ESP8266_Basic::start_WiFi_connections(){
  checkFlash();
  config_running = true;
  
  read_cfg();
  read_MyFile();
  
  if (start_WiFi()){
    WiFi.mode(WIFI_STA);     //exit AP-Mode if set once
	  config_running = false;
	  startConfigServer();
    timeClient.begin();
  }else{
    startAccessPoint();
  }
  printCFG();
}

//===> handle connections WiFi, MQTT, WebServer <------------------------------
void ESP8266_Basic::handle_connections(){
  
  webServer.handleClient();
  
  if (config_running == false){
    if (WiFi.status() == WL_CONNECTED) {
 	  mqtt_client.loop();
	  
	  if (!mqtt_client.connected()){
	    Serial.println("### MQTT has disconnected...");
	    mqtt_client.disconnect();
		strcpy(cfg.mqttStatus, "disconnected");
		start_MQTT();
	  }
	  
    }else{
      Serial.println("### WIFI has disconnected...");
	  if (!start_WiFi()){
		start_WiFi_connections();
	  }else{
	    Serial.println("### WIFI reconnect successful...");
	  };

      //publish_value(publish_status_topic[1], "off");
      //restart_wifi();
	  //WIFImanager();
	
	}
  }
  delay(1);
}


//===============================================================================
//  private WiFi-Manager-Control 
//===============================================================================

//===> start ConfigServer <----------------------------------------------------
void ESP8266_Basic::startConfigServer(){  
  webServer.set_cfgPointer(&cfg);
  //webServer.set_sensorPointer(&DS18B20_Sensors, &HTU21_Sensors, &BMP180_Sensors);
  webServer.start();
}

//===> start AP <--------------------------------------------------------------
void ESP8266_Basic::startAccessPoint(){
  Serial.println("AccessPoint start");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(cfg.apName, cfg.apPassword);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  startConfigServer();
}

//===> Set Function for save cfg Callback <------------------------------------
void ESP8266_Basic::cfgChange_Callback(){
  Serial.println("incomming Callback, config has changed!!");
  printCFG();
  write_cfgFile();
};

//===> WIFI SETUP <------------------------------------------------------------
bool ESP8266_Basic::start_WiFi(){
bool WiFiOK = false;

  delay(10);
  Serial.println();
  Serial.print("Connecting WiFi to: ");
  Serial.println(cfg.wifiSSID);
   
  WiFi.begin(cfg.wifiSSID, cfg.wifiPSK);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED and i < 31) {
    delay(500);
    Serial.print(".");
	i++;
  }
  Serial.println("");
  
  if (WiFi.status() == WL_CONNECTED){
    WiFiOK = true; 
    WIFI_reconnect = true;
    Serial.println("");
    Serial.print("WiFi connected with IP:    ");Serial.println(WiFi.localIP());
	  strcpy( cfg.wifiIP, IPtoString(WiFi.localIP()).c_str()  );
	  strcpy( cfg.wifiSSID, WiFi.SSID().c_str() );
	  strcpy( cfg.wifiPSK, WiFi.psk().c_str() );
	
    //IPAddress ip = WiFi.localIP();
    //TopicHeader = ip[3];

    //MySQL   
    //start_MySQL();
    
  }  
  return WiFiOK; 
}

//===> MQTT SETUP <---------------------------------------------------------
bool ESP8266_Basic::start_MQTT(){
bool MQTTOK = false;

  Serial.print("Connecting to MQTT-Broker: ");
  Serial.print(cfg.mqttServer);Serial.print(":");Serial.println(cfg.mqttPort);
  
  mqtt_client.setServer(charToIP(cfg.mqttServer), atoi(cfg.mqttPort)); 
 
  //boolean connect (clientID, willTopic, willQoS, willRetain, willMessage) 
  mqtt_client.disconnect();
  //if (mqtt_client.connect(cfg.mqttDeviceName)) {
  String lastWillTopic = "ESP8266/Devices/";
  lastWillTopic += cfg.mqttDeviceName;
  if (mqtt_client.connect(cfg.mqttDeviceName,lastWillTopic.c_str() , 0, false, "Dead")) {
    Serial.println("MQTT connected");
	  strcpy(cfg.mqttStatus, "connected");
	  MQTTOK = true;	        
	  
    if (WIFI_reconnect == true){
      WIFI_reconnect = false;
	    pub(1,0,0, "on");
	    pub(1,0,0, "off");
    }
    pub(1,0,1, "on");
    pub(1,0,1, "off");
	
    //testament
    mqtt_client.publish(lastWillTopic.c_str(), "Alive");

    //broker_subcribe();
	  String sub = cfg.mqttDeviceName;
	  sub += "/ADE7953/Control/#";
	  mqtt_client.subscribe(sub.c_str());
    mqtt_client.loop();
 
    sub = cfg.mqttDeviceName;
    sub += "/ADE7953/getValues/#";
    mqtt_client.subscribe(sub.c_str());
    mqtt_client.loop();

    sub = cfg.mqttDeviceName;
    sub += "/Relay/set";
    mqtt_client.subscribe(sub.c_str());
    mqtt_client.loop();

    sub = cfg.mqttDeviceName;
    sub += "/Relay/getStatus";
    mqtt_client.subscribe(sub.c_str());
    mqtt_client.loop();
  }

  //run_oneWire();
  run_I2C();
  
  return MQTTOK;
}


//===> MySQL SETUP <---------------------------------------------------------
/*void ESP8266_Basic::start_MySQL(){
 
  IPAddress server_addr(192,168,1,3);  // IP of the MySQL *server* here
  char user[] = "fhemuser";              // MySQL user login username
  char password[] = "fhempassword";        // MySQL user login password

  Serial.println("Connecting to MySQL-Server");
  MySQL_Connection conn((WiFiClient *)&wifi_client);
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(100);
  }
  else
    Serial.println("Connection failed.");

  // Sample query
  //char INSERT_SQL[] = "use fhem; INSERT INTO `current`(`DEVICE`, `TYPE`, `EVENT`, `READING`, `VALUE`, `UNIT`) VALUES (´ESP8266-Ch01´, `temperature:55.55`, `temperature`, 55.55, ´°C´)";

  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute("use fhem;");
  //cur_mem->execute("INSERT INTO `history`(`DEVICE`, `TYPE`, `EVENT`, `READING`, `VALUE`, `UNIT`) VALUES ([`ESP8266-Ch01`], [`1-Wire`], [`temperature:55.55`], [`temperature`], [55.55], [`C`]);");
  cur_mem->execute("INSERT INTO history (DEVICE, TYPE, EVENT, READING, VALUE, UNIT) VALUES ('ESP8266-Ch01', '1-Wire', 'temperature:55.55', 'temperature', 55.55, '°C');");

  
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
    
  conn.close();
    
}*/

//===============================================================================
//  Timer Stuff
//===============================================================================


void ESP8266_Basic::setup_Timer() {

  os_timer_setfn(&timer, tick, NULL);
  os_timer_arm(&timer, TIMER_T, true); // TIMER_T ms
}

void ESP8266_Basic::timerCallback() {
  
  ticks++;
  switch(currentLedMode) {
    case OFF:   Led(0); break;
    case ON:    Led(1); break;
    case BLINK: Led((ticks/BLINK_T) % 2); break;
  }
}

//===============================================================================
//  Peripherals
//===============================================================================

void ESP8266_Basic::setup_Peripherals() {

  //pinMode(LED2_PIN, OUTPUT);
  //pinMode(LED3_PIN, OUTPUT);
  

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  //pinMode(LED_PIN, OUTPUT);

  WS_LED.setBrightness(100);
  WS_LED.begin();
  WS_LED.show(); // Initialize all pixels to 'off'

  for(int i= 0; i< 17; i++) {
      buttonPinState[i]= 0;
      lastDebounceTime[i]= 0;
  }
  pinMode(RELAY_PIN, OUTPUT);
  
}

// software debouncer
int ESP8266_Basic::getButtonPinState(int buttonPin) {

  // combine with hardware debouncer (100 nF capacitor from buttonPin to GND)
  
  int lastButtonPinState= buttonPinState[buttonPin];
  buttonPinState[buttonPin]= digitalRead(buttonPin); 
  unsigned long now= millis();
  /* char s[128];
  sprintf(s, "%d(%d) -> %d(%d)", lastButtonPinState, lastDebounceTime[buttonPin], 
    buttonPinState[buttonPin], now);
  Serial.println(s);   */
  if(buttonPinState[buttonPin] != lastButtonPinState)
    lastDebounceTime[buttonPin]= now;
  if(now - lastDebounceTime[buttonPin]> DEBOUNCETIME) 
    return buttonPinState[buttonPin];
  else
    return -1; // undecided, still bouncing
}

void ESP8266_Basic::printButtonMode(String msg, buttonMode_t mode) {
  
  Serial.println(msg+": Button mode S= "+String(mode.S)+
    " L= "+String(mode.L)+" button= "+String(mode.state)+
    " idle= "+String(mode.idle));
}

void ESP8266_Basic::setButtonMode(buttonMode_t mode) {
  
  onSetButtonMode(currentButtonMode, mode);
  currentButtonMode= mode;
}

void ESP8266_Basic::handle_Peripherals() {

  // how to use the buttonMode?
  // - state signals if the button is up (0) or down (1)
  // - statex signals if state has been the same for at least BTIME milliseconds
  // - a short press of the button toggles the modeS between off (0) and on (1)
  // - a long press of the button toggles the modeL between off (0) and on (1)

  int buttonPinState= getButtonPinState(BUTTON_PIN);
  if(buttonPinState < 0) return; // still bouncing
  
  unsigned long now= millis();

  buttonMode_t mode= currentButtonMode;
  mode.state= !buttonPinState; // down if pin is 0
  if(mode.state != currentButtonMode.state) {
    // button changed
    mode.t= now;  
    /*Serial.println("Button changed to "+ 
      String(mode.state)+" @ "+String(mode.t));*/
    if(!mode.state) {
       // button up  
       if(mode.idle) mode.L= !mode.L; else mode.S= !mode.S;
    }
    mode.idle= 0;  
    setButtonMode(mode);
  } else {
    if(!mode.idle && (now - mode.t >= BTIME)) {
      mode.idle= 1;
      setButtonMode(mode);
    }
  }
}

void ESP8266_Basic::Led(int on) {

  if (on){ 
    WS_LED.setPixelColor(0, WS_LED.Color(255,0,0));
    WS_LED.show();    
    WS_LED.setPixelColor(1, WS_LED.Color(255,0,0));
    WS_LED.show();    
  }else{
    WS_LED.setPixelColor(0, WS_LED.Color(0,255,0));
    WS_LED.show();    
    WS_LED.setPixelColor(1, WS_LED.Color(0,255,0));
    WS_LED.show();    
  }
  
  //digitalWrite(LED_PIN, on);
}

void ESP8266_Basic::Relay(int on) {

  digitalWrite(RELAY_PIN, on);
}

//===> button mode service routine --------------------------------------------

void ESP8266_Basic::onSetButtonMode(buttonMode_t oldMode, buttonMode_t newMode) {

  // examples for how to use the idle flag:
  // - if button is pressed, indicate that releasing the button will toggle the L mode
  // - leave an input mode when not button is pressed for some time

  /*printButtonMode("old", oldMode);
  printButtonMode("new", newMode);*/
  if(newMode.S != oldMode.S) switchRelay(newMode.S);
  
  if(newMode.L != oldMode.L) {
    if(newMode.L)
      Serial.println("God mode is on.");
    else 
      Serial.println("God mode is off.");
  } else {
    if(newMode.state && newMode.idle != oldMode.idle && newMode.idle) {
      if(newMode.L) {      
        Serial.println("Prepare to leave God mode.");
        if(newMode.S) currentLedMode= ON; else currentLedMode= OFF;
      } else  {
        Serial.println("Prepare to enter God mode.");
        currentLedMode= BLINK;
      }
    }
  }
}

void ESP8266_Basic::switchRelay(int state) {
  if (state == 1){
    if(!currentButtonMode.L) currentLedMode= ON;   // signalisation of Mode L takes precedence
      Relay(1);
      pub(3,0, "on");        
      Serial.println("Relay is on.");
    } else { 
      if(!currentButtonMode.L) currentLedMode= OFF; // signalisation of Mode L takes precedence
      Relay(0);
      pub(3,0, "off"); 
     Serial.println("Relay is off.");
    }  
}


//===============================================================================
//  Configuration 
//===============================================================================

//===> WIFI Manager Config <---------------------------------------------------
void  ESP8266_Basic::read_cfg(){

  Serial.println("read config");
  if (read_cfgFile()){
    Serial.println("fsMount OK and File exist");
  
  }else{
    Serial.println("create new config");
    strcpy(cfg.webUser, "ESPuser");
    strcpy(cfg.webPassword, "ESPpass");

    String str = "ESP8266_";
    str += String(ESP.getChipId());
    strcpy(cfg.apName, str.c_str());
    strcpy(cfg.apPassword, "ESP8266config");
	
    //strcpy(cfg.wifiSSID, "");
    //strcpy(cfg.wifiPSK, "");
    strcpy(cfg.wifiIP, "");
	
	//strcpy( cfg.wifiIP, IPtoString(WiFi.localIP()).c_str()  );
	strcpy( cfg.wifiSSID, WiFi.SSID().c_str() );
	strcpy( cfg.wifiPSK, WiFi.psk().c_str() );
	
    strcpy(cfg.mqttServer, "");
    strcpy(cfg.mqttPort, "1883");
    strcpy(cfg.mqttDeviceName, cfg.apName);
	
	write_cfgFile();
  }
}

//===> WIFI Manager <----------------------------------------------------------
void ESP8266_Basic::write_cfg() {
 
  //IPAddress ip = WiFi.localIP();
  //TopicHeader = ip[3];
  //String MQTT_DeviceName = TopicHeader;
  //MQTT_DeviceName += "/AktSen";
  //strcpy(cfg.mqttDeviceName, MQTT_DeviceName.c_str());
}

//===> Reset Settings <--------------------------------------------------------
void ESP8266_Basic::resetSettings(){
  Serial.println("resetSettings");
  strcpy(cfg.webUser, "");
  strcpy(cfg.webPassword, "");
  strcpy(cfg.apName, "");
  strcpy(cfg.apPassword, "");
  strcpy(cfg.wifiSSID, "");
  strcpy(cfg.wifiPSK, "");
  strcpy(cfg.wifiIP, "");
  strcpy(cfg.mqttServer, "");
  strcpy(cfg.mqttPort, "1883");
  strcpy(cfg.mqttDeviceName, "");
  strcpy(cfg.updateServer, "");
  strcpy(cfg.filePath, "");
  
  write_cfgFile();
}

//===============================================================================
//  FileSystem
//===============================================================================

//My File
//===> read from MyFile <-------------------------------------------------
bool ESP8266_Basic::read_MyFile(){
  bool readOK = false;
  File MyFile;
  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("");
  Serial.println("mounting FS...for MyFile");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/MyFile.json")) {
      //file exists, reading and loading
      Serial.println("reading Myfile");
      MyFile = SPIFFS.open("/MyFile.json", "r");
      if (MyFile) {
        Serial.println("opened MyFile");
        size_t size = MyFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        MyFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        //json.printTo(Serial);
        if (json.success()) {
          Serial.println("json success to MyFile");
          
		  //Get Data from File
          strcpy(myFile.Field_01, json["Field_01"]);
          strcpy(myFile.Field_02, json["Field_02"]);
		  
	      updateMeasure_time = String(myFile.Field_01).toInt();
          Serial.print("Update Time = ");
          Serial.println(updateMeasure_time);


		  readOK = true;

        } else {
          Serial.println("failed to load json MyFile");
        }
      }
    }else{
	  Serial.println("MyFile does not exist");
	}
  } else {
    Serial.println("failed to mount FS");
  }
  MyFile.close();
  //end read
  return readOK;

};

//===> write to MyFile <--------------------------------------------------
void ESP8266_Basic::write_MyFile(){

  SPIFFS.begin();
  //save the custom parameters to FS
  Serial.println("saving MyFile");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  //Serial.println("bevor write_cfgFile ");
  //json.printTo(Serial);

  json["Field_01"] = myFile.Field_01;
  json["Field_02"] = myFile.Field_02;

  File MyFile = SPIFFS.open("/MyFile.json", "w");
  if (!MyFile) {
    Serial.println("failed to open MyFile for writing");
    Serial.print("format file System.. ");
	SPIFFS.format();
	Serial.println("done");
	//write_cfgFile();
 }

  json.printTo(Serial);
  json.printTo(MyFile);
  MyFile.close();
  //end save

}

//===> read Config from File <-------------------------------------------------
bool ESP8266_Basic::read_cfgFile(){
  bool readOK = false;
  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("");
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File cfgFile = SPIFFS.open("/config.json", "r");
      if (cfgFile) {
        Serial.println("opened config file");
        size_t size = cfgFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        cfgFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        //json.printTo(Serial);
        if (json.success()) {
          Serial.println("json success");
          
		  //Get Data from File
          strcpy(cfg.webUser, json["webUser"]);
          strcpy(cfg.webPassword, json["webPassword"]);
          strcpy(cfg.apName, json["apName"]);
          strcpy(cfg.apPassword, json["apPassword"]);
          strcpy(cfg.wifiSSID, json["wifiSSID"]);
          strcpy(cfg.wifiPSK, json["wifiPSK"]);
          strcpy(cfg.wifiIP, json["wifiIP"]);
          strcpy(cfg.mqttServer, json["mqttServer"]);
          strcpy(cfg.mqttPort, json["mqttPort"]);
          strcpy(cfg.mqttDeviceName, json["mqttDeviceName"]);
          strcpy(cfg.updateServer, json["updateServer"]);
          strcpy(cfg.filePath, json["filePath"]);

		  readOK = true;

        } else {
          Serial.println("failed to load json config");
        }
      }
    }else{
	  Serial.println("file does not exist");
	}
  } else {
    Serial.println("failed to mount FS");
  }
  cfgFile.close();
  //end read
  return readOK;

};

//===> write Config to File <--------------------------------------------------
void ESP8266_Basic::write_cfgFile(){

  SPIFFS.begin();
  //save the custom parameters to FS
  Serial.println("saving config");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  //Serial.println("bevor write_cfgFile ");
  //json.printTo(Serial);

  json["webUser"] = cfg.webUser;
  json["webPassword"] = cfg.webPassword;
  json["apName"] = cfg.apName;
  json["apPassword"] = cfg.apPassword;
  json["wifiSSID"] = cfg.wifiSSID;
  json["wifiPSK"] = cfg.wifiPSK;
  json["wifiIP"] = cfg.wifiIP;
  json["mqttServer"] = cfg.mqttServer;
  json["mqttPort"] = cfg.mqttPort;
  json["mqttDeviceName"] = cfg.mqttDeviceName;
  json["updateServer"] = cfg.updateServer;
  json["filePath"] = cfg.filePath;

  File cfgFile = SPIFFS.open("/config.json", "w");
  if (!cfgFile) {
    Serial.println("failed to open config file for writing");
    Serial.print("format file System.. ");
	SPIFFS.format();
	Serial.println("done");
	//write_cfgFile();
 }

  //json.printTo(Serial);
  json.printTo(cfgFile);
  cfgFile.close();
  //end save

}

//===============================================================================
//  helpers
//===============================================================================

//===> IPToString  <-----------------------------------------------------------
String ESP8266_Basic::IPtoString(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

IPAddress ESP8266_Basic::charToIP(char* IP) {
  IPAddress MyIP;

  String str = String(IP);
  for (int i = 0; i < 4; i++){
    String x = str.substring(0, str.indexOf("."));
    MyIP[i] = x.toInt();
    str.remove(0, str.indexOf(".")+1); 
  }
  return MyIP;
}

//===> Print Config  <---------------------------------------------------------
void ESP8266_Basic::printCFG(){

  Serial.println("");
  Serial.println("");
  Serial.println("Config:");
  Serial.println("########################################");
  Serial.print("WEBcfg Username:  "); Serial.println(cfg.webUser);
  Serial.print("WEBcfg Password:  "); Serial.println(cfg.webPassword);
  Serial.println("----------------------------------------");
  Serial.print("AP SSID:          "); Serial.println(cfg.apName);
  Serial.print("AP Password:      "); Serial.println(cfg.apPassword);
  Serial.println("----------------------------------------");
  Serial.print("WiFi SSID:        "); Serial.println(cfg.wifiSSID);
  Serial.print("WiFi Password:    "); Serial.println(cfg.wifiPSK);
  Serial.print("DHCP IP:          "); Serial.println(cfg.wifiIP);
  Serial.println("----------------------------------------");
  Serial.print("MQTT-Server IP:   "); Serial.println(cfg.mqttServer);
  Serial.print("MQTT-Server Port: "); Serial.println(cfg.mqttPort);
  Serial.print("MQTT-DeviceName:  "); Serial.println(cfg.mqttDeviceName);
  Serial.println("----------------------------------------");
  Serial.print("Update-Server IP: "); Serial.println(cfg.updateServer);
  Serial.print("FilePath:         "); Serial.println(cfg.filePath);
  Serial.println("########################################");

};

//===> Check Flash Memory <-----------------------------------------------------
void ESP8266_Basic::checkFlash(){
  uint32_t realSize = ESP.getFlashChipRealSize();
  uint32_t ideSize = ESP.getFlashChipSize();
  FlashMode_t ideMode = ESP.getFlashChipMode();

  Serial.println("");
  Serial.println("============================================");
    Serial.printf("Flash real id:   %08X", ESP.getFlashChipId());
    Serial.println("");
    Serial.printf("Flash real size: %u", realSize);
    Serial.println("");

    Serial.printf("Flash ide  size: %u", ideSize);
    Serial.println("");
    Serial.printf("Flash ide speed: %u", ESP.getFlashChipSpeed());
    Serial.println("");
    Serial.printf("Flash ide mode:  %s", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
    Serial.println("");
    
    if(ideSize != realSize) {
        Serial.println("Flash Chip configuration wrong!");
    } else {
        Serial.println("Flash Chip configuration ok.");
    }
  Serial.println("============================================");
  Serial.println("");
    
}






