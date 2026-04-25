void chkBtns() {

  selBtnstate = digitalRead(SEL_BTN);
  upBtnstate  = digitalRead(UP_BTN);
  dwnBtnstate = digitalRead(DWN_BTN);

  // SEL button
  if (selBtnstate == HIGH && upBtnstate == LOW && dwnBtnstate == LOW) {
    if (oldselBtnstate == 0) {
      oldselBtnstate = 1;
      if (displayMode == 0) {
        if (heatMode == 0)      { heatMode = 1; checkTemp(tempSensor1, tempSensor2, lowTemp); }
        else if (heatMode == 1) { heatMode = 2; setFanSpeed(0); }
        else if (heatMode == 2) { heatMode = 0; checkTemp(tempSensor1, tempSensor2, lowTemp); }
      }
      else if (displayMode == 1) {
        if (menuSelVal >= 5) { menuSelVal = 0; }
        else { menuSelVal++; }
        // Skip Save when nothing has changed
        if (menuSelVal == 4 && settingsChanged == 0) { menuSelVal = 5; }
      }
      else if (displayMode == 2) { displayMode = 0; }
    }
  }

  // UP button
  if (upBtnstate == HIGH && selBtnstate == LOW && dwnBtnstate == LOW) {
    if (displayMode == 0 && heatMode == 2) {
      if (oldupBtnstate == 0) {
        oldupBtnstate = 1;
        if (fanMode <= 2) { setFanSpeed(fanMode + 1); }
      }
    }
    if (displayMode == 1) {
      if (oldupBtnstate == 0) {
        oldupBtnstate = 1;
        if      (menuSelVal == 0) { lowTemp++;      settingsChanged = 1; }
        else if (menuSelVal == 1) { midTemp++;      settingsChanged = 1; }
        else if (menuSelVal == 2) { highTemp++;     settingsChanged = 1; }
        else if (menuSelVal == 3) { maxiterations++; settingsChanged = 1; }
        else if (menuSelVal == 4) { SaveSettings(); }
        else if (menuSelVal == 5) { displayMode = 0; }
      }
    }
  }

  // DOWN button
  if (dwnBtnstate == HIGH && upBtnstate == LOW && selBtnstate == LOW) {
    if (displayMode == 0 && heatMode == 2) {
      if (olddwnBtnstate == 0) {
        olddwnBtnstate = 1;
        if (fanMode >= 1) { setFanSpeed(fanMode - 1); }
      }
    }
    if (displayMode == 1) {
      if (olddwnBtnstate == 0) {
        olddwnBtnstate = 1;
        if      (menuSelVal == 0) { lowTemp--;      settingsChanged = 1; }
        else if (menuSelVal == 1) { midTemp--;      settingsChanged = 1; }
        else if (menuSelVal == 2) { highTemp--;     settingsChanged = 1; }
        else if (menuSelVal == 3) { maxiterations--; settingsChanged = 1; }
        else if (menuSelVal == 4) { SaveSettings(); }
        else if (menuSelVal == 5) { displayMode = 0; }
      }
    }
  }

  // UP + SEL: toggle menu
  if (upBtnstate == HIGH && selBtnstate == HIGH && dwnBtnstate == LOW) {
    if (oldselBtnstate == 0 || oldupBtnstate == 0) {
      oldupBtnstate  = 1;
      oldselBtnstate = 1;
      displayMode = (displayMode == 0) ? 1 : 0;
    }
  }

  // UP + DWN: show version screen
  if (upBtnstate == HIGH && dwnBtnstate == HIGH && selBtnstate == LOW) {
    if (olddwnBtnstate == 0 || oldupBtnstate == 0) {
      olddwnBtnstate = 1;
      oldupBtnstate  = 1;
      if (displayMode == 0) { displayMode = 2; }
    }
  }

  if (dwnBtnstate == LOW) { olddwnBtnstate = 0; }
  if (selBtnstate == LOW) { oldselBtnstate = 0; }
  if (upBtnstate  == LOW) { oldupBtnstate  = 0; }
}
