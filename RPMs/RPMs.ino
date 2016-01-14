const int hallPin = 8;        // Pin connected to Hall sensor



int getRpm(){
  
  unsigned long startTime;
  unsigned long deltaMillis;
  int rpm = -2;
  int hallReading = HIGH;
  int priorHallReading = HIGH;
  bool changed = false;
  bool normalOps = true;

  startTime = millis();
  
  // Count ten revolutions, only counting the transitions from LOW to HIGH.  Tested up to 2600 RPMs
  for (int i = 0; i < 10; i++){

    changed = false;
    
    while (normalOps && !changed){
      hallReading = digitalRead(hallPin);
  
      if (hallReading == HIGH && priorHallReading == LOW){
        changed = true;
      }
  
      priorHallReading = hallReading;

      int testDeltaMillis = millis() - startTime;

      // Prevent system from hanging if taking too long
      if(testDeltaMillis > 2000){
        normalOps = false;
        String strTestDeltaMillis = String(testDeltaMillis);
        Serial.print("Took too long.  Milliseconds between change: ");
        Serial.println(strTestDeltaMillis);
      }
    }

    // Taking too long to get a reading
    if (!normalOps){
      Serial.print("Abnormal Operations");
      return -1;
    }

    String sensorState = String(hallReading);
  }

  // Milliseconds for 10 revolutions
  deltaMillis = millis() - startTime;
  String strDeltaMillis = String(deltaMillis);
  Serial.print("Milliseconds for 10 revolutions: ");
  Serial.println(strDeltaMillis);


  float oneRev = deltaMillis / 10;

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

void testPerformance(){
  unsigned int currentMillis;
  unsigned int deltaMillis;
  unsigned int startMillis;
  unsigned int fetchReuse;
  unsigned int fetched;
  int counter = 0;


  
  Serial.println("\n\n **** Testing Performance ****");


  // Fetch millis() and initialize new int:  14ms - 16ms
  startMillis = millis();
  for (int i = 0; i < 10000; i++){
    unsigned int fetchNew = millis();
    fetched = fetchNew + 1;
  }
  deltaMillis = millis() - startMillis;
  Serial.print("\n**** fetching 10k new millis took fetchNew: ");
  Serial.print(String(deltaMillis));
  Serial.print(";   fetched = ");
  Serial.println(String(fetched));


  // Fetch millis() and reuse int:  14ms - 16ms
  startMillis = millis();
  for (int i = 0; i < 10000; i++){
    fetchReuse = millis();
    fetched = fetchReuse + 1;
  }
  deltaMillis = millis() - startMillis;
  Serial.print("\n**** fetching 10k reused millis took: ");
  Serial.print(String(deltaMillis));
  Serial.print(";   fetched = ");
  Serial.println(String(fetched));


  // Add up to 10k and reuse int:  zero
  counter = 0;
  int counted = 0;
  int addend = 0;
  startMillis = millis();
  for (int i = 0; i < 10000; i++){
    addend = addend + 1;
    counter = 1 + addend;
  }
  deltaMillis = millis() - startMillis;
  Serial.print("\n**** Counting to 10k took: ");
  Serial.print(String(deltaMillis));
  Serial.print(";   counter = ");
  Serial.println(String(counter));


  // Add up to 10k and initialize new int:  zero
  counter = 0;
  startMillis = millis();
  for (int i = 0; i < 10000; i++){
    int newAddend = counter + 1;
    counter = 1 + newAddend;
  }
  deltaMillis = millis() - startMillis;
  Serial.print("\n**** Counting to 10k with initialization took addend: ");
  Serial.print(String(deltaMillis));
  Serial.print(";   counter = ");
  Serial.println(String(counter));

 
}



void setup() {
  Serial.begin(9600);
  Serial.println("Begin setup");
  
  pinMode(hallPin, INPUT);

}

void loop() {

  //delay(5000);
  //testPerformance();

 
  int millisBetweenPulses = getMillisBetweenPulses();
  String strMillisBetweenPulses = String(millisBetweenPulses);
  Serial.print("Millis Between Pulses: ");
  Serial.println(strMillisBetweenPulses);
  
  Serial.println("\n\n*********\n\n");
  delay(1000);
  Serial.println("Getting RPM");

  int rpm = getRpm();
  String strRpm = String(rpm);
  Serial.print("RPM: ");
  Serial.println(strRpm);
  Serial.println("\n\n*********\n\n");
  delay(1000);


}
