#include "OneWire.h"
#include "DallasTemperature.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define MAX31850_BUS 9
#define DS18B20_BUS 10

OneWire oneWireMAX31850(MAX31850_BUS);
OneWire oneWireDS18B20(DS18B20_BUS);

DallasTemperature MAX31850s(&oneWireMAX31850);
DallasTemperature DS18B20s(&oneWireDS18B20);

const int hallPin = 8;
const int buttonPin = 7;


void testButton(){
  bool buttonPressed = false;
  int buttonState = digitalRead(buttonPin);
  Serial.println("\n********* testButton **********");
  Serial.print("Button State is: "); Serial.println(buttonState); 
  Serial.println("Press Button");
  while (!buttonPressed){
    buttonState = digitalRead(buttonPin);
    if(buttonState == HIGH){
      buttonPressed = true;
      Serial.println("\n** Button Pressed **");
    }
  }
}


void testLCD(){
  Serial.println("\n********** testLCD ************");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Printing Row One");
  lcd.setCursor(0, 1);
  lcd.print("0123456789ABCDEF");  
  Serial.println("Verify LCD printout");
  delay(5000);
}


void testDS18B20Sensors(){
  Serial.println("\n****** testDS18B20Sensors *****");
  DS18B20s.begin();
  DS18B20s.requestTemperatures();
  Serial.print("Index 0: "); Serial.println(DS18B20s.getTempFByIndex(0));
  Serial.print("Index 1: "); Serial.println(DS18B20s.getTempFByIndex(1));
  Serial.print("Index 2: "); Serial.println(DS18B20s.getTempFByIndex(2));
  Serial.print("Index 3: "); Serial.println(DS18B20s.getTempFByIndex(3));
  Serial.print("Index 4: "); Serial.println(DS18B20s.getTempFByIndex(4));
  Serial.print("Index 5: "); Serial.println(DS18B20s.getTempFByIndex(5));
}


void testMAX31850Sensors(){
  Serial.println("\n***** testMAX31850Sensors *****");  
  MAX31850s.begin();
  MAX31850s.requestTemperatures();
  Serial.print("Index 0: "); Serial.println(MAX31850s.getTempFByIndex(0));
  Serial.print("Index 1: "); Serial.println(MAX31850s.getTempFByIndex(1));
}


void testHallSensor(){
  Serial.println("\n******* testHallSensor ********");
  Serial.println("Wave magnet near sensor");
  unsigned long startTime;
  unsigned long deltaMillis;
  int hallReading = HIGH;
  int priorHallReading = HIGH;
  bool changed = false;
  startTime = millis();

  while (!changed){
    hallReading = digitalRead(hallPin);
    if(hallReading != priorHallReading){
      String sensorState = String(hallReading);
      Serial.print("Magnet change detected: "); Serial.println(sensorState);
      deltaMillis = millis() - startTime;
      String twine = String(deltaMillis);
      Serial.print("Milliseconds between change: "); Serial.println(twine);
      changed = true;
    }
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(hallPin, INPUT);
  lcd.begin(16, 2);

  Serial.print("\n\n");
  Serial.println("*******************************");  
  Serial.println("***** Testing All Sensors *****");  
  Serial.println("*******************************");  
  Serial.print("\n");
}


void loop() {
  Serial.println("*******************************");  
  Serial.println("******  Starting Tests  *******");  
  Serial.println("*******************************");  
  Serial.print("\n");
  
  testDS18B20Sensors(); delay(1000);
  testMAX31850Sensors();  delay(1000);
  testHallSensor();  delay(1000);
  testButton();  delay(1000);
  testLCD();  delay(1000);
  
  Serial.println("\n*******************************");  
  Serial.println("*******  Finished Tests  *****"); 
  Serial.println("*******************************\n");  
  
  delay(5000);
  lcd.clear();
}






