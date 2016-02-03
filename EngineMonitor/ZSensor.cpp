#include "Arduino.h"
#include "OneWire.h"
#include "DallasTemperature.h"


class ZSensor
{
  public:
    int id;
    int type;
    DeviceAddress devAddr;
};


class ZSensorFactory
{
   public:
    void initZSensors(ZSensor * zensors){

      //  You need to update these addresses with the ones that match your sensors.  Run DiscoverAddresses to retrieve the 
      //  addresses for your sensors









      
      DeviceAddress RawWaterIn  =  { 0x28, 0x3F, 0x72, 0x8B, 0x06, 0x00, 0x00, 0xA5 }; //good
      DeviceAddress RawWaterOut =  { 0x28, 0xFF, 0xC0, 0x2B, 0x73, 0x15, 0x03, 0x74 }; //good
      DeviceAddress CoolantIn   =  { 0x28, 0xFF, 0xF2, 0xCD, 0x72, 0x15, 0x01, 0x24 }; //good
      DeviceAddress CoolantOut  =  { 0x28, 0xFF, 0x7D, 0x02, 0x64, 0x15, 0x01, 0xB8 }; //good
      DeviceAddress CylHead     =  { 0x28, 0xFF, 0x43, 0x30, 0x73, 0x15, 0x03, 0x5D }; //good
      
      DeviceAddress EngineRoom  =  { 0x28, 0x91, 0xEE, 0x0F, 0x07, 0x00, 0x00, 0x00 }; 
      DeviceAddress Oil         =  { 0x3B, 0xA0, 0x17, 0x19, 0x00, 0x00, 0x00, 0x78 }; 
      DeviceAddress Exhaust     =  { 0x3B, 0x5F, 0x1D, 0x19, 0x00, 0x00, 0x00, 0x93 }; 
      
      zensors[0].id = 1;
      zensors[0].type = 1;
      memcpy(zensors[0].devAddr, RawWaterIn, 8);
      
      zensors[1].id = 2;
      zensors[1].type = 1;
      memcpy(zensors[1].devAddr, RawWaterOut, 8);
      
      zensors[2].id = 3;
      zensors[2].type = 1;
      memcpy(zensors[2].devAddr, CoolantIn, 8);

      zensors[3].id = 4;
      zensors[3].type = 1;
      memcpy(zensors[3].devAddr, CoolantOut, 8);

      zensors[4].id = 5;
      zensors[4].type = 1;
      memcpy(zensors[4].devAddr, CylHead, 8);

      zensors[5].id = 6;
      zensors[5].type = 1;
      memcpy(zensors[5].devAddr, EngineRoom, 8);

      zensors[6].id = 7;
      zensors[6].type = 2;
      memcpy(zensors[6].devAddr, Exhaust, 8);

      zensors[7].id = 8;
      zensors[7].type = 2;
      memcpy(zensors[7].devAddr, Oil, 8);

      zensors[8].id = 9;
      zensors[8].type = 3;
    };
};

