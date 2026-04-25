void SaveSettings() {
  EEPROM.update(LOWTMP_EEPROM, (int)lowTemp);
  EEPROM.update(MIDTMP_EEPROM, (int)midTemp);
  EEPROM.update(HIGHTMP_EEPROM, (int)highTemp);
  EEPROMWritelong(MAXITER_EEPROM, maxiterations);
  settingsChanged = 0;
}
