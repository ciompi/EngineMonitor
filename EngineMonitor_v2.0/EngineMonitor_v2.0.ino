byte number = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  if (Serial.available()) {
    number = Serial.read();
    String retVal = "{\"RWI\" : 71.1, \"";
    retVal = retVal + "\"RWO\" : 71.2, \"";
    retVal = retVal + "\"CEH\" : 71.3, \"";
    retVal = retVal + "\"CLH\" : 71.4, \"";
    retVal = retVal + "\"CYL\" : 71.5, \"";
    retVal = retVal + "\"ENR\" : 71.6, \"";
    retVal = retVal + "\"OIL\" : 71.7, \"";
    retVal = retVal + "\"EGT\" : 71.8, \"";
    retVal = retVal + "\"RPM\" : 71.6, \"";
    Serial.println(retVal);
  }
  delay(1000);
}
