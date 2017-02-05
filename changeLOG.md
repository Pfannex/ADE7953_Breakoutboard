#changeLOG
Stand: 05.02.2017 / 11:53h  
letzte Änderung: Pf@nne

- **Hardware**
  - 
  
- **Firmware**
  - Topic /getWave hinzugefügt, V_INST, IA_INST und IB_INST werden nacheinader published
  - SoftRegister Period und SampleRate zur Steuerung der INST-Werte hinzugefügt
  - INST-Routinen überarbeitet, 1000 Samples mit 7kHz möglich
  - INST mit max 4kHz, Samples auf max. 500 begrenzt
  - INST nach dem publish der INST-Values erfolgt ein INSTready publish zum Refresh des SVG-Plots
  - Energy /resetEnergy mit Vorgabewert

- **FHEM**
  - dummys für INST-Werte ergänzt
  - Pfanne_fhem.cfg abgelegt
  - INST funktionalitäten erweitert
  
