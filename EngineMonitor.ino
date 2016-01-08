
#include <OneWire.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ONE_WIRE_BUS 10

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

void getRpm(){
  
  
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.autoscroll();
  lcd.print("Engine Monitoring System");
  delay(1000);
  lcd.noAutoscroll();
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Temperature 0");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(0));  
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Temperature 1");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(1));  
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature 2");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(2));  
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature 3");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(3));  
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature 4");
  lcd.setCursor(0, 1);
  lcd.print(sensors.getTempCByIndex(4));  
  delay(1000);
}


/*
Address Data:
ROM = 28 3F 72 8B 6 0 0 A5

  Chip = DS18B20

  Data = 1 20 1 4B 46 7F FF 10 10 FC  CRC=FC

  Temperature = 18.00 Celsius, 64.40 Fahrenheit

ROM = 28 FF C0 2B 73 15 3 74

  Chip = DS18B20

  Data = 1 29 1 4B 1 7F FF C 10 8C  CRC=8C

  Temperature = 18.56 Celsius, 65.41 Fahrenheit

ROM = 28 FF F2 CD 72 15 1 24

  Chip = DS18B20

  Data = 1 2F 1 4B 1 7F FF C 10 1F  CRC=1F

  Temperature = 18.94 Celsius, 66.09 Fahrenheit

ROM = 28 FF 7D 2 64 15 1 B8

  Chip = DS18B20

  Data = 1 28 1 80 80 1F FF 80 80 4D  CRC=4D

  Temperature = 18.50 Celsius, 65.30 Fahrenheit

ROM = 28 FF 43 30 73 15 3 5D

  Chip = DS18B20

  Data = 1 25 1 4B 1 7F FF C 10 B3  CRC=B3

  Temperature = 18.31 Celsius, 64.96 Fahrenheit

No more addresses.
*/
