#include "Arduino.h"
#include "OneWire.h"
#include "DallasTemperature.h"

//typedef uint8_t DeviceAddress[8];

class ZSensor
{
  public:
    int id;
    int type;
    String desc;
    DeviceAddress devAddr;
    int intAddr;
    int currVal;
};


class ZSensorFactory
{
   public:
    int id; 
    void initZSensors(ZSensor * zensors){

      DeviceAddress RawWaterIn  =  { 0x28, 0xD2, 0x22, 0x10, 0x07, 0x00, 0x00, 0x8D }; 
      DeviceAddress RawWaterOut =  { 0x28, 0xEA, 0x9B, 0x0F, 0x07, 0x00, 0x00, 0xDF }; 
      DeviceAddress CoolantIn   =  { 0x28, 0x2E, 0x13, 0x10, 0x07, 0x00, 0x00, 0xCB }; 
      DeviceAddress CoolantOut  =  { 0x28, 0x6E, 0x0F, 0x10, 0x07, 0x00, 0x00, 0xE3 }; 
      DeviceAddress CylHead     =  { 0x28, 0x91, 0x80, 0x0F, 0x07, 0x00, 0x00, 0xB3 }; 
      DeviceAddress EngineRoom  =  { 0x28, 0x91, 0xEE, 0x0F, 0x07, 0x00, 0x00, 0x00 }; 
      DeviceAddress Oil         =  { 0x3B, 0xA0, 0x17, 0x19, 0x00, 0x00, 0x00, 0x78 }; 
      DeviceAddress Exhaust     =  { 0x3B, 0x5F, 0x1D, 0x19, 0x00, 0x00, 0x00, 0x93 }; 
      
      zensors[0].id = 1;
      zensors[0].type = 1;
      zensors[0].desc = "Raw Water In";      
      zensors[0].currVal = -1;   
      memcpy(zensors[0].devAddr, RawWaterIn, 8);
      
      zensors[1].id = 2;
      zensors[1].type = 1;
      zensors[1].desc = "Raw Water Out";      
      zensors[1].currVal = -1;    
      memcpy(zensors[1].devAddr, RawWaterOut, 8);
      
      zensors[2].id = 3;
      zensors[2].type = 1;
      zensors[2].desc = "Coolant In";      
      zensors[2].currVal = -1;    
      memcpy(zensors[2].devAddr, CoolantIn, 8);

      zensors[3].id = 4;
      zensors[3].type = 1;
      zensors[3].desc = "Coolant Out";      
      zensors[3].currVal = -1;    
      memcpy(zensors[3].devAddr, CoolantOut, 8);

      zensors[4].id = 5;
      zensors[4].type = 1;
      zensors[4].desc = "Cylinder Head";      
      zensors[4].currVal = -1;    
      memcpy(zensors[4].devAddr, CylHead, 8);

      zensors[5].id = 6;
      zensors[5].type = 1;
      zensors[5].desc = "Engine Room";      
      zensors[5].currVal = -1;    
      memcpy(zensors[5].devAddr, EngineRoom, 8);

      zensors[6].id = 7;
      zensors[6].type = 2;
      zensors[6].desc = "Exhaust";      
      zensors[6].currVal = -1;    

      zensors[7].id = 8;
      zensors[7].type = 2;
      zensors[7].desc = "Oil";      
      zensors[7].currVal = -1;    

      zensors[8].id = 9;
      zensors[8].type = 3;
      zensors[8].desc = "RPM";      
      zensors[8].currVal = -1;    

    };
};

