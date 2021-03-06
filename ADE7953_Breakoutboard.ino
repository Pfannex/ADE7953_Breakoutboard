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

  //int dcount= 0;

void tick(void *pArg) {
  espClient.timerCallback();
}


void setup() {  
  Serial.begin(115200); 
  Serial.println("");

  espClient.setup_Timer();
  espClient.setup_Peripherals();
  espClient.start_WiFi_connections();
  espClient.run_I2C();
  espClient.ADE.init();
  //espClient.ADE.Test();


} 

//void d(char *p) {
  //Serial.print(p);
  //if(!(dcount++ % 50)) Serial.println(); }
 

void loop() {
  //d("C");
  espClient.handle_connections();
  //d("M");
  espClient.handle_Measurement();
  //d("P");
  espClient.handle_Peripherals();

/*  espClient.handle_connections(); 
  espClient.handle_Measurement();
  espClient.handle_Peripherals();*/
}

/*ToDo
 * readBit / writeBit by Name
 * DONE -  write only changed json, at MQTT command 
 * DONE - SAVE
 * LastRW aus Register
 * Topics auf json
 * DONE Reading int/uint
 * DONE element reading
 * FS Abfrage ob Feld vorhanden, sonst ggf. format
 * write register from MQTT by Name
 * k-Faktor
 */


