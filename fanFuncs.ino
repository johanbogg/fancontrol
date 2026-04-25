void setFanSpeed(int reqSpeed) {
  if (reqSpeed == fanMode) return;

  // Turn all relays off first, then activate the requested speed
  digitalWrite(LOW_SPDPIN,  LOW);
  digitalWrite(MID_SPDPIN,  LOW);
  digitalWrite(HIGH_SPDPIN, LOW);
  delay(250);

  if      (reqSpeed == 1) { digitalWrite(LOW_SPDPIN,  HIGH); }
  else if (reqSpeed == 2) { digitalWrite(MID_SPDPIN,  HIGH); }
  else if (reqSpeed == 3) { digitalWrite(HIGH_SPDPIN, HIGH); }

  fanMode = reqSpeed;
}
