#ToDo
Stand: 23.02.2017 / 20:30h  
letzte Ã„nderung: Pf@nne

- **Hardware**
  - ~~CT-Test~~ - 20.01.2017
  - Ankopplung 230VAC
  
- **Firmware**
  - ~~MQTT max.150 Samples? jsonBuffer?~~ - 03.02.2017 - 1000 Samples @7kHz
  - ~~Begrenzung der SampleRate und der maximalen Samples~~ - 05.02.2017
  - mehrere Samples in einem 256Byte Frame pushen
  - ~~Topic resetEnergy REG, Value~~ 05.02.2017
  - ~~Topic /getValues/IA_INST Samples, kHz~~ - 05.02.2017 in SoftRegister implementiert
  - ~~Frequenz SoftRegister fÃ¼r GAIN~~ - 05.02.2017 SoftRegister PERIODGAIN hinzugefÃ¼gt (223.75 + (read(PERIODGAIN)/1000)) obwohl die Korrektur Datasheet 223kHz -> 223.75kHz (3.58 MHz/16= 223.750 kHz clock) schon reichen wÃ¼rde
  - Kalibrierungsfunktion in FW implementieren
  - ~~WiKi Kalibrierungshinweis GAIN = 0x400000~~ - 30.01.2017
  - NTP wird viel zu hÃ¤ufig abgefragt - beim Start und jede Stunde einmal genÃ¼gt
  - ~~Topic getWave hinzufÃ¼gen alle drei Waves werden gestaffelt published~~ - 02.02.2017
  - ~~Sinnvolle Default-Werte fÃ¼r Samples und Periods mit setDefault setzen~~ wird im SoftRegister gesetzt
  - ~~ESP8266/Control/Relay publish/subscribe~~ - 15.02.17 RÃ¼ckmeldestruktur in FHEM geht auch!
  - SoftClock
  - ~~getState implementieren~~ 23.02.17 
   

- **FHEM**
  - ~~Skalierung Plott in V/A nicht mV/mA~~ 30.01.2017 - FW fehler
  - HÃ¼bsch machen... :-)  z.B. ReadingsGroups
  - ToggleButton fÃ¼r die Umschaltung der MQTT-UpdateTime. "Normal" 60 Sekunden oder mehr. "Betrachten" 1 Sekunde
  - ~~ermÃ¶glichen, auch Samples im Format t1,x1;t2,x2;... im logProxyFile2xyPlot zu verarbeiten~~ 11.02.2017
  - ~~getState des Relais nach einem FHEM-Start abfragen~~ 23.02.17
  
***
##Themen:
```diff
+ Pf@nne
- Boris
```
  
###NTP
```diff
- NTP wird viel zu hÃ¤ufig abgefragt - beim Start und jede Stunde einmal genÃ¼gt
+ Die UpdateTime ist an die MQTT-Update-Time angekoppelt. Im "normalen" Betrieb werden die Messwerte 
+ vielleicht einmal pro Minute published, da fÃ¤llt neben den zig MQTT-Paketen das NTP-Paket nicht 
+ ins Gewicht. Eine Ã„nderung wÃ¼rde die Implementaion einer "SoftClock" nach sich ziehen. 
+ SoftClock wird implementiert!
```
