#include <OneWire.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include "ZSensor.cpp"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ZSensor zensors[9];          // List of sensors with attributes
const int ledPin = 6;        // Pin connected to LED
const int buttonPin = 7;     // Pin connected to pushbutton
const int hallPin = 8;        // Pin connected to Hall sensor
int currSensor = 1;          // Indicates the sensor currently displayed on the LCD screen
bool lastButtonState = LOW;
String lastKeyPrinted;
String lastValPrinted;


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


void printInfo(String key, int value){
  String val = String(value);
  printInfo(key, val);
}


void printInfo(String key, float value){
  String val = String(value);
  printInfo(key, val);
}


void printInfo(String key, String value){
  
  if(lastKeyPrinted != key || lastValPrinted != value){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(key);
    lcd.setCursor(0, 1);
    lcd.print(value);  
    lastKeyPrinted = key;
    lastValPrinted = value;
  }
}

void printWorking(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Working...");
}


void setLedOn(){
  digitalWrite(ledPin, HIGH); 
}


void setLedOff(){
  digitalWrite(ledPin, LOW); 
}


void printWarning (String key, String value){

  setLedOn();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WARNING");
  lcd.setCursor(0, 1);
  lcd.print(key);  
  delay(500);
  
  printInfo(key, value);
  delay(500);
  
  setLedOff();
}

void displaySensor(ZSensor sensor){
 
  // Determine sensor type
  if(sensor.type == 1){
    sensors.requestTemperaturesByAddress(sensor.devAddr);
    printInfo(sensor.desc, sensors.getTempF(sensor.devAddr)); 
  } 
  
  else if(sensor.type == 2){
    printWarning(sensor.desc, "Not Implemented");
  }
  
  else if(sensor.type == 3){
    int rpm = getRpm();

    if (rpm == -1){
      printInfo( sensor.desc, "Not Detected");
    } else {
      printInfo( sensor.desc, rpm);  
    }
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Begin setup");
  
   // initialize pins
  pinMode(buttonPin, INPUT);
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // turn on the led during startup
  digitalWrite(ledPin, HIGH);  // turn LED ON

  lcd.begin(16, 2);
  printInfo("Engine Monitor", "Starting Up");

  ZSensorFactory factory;
  factory.initZSensors(zensors);
  delay(500);
  sensors.begin();
  digitalWrite(ledPin, LOW);
  
  Serial.println("Complete setup");
  
}

void loop() {
  //Serial.println("Looping");
  // Determine if Next has been pressed
  if (digitalRead(buttonPin) == HIGH){
    delay(5);
    if (digitalRead(buttonPin) == HIGH){
      lastButtonState = HIGH;
    }
  }
  
  if (digitalRead(buttonPin) == LOW && lastButtonState == HIGH) {
    Serial.println("Button Released");
    printWorking();
    // Move to the next sensor
    if (currSensor < 9){
      currSensor++;
    } else {
      currSensor = 1;
    }
    lastButtonState = LOW;
  } 
  
  displaySensor(zensors[currSensor - 1]);

}

