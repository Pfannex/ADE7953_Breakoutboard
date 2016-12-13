# ADE7953 MQTT Wattmeter

Der ADE7953 wird über einen ESP8266-WLAN-Controller per I²C angesteuert.
Aktuell gibt es nur ein Breakoutboard mit Grundbeschaltung. 
Die Ankopplung der Leistungsmessgrößen erfolgt zu einem späteren Zeitpunkt.

Die externe Konfiguration des ADE7953 erfolgt über einen MQTT-Broker.
Folgende Topics sind bisher umgesetzt:

* ESP8266
  * Control
    * Reboot
* ADE7953
  * Control
    * read
    * write
    * readBit
    * writeBit
    * init
    * updateTime
    * saveConfig
    * setDefault
  * getValues
    * V_INST


