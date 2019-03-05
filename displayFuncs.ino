void updateScreen(float tempSensor1, float tempSensor2, int fanMode) {
  /*
   * Here there will be functions to update screen and
   * print text with Air/Water temperatures and current fan-speed
   * 
   */
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  // DisplayMode 0 = Main screen
  // DisplayMode 1 = Temp Settings
  // DisplayMode 2 = Version and Author
  
  if (displayMode==0) {

  display.println("Water temp: ");
  display.setCursor(70,0);
  
  display.println(tempSensor1);
  display.setCursor(105,0);
  display.println("C");
  display.setCursor(0,12);
  display.println("Air temp: ");
  display.setCursor(70,12);
  display.println(tempSensor2);
  display.setCursor(105,12);
  display.println("C");
  
  display.setCursor(0,24);
  display.println("Fan speed: ");
  display.setCursor(70,24);
  display.println(fanGfx[fanMode]);
  display.setCursor(0,36);
  display.println("Target: ");
  display.setCursor(70,36);
  display.println(lowTemp);
  display.setCursor(0,48);
  display.println("Mode: ");
  display.setCursor(35,48);
  
 display.println(Modes[heatMode]); 
 
  }
  else if (displayMode==1) 
  {
  // displayMode 1 - Menu!
 
  display.setCursor(0,0);
    if (menuSelVal==0) { display.println("* Low Temp: "); }
  else { display.println("Low Temp: "); }
  display.setCursor(72,0);
  display.println(lowTemp);
  display.setCursor(0,11);
  
  if (menuSelVal==1) { display.println("* Mid Temp: "); }
  else { display.println("Mid Temp: "); }
  display.setCursor(72,11);
  display.println(midTemp);
  display.setCursor(0,22);
  
  if (menuSelVal==2) { display.println("* High Temp: "); }
  else { display.println("High Temp: "); }
  display.setCursor(72,22);
  display.println(highTemp);
  
  display.setCursor(0,33);
  
  if (menuSelVal==3) { display.println("* Adj Period: "); }
  else { display.println("Adj Period: "); }
  display.setCursor(80,33);
  display.println(maxiterations);
  display.setCursor(90,33);
  display.println(" sec");
  
  display.setCursor(0,44);
  
  if (menuSelVal==4 && settingsChanged == 1) { display.println("* Save"); }
  else if (menuSelVal != 4 && settingsChanged == 1) { display.println("Save "); }
  else if (menuSelVal == 4 && settingsChanged == 0) { menuSelVal++; }
  
  display.setCursor(0,55);
  
  if (menuSelVal==5) { display.println("* Exit"); }
  else { display.println("Exit "); }
  
  
  }
  else if (displayMode=2) {
    display.setCursor(0,0);
    display.println("Version: ");
    display.setCursor(50,0);
    display.println(version);
    display.setCursor(0,12);
    display.println("Author: Johan Bogg");
    display.setCursor(0,24);
    display.println("Contact: johan@bogg.nu");
    display.setCursor(0,36);
    display.println("Sel to Exit");
  }
  
  
  
  
   display.display();
   

 
}
