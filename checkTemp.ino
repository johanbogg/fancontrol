void checkTemp(float tempSensor1, float tempSensor2, float lowTemp){
    if ( heatMode == 1) {
    
    if ( tempSensor1 > tempSensor2+1 ) { 
    
    if ( tempSensor1 <= lowTemp ){ setFanSpeed(0);  }
    else if ( tempSensor1 > lowTemp) {
          if ( tempSensor1 < midTemp ) { setFanSpeed(1); }
          else if ( tempSensor1 < highTemp ) { setFanSpeed(2); }
          else { setFanSpeed(3); }
          }
    else { setFanSpeed(0);}
    }
 
    else { setFanSpeed(0); }
    }
    else if ( heatMode == 0) {  // SUMMER MODE CODE HERE! 
      if ( tempSensor1 > tempSensor2+1) {
        setFanSpeed(0);
      }
      else if ( tempSensor1 < tempSensor2  ) {
        int airwaterdiff=tempSensor2-tempSensor1;
        if ( airwaterdiff > 5) {
          setFanSpeed(2);
        }
           
        
      }
     else { setFanSpeed(0); }
    }
    // Check if heatMode is manual (2)!
    else if (heatMode==2) {      } 
}
