#ToDo
Stand: 30.01.2017 / 20:27h  
letzte Änderung: Pf@nne

- **Hardware**
  - ~~CT-Test~~ - 20.01.2017
  - Ankopplung 230VAC
  
- **Firmware**
  - ~~MQTT max.150 Samples? jsonBuffer?~~ - 30.01.2017 - 240 Samples 80ms/3kHz
  - Topic resetEnergy REG, Value
  - Topic /getValues/IA_INST Samples, kHz
  - Frequenz SoftRegister für GAIN
  - Kalibrierungsfunktion in FW implementieren
  - ~~WiKi Kalibrierungshinweis GAIN = 0x400000~~ - 30.01.2017
  - NTP wird viel zu häufig abgefragt - beim Start und jede Stunde einmal genügt
  - Topic getWave hinzufügen alle drei Waves werden gestaffelt published

- **FHEM**
  - ~~Skalierung Plott in V/A nicht mV/mA~~ 30.01.2017 - FW fehler
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
+ Die UpdateTime ist an die MQTT-Update-Time angekoppelt. Im "normalen" Betrieb werden die Messwerte 
+ vielleicht einmal pro Minute published, da fällt neben den zig MQTT-Paketen das NTP-Paket nicht 
+ ins Gewicht. Eine Änderung würde die Implementaion einer "SoftClock" nach sich ziehen. 
```
  
  
