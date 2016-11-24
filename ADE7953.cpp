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
#include "ADE7953.h"

ADE7953::ADE7953(){
}

void ADE7953::Test(){
 
  Serial.println("startTest");

  uint8_t ret;
  Wire.beginTransmission(0x38); // start transmission to device 
  Wire.write(0x00); // sends register address to read from
  Wire.write(0x04); // sends register address to read from
  Serial.print("write 0x004 | ");Serial.println("0xAB");
  Wire.write(0xAB); // sends register address to read from
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(0x38); // start transmission to device 
  Wire.write(0x00); // sends register address to read from
  Wire.write(0x04); // sends register address to read from
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(0x38); // start transmission to device 
  Wire.requestFrom(0x38, 1);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  Wire.endTransmission(); // end transmission

  Serial.print("read  0x004 | 0x");Serial.println(ret, HEX);


  Wire.beginTransmission(0x38); // start transmission to device 
  Wire.write(0x02); // sends register address to read from
  Wire.write(0x00); // sends register address to read from
  Serial.print("write 0x200 | ");Serial.println("0xABCDEF");
  Wire.write(0xAB); // sends register address to read from
  Wire.write(0xCD); // sends register address to read from
  Wire.write(0xEF); // sends register address to read from
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(0x38); // start transmission to device 
  Wire.write(0x02); // sends register address to read from
  Wire.write(0x00); // sends register address to read from
  Wire.endTransmission(); // end transmission
  
  Wire.beginTransmission(0x38); // start transmission to device 
  Wire.requestFrom(0x38, 3);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  Serial.print("read  0x200 | 0x");Serial.println(ret, HEX);
  ret = Wire.read(); // receive DATA
  Serial.print("read  0x200 | 0x");Serial.println(ret, HEX);
  ret = Wire.read(); // receive DATA
  Serial.print("read  0x200 | 0x");Serial.println(ret, HEX);
  Wire.endTransmission(); // end transmission


  
}


