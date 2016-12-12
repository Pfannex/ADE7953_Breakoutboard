/******************************************************************************

  ProjectName: ADE7953-Test Sketch                ***** *****
  SubTitle   : ADE7953-WattMeter                 *     *     ************
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
ESP8266_Basic espClient;


void setup() {  
  Serial.begin(115200); 
  Serial.println("");
  
  espClient.start_WiFi_connections();
  espClient.run_I2C();
  espClient.ADE.init();
  //espClient.ADE.Test();
}  

void loop() {
  espClient.handle_connections(); 
  espClient.handle_Measurement();
}

/*ToDo
 * SAVE
 * LastRW aus Register
 * Topics aud json
 * Reading int/uint
 * element reading
 */



