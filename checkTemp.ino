void checkTemp(float tempSensor1, float tempSensor2, float lowTemp) {
  if (heatMode == 1) {
    // Winter mode: run fan when water is warmer than air
    if (tempSensor1 > tempSensor2 + 1) {
      if      (tempSensor1 <= lowTemp)  { setFanSpeed(0); }
      else if (tempSensor1 < midTemp)   { setFanSpeed(1); }
      else if (tempSensor1 < highTemp)  { setFanSpeed(2); }
      else                              { setFanSpeed(3); }
    } else {
      setFanSpeed(0);
    }
  }
  else if (heatMode == 0) {
    // Summer mode: run fan when air is warmer than water
    if (tempSensor1 > tempSensor2 + 1) {
      setFanSpeed(0);
    } else if (tempSensor1 < tempSensor2) {
      int airwaterdiff = tempSensor2 - tempSensor1;
      if (airwaterdiff > 5) { setFanSpeed(2); }
      else                  { setFanSpeed(1); }
    } else {
      setFanSpeed(0);
    }
  }
  // heatMode == 2 (Manual): fan speed set directly by buttons, no automatic adjustment
}
