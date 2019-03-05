void updateSerial(float tempSensor1, float tempSensor2, int fanMode) {
  Serial.write(27);       // ESC command
  Serial.print("[2J");    // clear screen command
  Serial.write(27);
  Serial.print("[H");     // cursor to home command
if ( displayMode == 0) {

 Serial.print("\n\rSensor 1 (Water): ");
 Serial.print(tempSensor1);
 Serial.print("\n\rSensor 2 (Air): ");
 Serial.print(tempSensor2);
 Serial.print("\n\rTarget temperature: ");
 Serial.print(lowTemp);
 Serial.print("\n\rIteration: ");
 Serial.print(iterations);
 Serial.print("\n\rCurrent Fan speed: ");
 Serial.print(fanGfx[fanMode]);
 Serial.print("\n\rHeat Mode: ");
 Serial.print(Modes[heatMode]);
}
else if (displayMode == 1 ) {
   
    if (menuSelVal==0) { Serial.print("\n\r* Low Temp: "); }
  else { Serial.print("\n\rLow Temp: "); }
  Serial.print(lowTemp);
  
  if (menuSelVal==1) { Serial.print("\n\r* Mid Temp: "); }
  else { Serial.print("\n\rMid Temp: "); }
  Serial.print(midTemp);
  
  if (menuSelVal==2) { Serial.print("\n\r* High Temp: "); }
  else { Serial.print("\n\rHigh Temp: "); }
  Serial.print(highTemp);
  
  
  if (menuSelVal==3) { Serial.print("\n\r* Adj Period: "); }
  else { Serial.print("\n\rAdj Period: "); }
  Serial.print(maxiterations);
  Serial.print("\n\r sec");
  
  if (menuSelVal==4 && settingsChanged == 1) { Serial.print("\n\r* Save"); }
  else if (menuSelVal != 4 && settingsChanged == 1) { Serial.print("\n\rSave "); }
  else if (menuSelVal == 4 && settingsChanged == 0) { menuSelVal++; }
  
  if (menuSelVal==5) { Serial.print("\n\r* Exit"); }
  else { Serial.print("\n\rExit "); }
  
  
  }

else if (displayMode == 2) {
  
    Serial.print("\n\rVersion: ");
    Serial.print(version);
    Serial.print("\n\rAuthor: Johan Bogg");
    Serial.print("\n\rContact: johan@bogg.nu");
    Serial.print("\n\rSel to Exit");
  
  }
  
}
