#include <OneWire.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include "ZSensor.cpp"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ONE_WIRE_BUS_A 9
#define ONE_WIRE_BUS_B 10

OneWire oneWireA(ONE_WIRE_BUS_A);
OneWire oneWireB(ONE_WIRE_BUS_B);

DallasTemperature sensorsA(&oneWireA);
DallasTemperature sensorsB(&oneWireB);

ZSensor zensors[9];          // List of sensors with attributes
const int ledPin = 6;        // Pin connected to LED
const int buttonPin = 7;     // Pin connected to pushbutton
const int hallPin = 8;        // Pin connected to Hall sensor
int currSensor = 1;          // Indicates the sensor currently displayed on the LCD screen
bool lastButtonState = LOW;
int lastId;
String lastValPrinted;


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
        //Serial.print("Took too long.  Milliseconds between change: ");
        //Serial.println(strTestDeltaMillis);
      }
    }

    // Taking too long to get a reading
    if (!normalOps){
      //Serial.print("Abnormal Operations");
      return -1;
    }

    String sensorState = String(hallReading);
  }

  // Milliseconds for 10 revolutions
  deltaMillis = millis() - startTime;
  String strDeltaMillis = String(deltaMillis);
  //Serial.print("Milliseconds for 10 revolutions: " + strDeltaMillis);

  float oneRev = deltaMillis / 10;

  float fltRpm = 60000 / oneRev;

  rpm = (int) fltRpm;  

  return rpm;
}


void printSensor(int Id, String value){

  if(lastId != Id || lastValPrinted != value){
    lcd.clear();
    lcd.setCursor(0, 0);

    switch (Id) {
      case 0:
        lcd.print("Raw Water In");
        break;
      case 1:
        lcd.print("Raw Water Out");
        break;
      case 2:
        lcd.print("Coolant In");
        break;
      case 3:
        lcd.print("Coolant Out");
        break;
      case 4:
        lcd.print("Cylinder Head");
        break;
      case 5:
        lcd.print("Engine Room");
        break;
      case 6:
        lcd.print("Exhaust");
        break;
      case 7:
        lcd.print("Oil");
        break;
      case 8:
        lcd.print("RPM");
        break;                                                        
      default: 
        lcd.print("Error");
      break;
    }

    lcd.setCursor(0, 1);
    lcd.print(value);  
    
    lastId = Id;
    lastValPrinted = value;
  }
}

void printWorking(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    Working...");
}


void displaySensor(ZSensor sensor){
 
  // Determine sensor type
  if(sensor.type == 1){
    sensorsA.requestTemperaturesByAddress(sensor.devAddr);
    printSensor(sensor.id, String(sensorsA.getTempF(sensor.devAddr))); 
  } 
  
  else if(sensor.type == 2){
    sensorsB.requestTemperaturesByAddress(sensor.devAddr);
    printSensor(sensor.id, String(sensorsB.getTempF(sensor.devAddr))); 
  }
  
  else if(sensor.type == 3){
    int rpm = getRpm();

    if (rpm == -1){
      printSensor( sensor.id, "Not Detected");
    } else {
      printSensor( sensor.id, String(rpm));  
    }
  }
}


void setup() {
  //Serial.begin(9600);
  //Serial.println("Begin setup");
  
  pinMode(buttonPin, INPUT);
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, HIGH);  

  lcd.begin(16, 2);
  printWorking();

  ZSensorFactory factory;
  factory.initZSensors(zensors);
  delay(500);
  sensorsA.begin();
  sensorsB.begin();
  digitalWrite(ledPin, LOW);
  
  //Serial.println("Complete setup");

}

void loop() {

  // Debounce
  if (digitalRead(buttonPin) == HIGH){
    delay(5);
    if (digitalRead(buttonPin) == HIGH){
      lastButtonState = HIGH;
    }
  }
  
  if (digitalRead(buttonPin) == LOW && lastButtonState == HIGH) {
    //Serial.println("Button Released");
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

