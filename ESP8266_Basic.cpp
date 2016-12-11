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
//HTU21 Luftfeuchtigkeit  
  //Adafruit_HTU21DF htu = Adafruit_HTU21DF();


//CLASS ESP8266_Basic################################################################
ESP8266_Basic::ESP8266_Basic() : webServer(), 
                                 mqtt_client(wifi_client){
  //Callbacks								 
  webServer.set_saveConfig_Callback(std::bind(&ESP8266_Basic::cfgChange_Callback, this));
  mqtt_client.setCallback(std::bind(&ESP8266_Basic::mqttBroker_Callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}



//===============================================================================
//  AktSen Control 
//===============================================================================
//===> updateMeasurement <-----------------------------------------------------
void ESP8266_Basic::handle_Measurement(){
  if (mqtt_client.connected()){
    long now = millis();
    if (now - lastMeasure_time > updateMeasure_time) {
      lastMeasure_time = now;
      //run_oneWire();
      //run_I2C();

      char chr[50];
      String strVal = String(ADE.getVRMS());
      strcpy(chr, strVal.c_str());
      pub(2,1,0, chr);
      strVal = String(ADE.getIRMSA());
      strcpy(chr, strVal.c_str());
      pub(2,1,1, chr);
      strVal = String(ADE.getIRMSB());
      strcpy(chr, strVal.c_str());
      pub(2,1,2, chr);
    }
  }
}
//===> run I2C <-----------------------------------------------------
void ESP8266_Basic::run_I2C(){
  int nDevices = 0;
  int mDevices = 0;
  String str; char chr[15];
 
  Wire.begin(I2C_SDA, I2C_SCL);   
  
  /*for (int i=0; i<4; i++){
    mux(i);
    if (HTU21_begin()){
      Serial.print("Found HTU21 on Channel "); 
      Serial.println(i); 
      
      nDevices++;
      HTU21_Sensors.count = nDevices;
      HTU21_Sensors.item[nDevices-1].channel = i;
      str = htu.readTemperature();
      strcpy(chr, str.c_str());  
      strcpy(HTU21_Sensors.item[nDevices-1].temperature, chr);
  
      str = htu.readHumidity();
      strcpy(chr, str.c_str());  
      strcpy(HTU21_Sensors.item[nDevices-1].humidity, chr);
    }
    if (BMP180_begin()){
      bmp.begin();
      Serial.print("Found BMP180 on Channel "); 
      Serial.println(i); 
      
      mDevices++;
      BMP180_Sensors.count = mDevices;
      BMP180_Sensors.item[mDevices-1].channel = i;
      str = bmp.readTemperature();
      //Serial.println(str);
      strcpy(chr, str.c_str());  
      strcpy(BMP180_Sensors.item[mDevices-1].temperature, chr);

      str = bmp.readPressure()/100;
      strcpy(chr, str.c_str());  
      strcpy(BMP180_Sensors.item[mDevices-1].pressure, chr);
   }
  }

    for (int i=0; i<HTU21_Sensors.count; i++){
      Serial.println(HTU21_Sensors.item[i].temperature);
      Serial.println(HTU21_Sensors.item[i].humidity);
      pub(3,1,i, HTU21_Sensors.item[i].temperature);
      pub(3,2,i, HTU21_Sensors.item[i].humidity);
    }
    for (int i=0; i<BMP180_Sensors.count; i++){
      Serial.println(BMP180_Sensors.item[i].temperature);
      Serial.println(BMP180_Sensors.item[i].pressure);
      pub(4,1,i, BMP180_Sensors.item[i].temperature);
      pub(4,2,i, BMP180_Sensors.item[i].pressure);
    }*/

  
}

//===> search HTU21 <----------------------------------------------------------
/*bool ESP8266_Basic::HTU21_begin(){
  bool HTU21_found = false;
  byte error;

    Wire.beginTransmission(0x40);
    error = Wire.endTransmission(); 
    if (error == 0) HTU21_found = true;
    
    return HTU21_found;
}
//===> search BMP180 <----------------------------------------------------------
bool ESP8266_Basic::BMP180_begin(){
  bool BMP180_found = false;
  byte error;

    Wire.beginTransmission(0x77);
    error = Wire.endTransmission(); 
    if (error == 0) BMP180_found = true;
    
    return BMP180_found;
}

//===============================================================================
//  MUX PCA9544
//===============================================================================
void ESP8266_Basic::mux(byte channel){
  byte controlRegister = 0x04;  
  controlRegister |= channel;
  Wire.beginTransmission(MUX);
  if (channel == 0xFF){Wire.write(0x00);} //deselect all channels
  else {Wire.write(controlRegister);}     //set to selected channel
  Wire.endTransmission();
}
//===============================================================================
//  Scan I2C-Bus
//===============================================================================

void ESP8266_Basic::scanI2C(){
  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C-Bus......");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);

      if (address == 0x77) {Serial.println(" BMP180");}
      else if (address == 0x40) {Serial.println(" SI7021");}
      else if (address >= 0x70 & address <= 0x77) {Serial.println(" PCA9544");}
      else if (address >= 0x60 & address <= 0x67) {Serial.println(" MCP4725");}
      else {Serial.println(" unknown");};
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 }
 
//===> run 1Wire <-----------------------------------------------------
void ESP8266_Basic::run_oneWire(){
  OneWire oneWire(oneW);                   //GPIO 2
  DallasTemperature DS18B20(&oneWire);
  DeviceAddress DS18B20device;
  
  DS18B20.begin();
  delay(100);
  DS18B20.setResolution(12);  //##
  delay(100);

  DS18B20_Sensors.count = DS18B20.getDeviceCount();
  delay(100);
  DS18B20.requestTemperatures(); 
  delay(100);

  Serial.print("#### DeviceCount = ");
  Serial.println(DS18B20_Sensors.count);
  
  for (int i = 0; i < DS18B20_Sensors.count; i++) {
    String str_temp = String(DS18B20.getTempCByIndex(i));
    delay(100);
	  char temp[7];
    strcpy(temp, str_temp.c_str());  
	  pub(2,1,i, temp);
		
	  DS18B20.getAddress(DS18B20device, i);
    delay(100);
    String strDeviceAddress = "";
	  char str[5];
	  for (int j = 0; j < 8; j++) {
      sprintf(str, "%02X", DS18B20device[j]);
	    strDeviceAddress += str;
	    if (j < 7) strDeviceAddress += "-";
	  }
	  strcpy(DS18B20_Sensors.item[i].serial, strDeviceAddress.c_str());
	  strcpy(DS18B20_Sensors.item[i].temperature, temp);

	  //Serial.println(strDeviceAddress);
  }
}*/

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

//===> incomming subscribe <---------------------------------------------------
void ESP8266_Basic::mqttBroker_Callback(char* topic, byte* payload, unsigned int length) {

  char value[50] = "";
  char chr[50] = "";
  int samples = 50;
  double inst[samples];
  String str = "";
  
  for (int i = 0; i < length; i++) {
    value[i] = payload[i];
  }

  Serial.print("incoming subscribe: ");
  Serial.print(topic);
  Serial.print(" | ");
  Serial.println(value);
  
  TdissectResult dissectResult;    
  dissectResult = dissectPayload(topic, value);

  if (dissectResult.found){
    if (dissectResult.itemPath == "2/0"){         //ADE7953.read
      String strReg = "0x";
      strReg += String(ADE.StrToInt(value), HEX);
      strcpy(chr, strReg.c_str());
      pub(2,0, chr);

      uint32_t reg = ADE.read(String(value));
      String str = "0x";
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
    if (dissectResult.itemPath == "2/1"){         //ADE7953.write
      ADE.write(String(value));
      
      String strReg = "0x";
      int pos = String(value).indexOf(",");
      strReg += String(ADE.StrToInt(String(value).substring(0, pos)), HEX);
      
      strcpy(chr, strReg.c_str());
      pub(2,0, chr);
      
      uint32_t reg = ADE.read(String(value));
      String str = "0x";
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

    if (dissectResult.itemPath == "2/2"){         //ADE7953.init
      ADE.init();
    }
    
    if (dissectResult.itemPath == "2/3/0"){         //ADE7953.getV_INST
      for (int i = 0; i<samples; i++){
        inst[i] = ADE.getV();
      }
      for (int i = 0; i<samples; i++){
        for( int j = 0; j < sizeof(chr);  j++ )
          chr[j] = (char)0;
          
        str = String(inst[i]);
        strcpy(chr, str.c_str());      
        pub(2,1,3, chr);
        //delay(100);
      }
    }
   
    if (dissectResult.itemPath == "3/1/0"){
      //Write Field_01
      strcpy(myFile.Field_01, value);
      write_MyFile();
      updateMeasure_time = String(value).toInt();
      Serial.print("UpdateMesure_time = "); Serial.println(value);
    }
    
    /*if (dissectResult.itemPath == "1/0/0"){
	    if (strcmp(value, "Reboot") == 0){
	      ESP.restart();
	    }
	  }
    if (dissectResult.itemPath == "1/0/1"){
	    pubConfig();
	  }
    if (dissectResult.itemPath == "1/0/2"){
      //UpdateFirmware()
      webServer.updateFirmware();
    }
	
    if (dissectResult.itemPath == "3/0/0"){
	    //Read Field_01
	    strcpy(myFile.Field_01, "");
	    read_MyFile();
	    Serial.println(myFile.Field_01);
	  }*/
  }
}

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
    start_MySQL();
    
  }  
  return WiFiOK; 
}

//===> MQTT SETUP <---------------------------------------------------------
bool ESP8266_Basic::start_MQTT(){
bool MQTTOK = false;

  Serial.print("Connecting to MQTT-Broker: ");
  Serial.print(cfg.mqttServer);Serial.print(":");Serial.println(cfg.mqttPort);
  
  mqtt_client.setServer(charToIP(cfg.mqttServer), atoi(cfg.mqttPort)); 
 
  if (mqtt_client.connect(cfg.mqttDeviceName)) {
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
	
    //broker_subcribe();
	String sub = cfg.mqttDeviceName;
	sub += "/#";
	mqtt_client.subscribe(sub.c_str());
    mqtt_client.loop();
	sub = "/";
	sub += cfg.mqttDeviceName;
	sub += "/#";
	mqtt_client.subscribe(sub.c_str());
    mqtt_client.loop();

  }

    //run_oneWire();
    run_I2C();
  
  return MQTTOK;
}


//===> MySQL SETUP <---------------------------------------------------------
void ESP8266_Basic::start_MySQL(){
 
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






