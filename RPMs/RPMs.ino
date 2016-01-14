const int hallPin = 8;        // Pin connected to Hall sensor



int getRpm(){
  
  unsigned long startTime;
  unsigned long deltaMillis;
  unsigned int rpm;
  int hallReading;
  int priorHallReading = LOW;
  bool changed;
  bool normalOps = true;
  
  startTime = millis();
  
  // Count ten revolutions
  for (int i = 0; i < 10; i++){

    changed = false;
    
    while (normalOps && !changed){
      hallReading = digitalRead(hallPin);
  
      // Might need to debounce
      if (hallReading != priorHallReading){
        changed = true;
      }
  
      priorHallReading = hallReading;

      // Prevent system from hanging if taking too long
      if((millis() - startTime) > 1000){
        normalOps = false;
      }
    }

    // Taking too long to get a reading
    if (!normalOps){
      return -1;
    }
  }

  // Milliseconds for 10 revolutions
  deltaMillis = millis() - startTime;

  float oneRev = 10 / deltaMillis;

  float fltRpm = 60000 / oneRev;

  rpm = (int) fltRpm;  

  return rpm;
}



int getMillisBetweenPulses(){
  unsigned long startTime;
  unsigned long deltaMillis;
  unsigned int rpm;
  int hallReading = HIGH;
  int priorHallReading = HIGH;
  bool changed = false;
  bool normalOps = true;

  startTime = millis();

  while (!changed){
    
  
    hallReading = digitalRead(hallPin);

    if(hallReading != priorHallReading){
  
      String sensorState = String(hallReading);
      Serial.print("Magnet change detected: ");
      Serial.println(sensorState);
      
      deltaMillis = millis() - startTime;
      String twine = String(deltaMillis);
      Serial.print("Milliseconds between change: ");
      Serial.println(twine);

      changed = true;
      
    }
  }

  
  return 303;



  
}


void setup() {
  Serial.begin(9600);
  Serial.println("Begin setup");
  
  pinMode(hallPin, INPUT);

}

void loop() {

  delay(500);
  int rpm = getMillisBetweenPulses();
  String rpms = String(rpm);
  Serial.print("RPMS detected: ");
  Serial.println(rpms);
  

}
