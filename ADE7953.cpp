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

Treg reg[] ={
  //8-Bit Registers
  //   Name              Address         Def       Signed RW     Changed
  { 8, "SAGCYC",         SAGCYC,         0x000000, false, true,  false},
  { 8, "DISNOLOAD",      DISNOLOAD,      0x000000, false, true,  false},
  { 8, "LCYCMODE",       LCYCMODE,       0x000040, false, true,  false},
  { 8, "PGA_V",          PGA_V,          0x000001, false, true,  false},
  { 8, "PGA_IA",         PGA_IA,         0x000001, false, true,  false},
  { 8, "PGA_IB",         PGA_IB,         0x000001, false, true,  false},
  { 8, "WRITE_PROTECT",  WRITE_PROTECT,  0x000000, false, true,  false},
  { 8, "LAST_OP",        LAST_OP,        0x000000, false, false, false},
  { 8, "LAST_RWDATA8",   LAST_RWDATA8,   0x000000, false, false, false},
  { 8, "Version",        Version,        0x000000, false, false, false},
  { 8, "EX_REF",         EX_REF,         0x000000, false, true,  false},
  { 8, "unlock",         unlock,         0x0000AD, false, false, false},

  //16-Bit Registers
  //   Name              Address         Def       Signed RW     Changed
  {16, "ZXTOUT",         ZXTOUT,         0x00FFFF, false, true,  false},
  {16, "LINECYC",        LINECYC,        0x000000, false, true,  false},
  {16, "CONFIG",         CONFIG,         0x008004, false, true,  false},
  {16, "CF1DEN",         CF1DEN,         0x00003F, false, true,  false},
  {16, "CF2DEN",         CF2DEN,         0x00003F, false, true,  false},
  {16, "CFMODE",         CFMODE,         0x000300, false, true,  false},
  {16, "PHCALA",         PHCALA,         0x000000, true,  true,  false},
  {16, "PHCALB",         PHCALB,         0x000000, true,  true,  false},
  {16, "PFA",            PFA,            0x000000, true,  true,  false},
  {16, "PFB",            PFB,            0x000000, true,  true,  false},
  {16, "ANGLE_A",        ANGLE_A,        0x000000, true,  true,  false},
  {16, "ANGLE_B",        ANGLE_B,        0x000000, true,  true,  false},
  {16, "Period",         Period,         0x000000, false, true,  false},
  {16, "ALT_OUTPUT",     ALT_OUTPUT,     0x000000, false, true,  false},
  {16, "LAST_ADD",       LAST_ADD,       0x000000, false, true,  false},
  {16, "LAST_RWDATA16",  LAST_RWDATA16,  0x000000, false, true,  false},
  {16, "Reserved1",      Reserved1,      0x000030, false, false,  false},

  //24-Bit Registers
  //   Name              Address         Def       Signed RW     Changed
  {24, "SAGLVL",         SAGLVL,         0x000000, false, true,  false},
  {24, "ACCMODE",        ACCMODE,        0x000000, false, true,  false},
  {24, "AP_NOLOAD",      AP_NOLOAD,      0x00E419, false, true,  false},
  {24, "VAR_NOLOAD",     VAR_NOLOAD,     0x00E419, false, true,  false},
  {24, "VA_NOLOAD",      VA_NOLOAD,      0x000000, false, true,  false},
  {24, "AVA",            AVA,            0x000000, true,  false, false},
  {24, "BVA",            BVA,            0x000000, true,  false, false},
  {24, "AWATT",          AWATT,          0x000000, true,  false, false},
  {24, "BWATT",          BWATT,          0x000000, true,  false, false},
  {24, "AVAR",           AVAR,           0x000000, true,  false, false},
  {24, "BVAR",           BVAR,           0x000000, true,  false, false},
  {24, "IA",             IA,             0x000000, true,  false, false},
  {24, "IB",             IB,             0x000000, true,  false, false},
  {24, "V",              V,              0x000000, true,  false, false},
  {24, "IRMSA",          IRMSA,          0x000000, false, false, false},
  {24, "IRMSB",          IRMSB,          0x000000, false, false, false},
  {24, "VRMS",           VRMS,           0x000000, false, false, false},
  {24, "AENERGYA",       AENERGYA,       0x000000, true,  false, false},
  {24, "AENERGYB",       AENERGYB,       0x000000, true,  false, false},
  {24, "RENERGYA",       RENERGYA,       0x000000, true,  false, false},
  {24, "RENERGYB",       RENERGYB,       0x000000, true,  false, false},
  {24, "APENERGYA",      APENERGYA,      0x000000, true,  false, false},
  {24, "APENERGYB",      APENERGYB,      0x000000, true,  false, false},
  {24, "OVLVL",          OVLVL,          0xFFFFFF, false, true,  false},
  {24, "OILVL",          OILVL,          0xFFFFFF, false, true,  false},
  {24, "VPEAK",          VPEAK,          0x000000, false, false, false},
  {24, "RSTVPEAK",       RSTVPEAK,       0x000000, false, false, false},
  {24, "IAPEAK",         IAPEAK,         0x000000, false, false, false},
  {24, "RSTIAPEAK",      RSTIAPEAK,      0x000000, false, false, false},
  {24, "IBPEAK",         IBPEAK,         0x000000, false, false, false},
  {24, "RSTIBPEAK",      RSTIBPEAK,      0x000000, false, false, false},
  {24, "IRQENA",         IRQENA,         0x100000, false, true,  false},
  {24, "IRQSTATA",       IRQSTATA,       0x000000, false, false, false},
  {24, "RSTIRQSTATA",    RSTIRQSTATA,    0x000000, false, false, false},
  {24, "IRQENB",         IRQENB,         0x000000, false, true,  false},
  {24, "IRQSTATB",       IRQSTATB,       0x000000, false, false, false},
  {24, "RSTIRQSTATB",    RSTIRQSTATB,    0x000000, false, false, false},
  {24, "CRC",            CRC,            0xFFFFFF, false, false, false},
  {24, "AIGAIN",         AIGAIN,         0x400000, false, true,  false},
  {24, "AVGAIN",         AVGAIN,         0x400000, false, true,  false},
  {24, "AWGAIN",         AWGAIN,         0x400000, false, true,  false},
  {24, "AVARGAIN",       AVARGAIN,       0x400000, false, true,  false},
  {24, "AVAGAIN",        AVAGAIN,        0x400000, false, true,  false},
  {24, "Reserved2",      Reserved2,      0x000000, false, true,  false},
  {24, "AIRMSOS",        AIRMSOS,        0x000000, false, true,  false},
  {24, "Reserved3",      Reserved3,      0x000000, false, true,  false},
  {24, "VRMSOS",         VRMSOS,         0x000000, false, true,  false},
  {24, "AWATTOS",        AWATTOS,        0x000000, false, true,  false},
  {24, "AVAROS",         AVAROS,         0x000000, false, true,  false},
  {24, "AVAOS",          AVAOS,          0x000000, false, true,  false},
  {24, "BIGAIN",         BIGAIN,         0x400000, false, true,  false},
  {24, "BVGAIN",         BVGAIN,         0x400000, false, true,  false},
  {24, "BWGAIN",         BWGAIN,         0x400000, false, true,  false},
  {24, "BVARGAIN",       BVARGAIN,       0x400000, false, true,  false},
  {24, "BVAGAIN",        BVAGAIN,        0x400000, false, true,  false},
  {24, "Reserved4",      Reserved4,      0x000000, false, true,  false},
  {24, "BIRMSOS",        BIRMSOS,        0x000000, false, true,  false},
  {24, "Reserved5",      Reserved5,      0x000000, false, true,  false},
  {24, "Reserved6",      Reserved6,      0x000000, false, true,  false},
  {24, "BWATTOS",        BWATTOS,        0x000000, false, true,  false},
  {24, "BVAROS",         BVAROS,         0x000000, false, true,  false},
  {24, "BVAOS",          BVAOS,          0x000000, false, true,  false},
  {24, "LAST_RWDATA24",  LAST_RWDATA24,  0x000000, false, false, false},

  //24-Bit SOFT Registers
  //   Name                Address           Def       Signed RW     Changed
  {24, "k_V",              k_V,              0x000001, false, true,  false},
  {24, "k_IA",             k_IA,             0x000001, false, true,  false},
  {24, "k_IB",             k_IB,             0x000001, false, true,  false},
  {24, "WA",               WA,               0x000000, true,  true,  false},
  {24, "WbA",              WbA,              0x000000, true,  true,  false},
  {24, "WsA",              WsA,              0x000000, true,  true,  false},
  {24, "WB",               WB,               0x000000, true,  true,  false},
  {24, "WbB",              WbB,              0x000000, true,  true,  false},
  {24, "WsB",              WsB,              0x000000, true,  true,  false},
  {24, "updateTimeEnergy", updateTimeEnergy, 0x0003E8, false, true,  false},
  {24, "updateTimeMQTT",   updateTimeMQTT,   0x0003E8, false, true,  false},
  {24, "SampleRate",       SampleRate,       0x000001, false, true,  false},
  {24, "Periods",          Periods,          0x000003, false, true,  false}
  };

ADE7953::ADE7953(){
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
  //Check I2C-Communication
  if (read(0x203) == 0xE419){
    Serial.println("I2C-Communication OK");
  }else{
      Serial.println("I2C-Communication failed!!!!");
      while (1){}
  }
  //write(0x284, 0xABABAB);
  //read(0x284);
  //while (1){}

  //write(0x284, 0xABABAB);
  //read(0x284);
  //while (1){}

  //write_ADE7953_json();
  read_ADE7953_json();
  //Test();
  
  Serial.println("start Register settings");
//REQUIRED REGISTER SETTING  
  write(unlock, 0xAD);
  write(Reserved1, 0x30);
  //pREG(unlock);pREG(Reserved1);

//json REGISTER SETTING  
  for (auto &element : reg){
    write(element.regAdr);
    element.changed = false;
  }

  
  //Test();

  return true;
}

//===> Callback for CFGchange <------------------------------------------------
//void ADE7953::set_Callback(CallbackFunction c){
  //myCallback = c;
//}

void ADE7953::setADECallback(ADE_CALLBACK_SIGNATURE) {
    this->callback = callback;
    //return *this;
}

//===============================================================================
//  ADE7953 read/write Register / Bit
//===============================================================================
//write-------------------------------------------------------------
void ADE7953::write(uint16_t Reg, uint32_t val){
  int count = 0;
  
  if (Reg < 0x100 | Reg == 0x702 | Reg == 0x800) {count = 1;} //8Bit inkl. 0x702/0x800
  else if (Reg < 0x200){count = 2;}                           //16Bit 
  else if (Reg < 0x300){count = 3;}                           //24Bit
  else if (Reg < 0x400){count = 4;}                           //32Bit
  else {count = 5;}                                           //soft register

  if (count < 5){                                             //HW register

    uint8_t buffer[10];
    buffer[0] = Reg >> 8;
    buffer[1] = Reg;
    for (int i = 2; i<count+2; i++){
      buffer[i] = (val >> (count-1-i-2)*8);               //write MSB first
    } 
    brzo_i2c_start_transaction(I2Caddr,400);
    brzo_i2c_write(buffer, count+2, false);
    brzo_i2c_end_transaction(); 
  }

  //save to registerArray
  for (auto &element : reg){
    if (element.regAdr == Reg){
      element.regVal = val;
      element.changed = true;
    }
  } 
}

void ADE7953::write(String strRegVal){
  //Serial.println("Write as String strRegVal");
  int pos = strRegVal.indexOf(",");
  String strReg = strRegVal.substring(0, pos);
  String strVal = strRegVal.substring(pos+1);
  
  uint16_t Reg = StrToInt(strReg);
  long int val = StrToInt(strVal);

  write(Reg, val);

  //for (auto &element : reg){
    //if (element.regAdr == Reg){
      //element.regVal = val;
    //}
  //}
  
  //write_ADE7953_json();
  //Test();
}

void ADE7953::write(uint16_t Reg){
  //Serial.println("Write as uint16_t Reg");
  for (auto element : reg){
    if (element.regAdr == Reg){
      write(Reg, element.regVal);
    }
  }
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
uint32_t ADE7953::read(uint16_t Reg){
  int count = 0;
  uint32_t val = 0x00;
  
  if (Reg < 0x100 | Reg == 0x702 | Reg == 0x800) {count = 1;} //8Bit inkl. 0x702/0x800
  else if (Reg < 0x200){count = 2;}                           //16Bit 
  else if (Reg < 0x300){count = 3;}                           //24Bit
  else if (Reg < 0x400){count = 4;}                           //32Bit
  else {count = 5;}                                           //soft register

  if (count < 5){
    uint8_t buffer[10];
    buffer[0] = Reg >> 8;
    buffer[1] = Reg;
    brzo_i2c_start_transaction(I2Caddr, 700);
    brzo_i2c_write(buffer, 2, true); 
    brzo_i2c_read(buffer, count, true);
    brzo_i2c_end_transaction(); 
        
    for (int i = 0; i<count; i++){
      val = (val << 8) + buffer[i];                  //read MSB first
    }

  }else{                                               //read soft Register
    //Serial.println("read SOFT register");
    for (auto element : reg){
      if (element.regAdr == Reg){
        val = element.regVal;
      }
    } 
  }
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
//  FileSystem
//===============================================================================

//ADE7953 config-File-Control
//===> read from ADE7953_json <-------------------------------------------------
bool ADE7953::read_ADE7953_json(){
  Serial.println("###############################");
  Serial.println("Read from json");
  Serial.println("###############################");

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
          //ADE7953_json.AIGAINjson = json["AIGAIN"];
          //strcpy(ADE7953.Field_01, json["Field_01"]);

          int i = 0;
          for (auto element : reg){
            if (element.RW){
              //element.regVal = json[element.regName];
              reg[i].regVal = json[element.regName];
            }
            i++;
          }
          readOK = true;

        }else{
          Serial.println("failed to load json ADE7953");
        }
      }
    }else{
      Serial.println("ADE7953 does not exist");
    }
  }else{
    Serial.println("failed to mount FS");
  }
  ADE7953.close();
  //end read  
  return readOK;
};

//===> write to ADE7953_json <--------------------------------------------------
void ADE7953::write_ADE7953_json(){

  Serial.println("###############################");
  Serial.println("Write to json");
  Serial.println("###############################");
  
  
  SPIFFS.begin();
  //save the custom parameters to FS
  Serial.println("saving ADE7953.json");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  //Serial.println("bevor write_cfgFile ");
  //json.printTo(Serial);

  //json["AIGAIN"]  = ADE7953_json.AIGAINjson;

  for (auto &element : reg){
    if (element.RW){  //and element.changed
      json[element.regName] = element.regVal;
      element.changed = false;
      String line = element.regName  + " | " + String(element.regVal, HEX);
      Serial.println(line);   
    }
  }
  
  File ADE7953 = SPIFFS.open("/ADE7953.json", "w");
  if (!ADE7953) {
    Serial.println("failed to open ADE7953 for writing");
    //Serial.print("format file System.. ");
    //SPIFFS.format();
    //Serial.println("done");
    //write_cfgFile();
  }
  //json.printTo(Serial);
  Serial.println("");
  json.printTo(ADE7953);
  ADE7953.close();
  //end save
}

//===> set default Values to ADE7953 & json <------------------------------------
void ADE7953::setDefault(){
  int timeout = 0;
  
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
      Serial.println("ADE7953.init TIMEOUT!!!!");
      while (1){}
    }
  }
  Serial.println("");
  Serial.println("ADE7953.init OK");  //all register on default 

  //write_ADE7953_json();
  //read_ADE7953_json();
  //Test();
  
//REQUIRED REGISTER SETTING  
  //write(unlock, 0xAD);
  //write(Reserved1, 0x30);
  //pREG(unlock);pREG(Reserved1);

  Serial.println("read Register settings");

//json REGISTER SETTING  
  for (auto &element : reg){
    //write(element.regAdr);
    element.regVal = read(element.regAdr);
    element.changed = true;
  }
  write_ADE7953_json(); 
}

//===============================================================================
//  read values 
//===============================================================================
double ADE7953::getIRMSA(){
  return getFullScaleInput(read(PGA_IA)) * double(read(IRMSA)) / 9032007 * read(k_IA) / 100;
}
double ADE7953::getIRMSArel(){
 return 100.0 / (0x89D147) * double(read(IRMSA));
}
//----------------------------------
double ADE7953::getIRMSB(){
  return getFullScaleInput(read(PGA_IB)) * double(read(IRMSB)) / 9032007 * read(k_IB) / 100;
}
double ADE7953::getIRMSBrel(){
  return 100.0 / (0x89D147) * double(read(IRMSB));
}
//----------------------------------
double ADE7953::getVRMS(){
  return getFullScaleInput(read(PGA_V)) * double(read(VRMS)) / 9032007 * read(k_V) / 100;
}
double ADE7953::getVRMSrel(){
  return 100.0 / (0x89D147) * double(read(VRMS));
}
//--------------------------------------------------------------------------------
double ADE7953::getPFA(){
  double pf = 1.0 / 0x8000 * double(uint16Tolong32(read(PFA))); 
  return pf;
}
double ADE7953::getPFB(){
  double pf = 1.0 / 0x8000 * double(uint16Tolong32(read(PFB)));
  return pf;
}
//----------------------------------
double ADE7953::getANGLE_A(){
  double angle = double(uint16Tolong32(read(ANGLE_A))) * (360 * getFREQ() / 223000);
  return angle ;
}
double ADE7953::getANGLE_B(){
  double angle = double(uint16Tolong32(read(ANGLE_B))) * (360 * getFREQ() / 223000);
  return angle ;
}
//----------------------------------
double ADE7953::getPERIOD(){
  return double(read(Period)+1) / 223.753; //3.58 MHz/16= 223.750 kHz clock result in ms

}
double ADE7953::getFREQ(){
  return 1.0 / (getPERIOD()/1000);
}

//--------------------------------------------------------------------------------
double ADE7953::getP_A(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
  return uint24Tolong32(read(AWATT)) / 4862401.0 * k;
}
double ADE7953::getP_Arel(){
  return 100.0 / 4862401 * uint24Tolong32(read(AWATT));
}

double ADE7953::getQ_A(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
  return uint24Tolong32(read(AVAR)) / 4862401.0 * k;
}
double ADE7953::getQ_Arel(){
  return 100.0 / 4862401 * uint24Tolong32(read(AVAR));
}

double ADE7953::getS_A(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
  return uint24Tolong32(read(AVA)) / 4862401.0 * k;
}
double ADE7953::getS_Arel(){
  return 100.0 / 4862401 * uint24Tolong32(read(AVA));
}
//----------------------------------
double ADE7953::getP_B(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;
  return uint24Tolong32(read(BWATT)) / 4862401.0 * k;
}
double ADE7953::getP_Brel(){
  return 100.0 / 4862401 * uint24Tolong32(read(BWATT));
}

double ADE7953::getQ_B(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;
  return uint24Tolong32(read(BVAR)) / 4862401.0 * k;
}
double ADE7953::getQ_Brel(){
  return 100.0 / 4862401 * uint24Tolong32(read(BVAR));
}

double ADE7953::getS_B(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;
  return uint24Tolong32(read(BVA)) / 4862401.0 * k;
}
double ADE7953::getS_Brel(){
  return 100.0 / 4862401 * uint24Tolong32(read(BVA)); 
}

//----------------------------------

void ADE7953::updateEnergy(){
  long now = millis();
  if (now - lastMeasure_time > read(updateTimeEnergy)) {
    lastMeasure_time = now;

    int regGAIN[] = {AWGAIN, AVARGAIN, AVAGAIN, BWGAIN, BVARGAIN, BVAGAIN};
    double PN_A = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
    double PN_B = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;   
    double PN_AB[] = {PN_A, PN_A, PN_A, PN_B, PN_B, PN_B };
    int regEnergy[] = {AENERGYA, RENERGYA, APENERGYA, AENERGYB, RENERGYB, APENERGYB};
    //double Energy[] = {WA, WbA, WsA, WB, WbB, WsB};
    
    for (int i=0; i<6; i++){
      double t_rollOver = (1/206900.0 * 0x7FFFFF) / (double(read(regGAIN[i])) / 0x400000);
      double PN = PN_AB[i];
      double Wmax = PN * t_rollOver;
      double Wist = double(uint24Tolong32(read(regEnergy[i]))) / 0x7FFFFF * Wmax;
      
      //Serial.print("Wist:  ");Serial.println(Wist,6);
      //Serial.print("old:   ");Serial.println(energy[i],6);
      
      energy[i] = energy[i] + Wist;
      
      //Serial.print("new:   ");Serial.println(energy[i],6);
      //Serial.println("--------");
      

    }
    //Serial.println("-----------------------");

  }
}

double ADE7953::getW_A(){  
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
  return uint24Tolong32(read(AENERGYA)) / 4862401.0 * k  * 3600 ;
}
double ADE7953::getWb_A(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
  return uint24Tolong32(read(RENERGYA)) / 4862401.0 * k  * 3600 ;
}
double ADE7953::getWs_A(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IA)) * read(k_V) / 100 * read(k_IA) / 100;
  return uint24Tolong32(read(APENERGYA)) / 4862401.0 * k  * 3600 ;
}
//----------------------------------
double ADE7953::getW_B(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;
  return uint24Tolong32(read(AENERGYB)) / 4862401.0 * k  * 3600 ;
}
double ADE7953::getWb_B(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;
  return uint24Tolong32(read(RENERGYB)) / 4862401.0 * k  * 3600 ;
}
double ADE7953::getWs_B(){
  double k = getFullScaleInput(read(PGA_V)) * getFullScaleInput(read(PGA_IB)) * read(k_V) / 100 * read(k_IB) / 100;
  return uint24Tolong32(read(APENERGYB)) / 4862401.0 * k  * 3600 ;
}



//===============================================================================
//  read instantaneous values 
//===============================================================================
String ADE7953::getWave(uint16_t regNumber){  
  uint16_t k = 1;
  uint16_t PGA = 1;
  if (regNumber == V){
    k = k_V;
    PGA = PGA_V;
  } else
  if (regNumber == IA){
    k = k_IA;
    PGA = PGA_IA;
  } else
  if (regNumber == IB){
    k = k_IB;
    PGA = PGA_IB;
  }

  read(RSTIRQSTATA); //Clear IROs
  while (!readBit(RSTIRQSTATA,15)) {   //wait for IRQ V zeroCross
  }  
  delayMicroseconds(5300);  

  int sampleRate = read(SampleRate);  //in kHz
  unsigned int tsample = 1000000.0 / (sampleRate * 1000); //in µs
  int samples = read(Periods) * 20000 / tsample;
   
  //unsigned long avarage = 0;
  //unsigned long t0 = micros();
  for (int i=0; i<samples; i++){
    values[i] = read(regNumber);
    delayMicroseconds(tsample-106);
    //avarage = (avarage + (micros()-t0) ) / i+1.0;
    //Serial.println(avarage);
  }
  
  String wave = "";
  for (int i=0; i<samples; i++){
    char cTime[30] {""};
    char cValue[15] {""};
    dtostrf(0.000001* tsample * i, 1, 5, cTime);
    //dtostrf(0.000001* avarage * i, 1, 5, cTime);
    double val = getFullScaleInput(read(PGA))* sqrt(2) * uint24Tolong32(values[i]) / 6500000.0 * read(k) / 100;
    dtostrf(val, 1, 5, cValue);
    
    strcat(cTime, ",");
    strcat(cTime, cValue);

    if (callback != nullptr) callback(cTime, regNumber);
  } 

  
//ENDLESS with 320Hz  
/*  
  unsigned long t0 = micros();  
  double scale = getFullScaleInput(read(PGA))* sqrt(2)  / 6500000.0 * read(k) / 100;
  for (int i=0; i<samples; i++){
    
    double t = 0.000001 * (micros()- t0);
    double val = uint24Tolong32(read(regNumber)) * scale;
    
    char cTime[30] {""};
    char cValue[15] {""};
    dtostrf(t, 1, 5, cTime);
    dtostrf(val, 1, 5, cValue);
    
    strcat(cTime, ",");
    strcat(cTime, cValue);

    if (callback != nullptr) callback(cTime, regNumber);
  }  
*/  
  

  return "";
}

//===============================================================================
//  helpers 
//===============================================================================
//format double
String ADE7953::formatDouble(double value, int dec){
  char out[20];
  char str_temp[20];
  /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
  dtostrf(value, 1, dec, str_temp);
  sprintf(out,"%s", str_temp);    
  return out;
}

//get InputScale
double ADE7953::getFullScaleInput(int PGA){
  double scale = 0;
  if (PGA == 5){
     scale = 0.0227 / sqrt(2);
  }else{
    scale = 0.5 / pow(2,PGA) / sqrt(2);
  }
  return scale; 
}

//search register name
String ADE7953::getRegName(uint16_t regNumber){
  String Name = "NIL";
  for (auto element : reg){
    if (element.regAdr == regNumber){
      Name = element.regName;
      break;  
    }
  }
  return Name;  
}

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
  long int val = 0;

  if (str.indexOf(",") > 0) str = str.substring(0,str.indexOf(","));
  for (auto element : reg){
    if (element.regName == str){
      val = element.regAdr;   
    }
  }

  if (val == 0){
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
  }  
  return val;
}

//uint32_t to long int
long ADE7953::uint24Tolong32(uint32_t val){
  long tmp = val;
  if (tmp >= 0xFFFFFF/2) tmp = (0xFFFFFF - tmp +1) * -1;
  return tmp;  
}
//uint32_t to long int
long ADE7953::uint16Tolong32(uint16_t val){
  long tmp = val;
  if (tmp >= 0xFFFF/2) tmp = (0xFFFF - tmp +1) * -1;
  return tmp;  
}

//===============================================================================
//  xxxxxxxxx 
//===============================================================================

void ADE7953::Test(){
/*
  Serial.println("list changed registers");
  for (auto element : reg){
    if (element.changed){
      String line = element.regName  + " | " + String(element.regVal, HEX);
      Serial.println(line);   
    }
  }
*/

  

  for (auto element : reg){
    //Serial.print(element.BitSize);Serial.print(" | ");
    Serial.print(element.regName);Serial.print(" | ");
    //Serial.print(element.regAdr, HEX);Serial.print(" | ");
    Serial.print(element.regVal);Serial.println(" | ");
    //Serial.print(element.Signed);Serial.print(" | ");
    //Serial.print(element.RW);Serial.print(" | ");
    //Serial.println(element.changed);
  }
    Serial.println(""); 
    Serial.println(""); 

/*  for (auto element : reg){
    if (element.RW){
      String line = char(34) +  element.regName + char(34) + " : " + char(34)+char(34) + ",";
      
      Serial.println(line);   
    }
  }
  Serial.println(""); 
  Serial.println(""); 
*/
    
}


