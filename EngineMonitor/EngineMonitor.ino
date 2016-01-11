#include <OneWire.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include "ZSensor.cpp"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ZSensor zensors[9];          // list of sensors with attributes
const int buttonPin = 7;     // the pin that the pushbutton is attached to
const int ledPin = 6;        // the pin that the LED is attached to
int currSensor = 1;          // 1 through 9
bool lastButtonState = LOW;
String lastKeyPrinted;
String lastValPrinted;


int getRpm(){
  return 2200;
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
  float tempF;
  
  // Determine sensor type
  if(sensor.type == 1){
    
    //Serial.println("requestTemperatures");
    //sensors.requestTemperatures();
    //Serial.println("requestTemperaturesByAddress");
    sensors.requestTemperaturesByAddress(sensor.devAddr);
    //Serial.println("getTempF");
    tempF = sensors.getTempF(sensor.devAddr);
    //Serial.println("Done");    
    printInfo(sensor.desc, tempF); 
  } 
  else if(sensor.type == 2){
    printWarning(sensor.desc, "Not Implemented");
  }
  else if(sensor.type == 3){
    printInfo( sensor.desc, getRpm());     
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Begin setup");
   // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);

  // initialize the LED as an output:
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

