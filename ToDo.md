#ToDo
Stand: 29.01.2017 / 19:22h  
letzte Änderung: Pf@nne

- **Hardware**
  - ~~CT-Test~~ - 20.01.2017
  - Ankopplung 230VAC
  
- **Firmware**
  - MQTT max.150 Samples? jsonBuffer?
  - Topic resetEnergy Samples, kHz
  - Frequenz SoftRegister für GAIN
  - Kalibrierungsfunktion in FW implementieren
  - WiKi Kalibrierungshinweis GAIN = 0x400000
  - NTP wird viel zu häufig abgefragt - beim Start und jede Stunde einmal genügt

- **FHEM**
  - Skalierung Plott in V/A nicht mV/mA
  - Hübsch machen... :-)
  - ToggleButton für die Umschaltung der MQTT-UpdateTime. "Normal" 60 Sekunden oder mehr. "Betrachten" 1 Sekunde
  
***
##Themen:
```diff
+ Pf@nne
- Boris
```
  
###NTP
```diff
- NTP wird viel zu häufig abgefragt - beim Start und jede Stunde einmal genügt
+ Die UpdateTime ist an die MQTT-Update-Time angekoppelt. Im "normalen" Betrieb werden die Messwerte vielleicht 
+ einmal pro Minute published, da fällt dich neben den zig MQTT-Paketen das NTP-Paket nic´ht ins Gewicht. 
+ Eine Änderung würde die Implementaion einer "SoftClock" nach sich ziehen. 
```
  
  
