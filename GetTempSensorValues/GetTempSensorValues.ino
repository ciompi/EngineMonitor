  /*
 *  This sketch iterates though each DS18B20 sensor found on the DS18B20_BUS pin
 *  and displays the index and temp value to the LCD
 */


#include "OneWire.h"
#include "DallasTemperature.h"
#include <LiquidCrystal.h>

#define DS18B20_BUS 10

OneWire oneWireDS18B20(DS18B20_BUS);

DallasTemperature DS18B20s(&oneWireDS18B20);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



void setup() {
  lcd.begin(16, 2);
  DS18B20s.begin();
}

void loop() {

  lcd.clear();+
  
  lcd.setCursor(0, 0);
  lcd.print("Searching...");
  
  
  DS18B20s.requestTemperatures();
  
  for (int i = 0; i < DS18B20s.getDeviceCount(); i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(i);
    lcd.setCursor(0, 1);
    lcd.print(DS18B20s.getTempFByIndex(i));  
    delay(3000);
  }
}
