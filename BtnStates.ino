void chkBtns() {
  
  selBtnstate=digitalRead(SEL_BTN);
  upBtnstate=digitalRead(UP_BTN);
  dwnBtnstate=digitalRead(DWN_BTN);

// check SelBtn
  if (selBtnstate == HIGH && upBtnstate == LOW && dwnBtnstate == LOW) {

    if (oldselBtnstate == 1) { oldselBtnstate = 1;}
    else { 
      oldselBtnstate = 1; 
      if (displayMode == 0) {      
      if (heatMode == 0) { heatMode=1; checkTemp(tempSensor1,tempSensor2,lowTemp);}
      else if (heatMode == 1) { heatMode=2; setFanSpeed(0);}
      else if (heatMode == 2) { heatMode=0; checkTemp(tempSensor1,tempSensor2,lowTemp);}
      }
      else if (displayMode == 1) {
        if (menuSelVal >= 5) { menuSelVal=0; }
        else { menuSelVal++; }
        }
      else if (displayMode == 2) { displayMode=0; }
    }
    }
    
// check UpBtn
   if (upBtnstate == HIGH && dwnBtnstate == LOW && dwnBtnstate == LOW) {

    if (displayMode == 0 && heatMode == 2) {
if (olddwnBtnstate == 1) {}
      else {
      if ( fanMode <= 2 ) { fanMode++; setFanSpeed(fanMode); }
      olddwnBtnstate = 1;
      }
      }
   if (displayMode == 1) {
    if (oldupBtnstate == 1) { oldupBtnstate = 1;}
    else { 
      oldupBtnstate = 1; 
      if (menuSelVal==0) {
      lowTemp++;
      settingsChanged=1;
      }
      else if (menuSelVal==1) {
      midTemp++;
      settingsChanged=1;
      }
      else if (menuSelVal==2) {
      highTemp++;
      settingsChanged=1;
      }
      else if (menuSelVal==3) {
      maxiterations++;
      settingsChanged=1;
      }
      else if (menuSelVal==4 && settingsChanged == 1) {
      Serial.print("SAVING");
      SaveSettings();
      }
      else if (menuSelVal==5) {
      displayMode=0;
      }
      }
         }
   }
   
   
// check DwnBtn

   if (dwnBtnstate == HIGH && upBtnstate == LOW && selBtnstate == LOW) {
    if (displayMode == 0 && heatMode == 2) { 
      if (olddwnBtnstate == 1) {}
      else {
      if ( fanMode >= 1 ) { fanMode--; setFanSpeed(fanMode); }
      olddwnBtnstate = 1;
      }
      }
    if (displayMode == 1) {
    if (olddwnBtnstate == 1) { olddwnBtnstate = 1;}
    else { 
      olddwnBtnstate = 1; 
      if (menuSelVal==0) {
      lowTemp--;
      settingsChanged=1;
      }
      else if (menuSelVal==1) {
      midTemp--;
      
      settingsChanged=1;
      }
      else if (menuSelVal==2) {
      highTemp--;
      settingsChanged=1;
      }
      else if (menuSelVal==3) {
      maxiterations--;
      settingsChanged=1;
      }
      else if (menuSelVal==4 && settingsChanged == 1) {
      Serial.print("SAVING");
      SaveSettings();
      }
      else if (menuSelVal==5) {
      displayMode=0;
      }
      }
         }
      
    }
// check if upBtn and sel is pressed at the same time:
  
  if (upBtnstate == HIGH && selBtnstate == HIGH && dwnBtnstate == LOW) {
    
    if (oldselBtnstate==1 && oldupBtnstate==1) { }
    else if (displayMode==0) {
    Serial.print("ENTERING MENU!");
    displayMode=1;
    oldupBtnstate = 1;
    oldselBtnstate = 1;
    }
    else if (displayMode==1) {
      displayMode=0;
      oldupBtnstate = 1;
      oldselBtnstate = 1;
    }
    
  }
  if (upBtnstate == HIGH && selBtnstate == LOW && dwnBtnstate == HIGH) { 
    if (olddwnBtnstate == 1 && oldupBtnstate == 1) {    }
    else if ( displayMode == 0) { 
      Serial.print("VERSION AND AUTHOR");
      displayMode=2;
      olddwnBtnstate = 1;
      oldupBtnstate = 1;
      }
    } 
  
    if (dwnBtnstate == LOW) { olddwnBtnstate = 0; }
    if (selBtnstate == LOW) { oldselBtnstate = 0; }
    if (upBtnstate == LOW) { oldupBtnstate = 0; } 
  
  }
