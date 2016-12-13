/******************************************************************************

  ProjectName: ESP8266 Basic template             ***** *****
  SubTitle   : Data definitions                  *     *     ************
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
#include <Arduino.h>
#include "ESP8266_Basic_data.h"

Topics::Topics(){ 

//suscibe
  sub.E1.count = sub_e1;
  sub.E2.count = sub_e2;
  sub.E3.count = sub_e3;
  
  sub.E1.item[0] = "WiFiConfig";
  sub.E2.item[0][0] = "WEBserver";
  sub.E3.item[0][0][0] = "Username";
  sub.E3.item[0][0][1] = "Password";
  sub.E2.item[0][1] = "Accesspoint";
  sub.E3.item[0][1][0] = "SSID";
  sub.E3.item[0][1][1] = "Password";
  sub.E2.item[0][2] = "WiFi";
  sub.E3.item[0][2][0] = "SSID";
  sub.E3.item[0][2][1] = "Password";
  sub.E3.item[0][2][2] = "IP";
  sub.E2.item[0][3] = "MQTT";
  sub.E3.item[0][3][0] = "Server";
  sub.E3.item[0][3][1] = "Port";
  sub.E3.item[0][3][2] = "Status";
  sub.E2.item[0][4] = "UpdateServer";
  sub.E3.item[0][4][0] = "Server";
  sub.E3.item[0][4][1] = "FilePath";
    
  sub.E1.item[1] = "ESP8266";
  sub.E2.item[1][0] = "Control";
  sub.E3.item[1][0][0] = "Reboot";

  sub.E1.item[2] = "ADE7953";
  sub.E2.item[2][0] = "Control";
  sub.E3.item[2][0][1] = "read";
  sub.E3.item[2][0][2] = "write";
  sub.E3.item[2][0][3] = "readBit";
  sub.E3.item[2][0][4] = "writeBit";
  sub.E3.item[2][0][5] = "init";
  sub.E3.item[2][0][6] = "updateTime";
  sub.E3.item[2][0][7] = "saveConfig";
  sub.E3.item[2][0][8] = "setDefault";
  sub.E2.item[2][1] = "getValues";
  sub.E3.item[2][1][0] = "V_INST";

  sub.E1.item[3] = "File";
  sub.E2.item[3][0] = "Read";
  sub.E3.item[3][0][0] = "Field_01";
  sub.E3.item[3][0][1] = "Field_02";
  sub.E2.item[3][1] = "Write";
  sub.E3.item[3][1][0] = "Field_01";
  sub.E3.item[3][1][1] = "Field_02";

//publish
  pub.E1.count = pub_e1;
  pub.E2.count = pub_e2;
  pub.E3.count = pub_e3;
  
  pub.E1.item[0] = "WiFiConfig";
  pub.E2.item[0][0] = "WEBserver";
  pub.E3.item[0][0][0] = "Username";
  pub.E3.item[0][0][1] = "Password";
  pub.E2.item[0][1] = "Accesspoint";
  pub.E3.item[0][1][0] = "SSID";
  pub.E3.item[0][1][1] = "Password";
  pub.E2.item[0][2] = "WiFi";
  pub.E3.item[0][2][0] = "SSID";
  pub.E3.item[0][2][1] = "Password";
  pub.E3.item[0][2][2] = "IP";
  pub.E2.item[0][3] = "MQTT";
  pub.E3.item[0][3][0] = "Server";
  pub.E3.item[0][3][1] = "Port";
  pub.E3.item[0][3][2] = "Status";
  pub.E2.item[0][4] = "UpdateServer";
  pub.E3.item[0][4][0] = "Server";
  pub.E3.item[0][4][1] = "FilePath";
  
  pub.E1.item[1] = "Control";
  pub.E2.item[1][0] = "Status";
  pub.E3.item[1][0][0] = "WiFi";
  pub.E3.item[1][0][1] = "MQTT";
  pub.E3.item[1][0][2] = "updateFirmware";

  pub.E1.item[2] = "ADE7953";
  pub.E2.item[2][0] = "Last_RW";
  pub.E3.item[2][0][0] = "HEX";
  pub.E3.item[2][0][1] = "BIN";
  pub.E3.item[2][0][2] = "DEC";
  pub.E3.item[2][0][3] = "Bit";
  pub.E3.item[2][0][4] = "value";
  pub.E2.item[2][1] = "values";
  pub.E3.item[2][1][0] = "V_RMS";
  pub.E3.item[2][1][1] = "IA_RMS";
  pub.E3.item[2][1][2] = "IB_RMS";
  pub.E3.item[2][1][3] = "V_INST";




}
