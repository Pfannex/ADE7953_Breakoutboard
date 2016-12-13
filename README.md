# ADE7953 MQTT Wattmeter

Der ADE7953 wird über einen ESP8266-WLAN-Controller per I²C angesteuert.
Aktuell gibt es nur ein Breakoutboard mit Grundbeschaltung. 
Die Ankopplung der Leistungsmessgrößen erfolgt zu einem späteren Zeitpunkt.

### MQTT
Die externe Konfiguration des ADE7953 erfolgt über einen MQTT-Broker. 
Alle Topics beginnen mit dem über das Webinterface einstellbaren MQTT-Devicenamen.
Voreingestellt ist ESP8266_ in Verbindung mit der ESP spezifischen Seriennummer.
Z.B. ESP8266_1032096

Folgende Topics werden vom ESP8266 **subscribed**:

ESP8266_1032096/ 
* /ESP8266
  * /Control
    * /Reboot
* /ADE7953
  * /Control
    * /read
    * /write
    * /readBit
    * /writeBit
    * /init
    * /updateTime
    * /saveConfig
    * /setDefault
  * /getValues
    * /V_INST

Folgende Topics werden vom ESP8266 **published**:

ESP8266_1032096/ 
* /ADE7953
  * /Last_RW
    * /HEX
    * /BIN
    * /DEC
    * /Bit
    * /value
  * /values
    * /V_RMS
    * /IA_RMS
    * /IB_RMS
    * /V_INST

***
## ESP8266_1032096/ESP8266/Control/_Reboot_
Der ESP8266 führt einen Softreset durch.

## ESP8266_1032096/ADE7953/Control/_read_
Liest den Inhalt eines Registers des ADE7953.

Beispiele:   

| MQTT-payload | ESP8266 publish ESP8266_1032096/ADE7953/Last_RW/HEX (BIN, DEC)|
| :---         |          ---: |
| `0x281`   | 0x400000 (10000000000000000000000, 4194304| 
| git diff     | git diff       | 

### Webinterface











