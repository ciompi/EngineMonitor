
#include <OneWire.h>
#define SENSOR_PIN 10  
OneWire  ourBus(SENSOR_PIN); 

void setup()
{
  Serial.begin(9600);
 
  
}

void loop() 
{
  discoverOneWireDevices();  
}

/*-----( Declare User-written Functions )-----*/
void discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  Serial.print("Looking for 1-Wire devices...\n\r");// "\n\r" is NewLine 
  while(ourBus.search(addr)) {
    Serial.print("\n\r\n\rFound \'1-Wire\' device with address:\n\r");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      } 
      
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!\n\r");
      return;
    }
    ourBus.requestTemperatures();
    Serial.println(ourBus.
    
  }
  Serial.println();
  Serial.print("Done");
    


  
  ourBus.reset_search();
  return;
}

