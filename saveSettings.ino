void SaveSettings() {
  EEPROM.write(LOWTMP_EEPROM, lowTemp);
  EEPROM.write(MIDTMP_EEPROM, midTemp);
  EEPROM.write(HIGHTMP_EEPROM, highTemp);
  EEPROMWritelong(MAXITER_EEPROM, maxiterations);
  settingsChanged=0;
  }
