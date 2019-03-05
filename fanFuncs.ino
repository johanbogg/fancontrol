

void setFanSpeed(int reqSpeed) {
  if ( reqSpeed == fanMode) {} // If new speed is same as current speed, do nothing
  else {  // Else, if current and new speed aren't the same, turn all pins to low and set the correct pin to high.
    digitalWrite(LOW_SPDPIN, LOW); 
    digitalWrite(MID_SPDPIN, LOW); 
    digitalWrite(HIGH_SPDPIN, LOW);
    delay(480);
    if (reqSpeed == 0) { }
  else if (reqSpeed == 1) { digitalWrite(LOW_SPDPIN, HIGH); }
    
  else if (reqSpeed == 2) {   digitalWrite(MID_SPDPIN, HIGH); }
  
  else if (reqSpeed == 3) { digitalWrite(HIGH_SPDPIN, HIGH);  }
  
  else { }
  
  fanMode=reqSpeed;
}
}
