#include "OneWire.h"
#include "DallasTemperature.h"

#define MAX31850_BUS 9
#define DS18B20_BUS 10

OneWire oneWireMAX31850(MAX31850_BUS);
OneWire oneWireDS18B20(DS18B20_BUS);

DallasTemperature MAX31850s(&oneWireMAX31850);
DallasTemperature DS18B20s(&oneWireDS18B20);


void printAddress(DeviceAddress addr){

  for( int i = 0; i < 8; i++) {
    Serial.print("0x");
    if (addr[i] < 16) {
      Serial.print('0');
    }
    Serial.print(addr[i], HEX);
      if (i < 7) {
    Serial.print(", ");
    }
  }
}

void testTempSensors(){

  DS18B20s.begin();
  MAX31850s.begin();
  
  DeviceAddress addr;
  
  Serial.println("\n\n **** Testing DS18B20 Sensors ****");

  DS18B20s.requestTemperatures();
  
  for (int i = 0; i < DS18B20s.getDeviceCount(); i++) {

    DS18B20s.getAddress(addr, i);
    
    Serial.print("Index: ");      Serial.print(i); 
    Serial.print(" Address: ");   printAddress(addr);
    Serial.print(" Temp C: ");    Serial.print(DS18B20s.getTempCByIndex(i));
    Serial.print(" Temp F: ");    Serial.println(DS18B20s.getTempFByIndex(i));
  }


  Serial.println("\n\n **** Testing MAX31850s Sensors ****");

  MAX31850s.requestTemperatures();
  
  for (int i = 0; i < MAX31850s.getDeviceCount(); i++) {

    MAX31850s.getAddress(addr, i);
    
    Serial.print("Index: ");      Serial.print(i); 
    Serial.print(" Address: ");   printAddress(addr);
    Serial.print(" Temp C: ");    Serial.print(MAX31850s.getTempCByIndex(i));
    Serial.print(" Temp F: ");    Serial.println(MAX31850s.getTempFByIndex(i));
  }


  Serial.println("\n\n **** Testing Addressing ****");

  DeviceAddress RawWaterIn  =  { 0x28, 0xD2, 0x22, 0x10, 0x07, 0x00, 0x00, 0x8D }; 
  DeviceAddress RawWaterOut =  { 0x28, 0xEA, 0x9B, 0x0F, 0x07, 0x00, 0x00, 0xDF }; 
  DeviceAddress CoolantIn   =  { 0x28, 0x2E, 0x13, 0x10, 0x07, 0x00, 0x00, 0xCB }; 
  DeviceAddress CoolantOut  =  { 0x28, 0x6E, 0x0F, 0x10, 0x07, 0x00, 0x00, 0xE3 }; 
  DeviceAddress CylHead     =  { 0x28, 0x91, 0x80, 0x0F, 0x07, 0x00, 0x00, 0xB3 }; 
  DeviceAddress EngineRoom  =  { 0x28, 0x91, 0xEE, 0x0F, 0x07, 0x00, 0x00, 0x00 }; 
  DeviceAddress Oil         =  { 0x3B, 0xA0, 0x17, 0x19, 0x00, 0x00, 0x00, 0x78 }; 
  DeviceAddress Exhaust     =  { 0x3B, 0x5F, 0x1D, 0x19, 0x00, 0x00, 0x00, 0x93 }; 
  

  // DS18B20 Chips
  
  DS18B20s.requestTemperaturesByAddress(RawWaterIn);
  Serial.println("RawWaterIn: " + String(DS18B20s.getTempF(RawWaterIn)));

  DS18B20s.requestTemperaturesByAddress(RawWaterOut);
  Serial.println("RawWaterOut: " + String(DS18B20s.getTempF(RawWaterOut)));

  DS18B20s.requestTemperaturesByAddress(CoolantIn);
  Serial.println("CoolantIn: " + String(DS18B20s.getTempF(CoolantIn)));
  
  DS18B20s.requestTemperaturesByAddress(CoolantOut);
  Serial.println("CoolantO: " + String(DS18B20s.getTempF(CoolantOut)));
  
  DS18B20s.requestTemperaturesByAddress(CylHead);
  Serial.println("CylHead: " + String(DS18B20s.getTempF(CylHead)));
  
  DS18B20s.requestTemperaturesByAddress(EngineRoom);
  Serial.println("EngineRoom: " + String(DS18B20s.getTempF(EngineRoom)));

  DS18B20s.requestTemperatures();
  Serial.print("Index 0: "); Serial.println(DS18B20s.getTempFByIndex(0));
  Serial.print("Index 1: "); Serial.println(DS18B20s.getTempFByIndex(1));
  Serial.print("Index 2: "); Serial.println(DS18B20s.getTempFByIndex(2));
  Serial.print("Index 3: "); Serial.println(DS18B20s.getTempFByIndex(3));
  Serial.print("Index 4: "); Serial.println(DS18B20s.getTempFByIndex(4));
  Serial.print("Index 5: "); Serial.println(DS18B20s.getTempFByIndex(5));


  // Thermocouples
  
  MAX31850s.requestTemperaturesByAddress(Oil);
  Serial.print("Oil: "); Serial.println(MAX31850s.getTempF(Oil));

  MAX31850s.requestTemperaturesByAddress(Exhaust);
  Serial.print("Exhaust: "); Serial.println(MAX31850s.getTempF(Exhaust));

  
  MAX31850s.requestTemperatures();
  Serial.print("Index 0: "); Serial.println(MAX31850s.getTempFByIndex(0));
  Serial.print("Index 1: "); Serial.println(MAX31850s.getTempFByIndex(1));

}


void testThermocouple(int index){
  
  DeviceAddress addr;
  
  //MAX31850s.begin();
  MAX31850s.requestTemperatures();

  MAX31850s.getAddress(addr, index);
    
  Serial.print(" Address: ");   printAddress(addr);
  Serial.print(" Temp C: ");    Serial.print(MAX31850s.getTempCByIndex(index));
  Serial.print(" Temp F: ");    Serial.println(MAX31850s.getTempFByIndex(index));

  float fltVal = MAX31850s.getTempFByIndex(index);
  String strVal = String(fltVal);
  Serial.print("Index: "); Serial.print(index); Serial.print(" Temp: "); Serial.println(strVal);
}





void setup() {
  Serial.begin(9600);
  
  //DS18B20s.begin();
  MAX31850s.begin();

}

void loop() {
  Serial.println("******  Testing Thermocouples  ******");
  testThermocouple(0);
  testThermocouple(1);  
  Serial.println("\n******  Testing All Temp Sensors  ******");  
  testTempSensors();
  Serial.println("******  Done  ******\n\n");  
  delay(5000);
}










