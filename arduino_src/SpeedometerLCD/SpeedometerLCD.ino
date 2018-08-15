#include <TM1638.h>

TM1638 module(8, 9, 7);

struct sSpeedometerInfo
{
  /*<thisrel this+0x0>*/ /*|0x2|*/ unsigned short Speed;
  /*<thisrel this+0x2>*/ /*|0x1|*/ unsigned char  Shift;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char  Leds;
} SpeedometerInfo; 

void setup()
{
  Serial.begin(19200);
  Serial.flush();
  
  //module.setupDisplay(true, 5);
}

void loop()
{
  if(Serial.available() >= 4)
  {
    //SERIAL: Read
    SpeedometerInfo.Speed = (Serial.read() << 0) | (Serial.read() << 8);
    SpeedometerInfo.Shift = Serial.read();
    SpeedometerInfo.Leds = Serial.read();
   
    //LEDS: Turn on/off 
    
    switch(SpeedometerInfo.Leds)
    {
      case 0:
        module.setLEDs(0x0000); //TM1638_COLOR_GREEN
        break;
      case 1:
        module.setLEDs(0x8000);
        break;
      case 2:
        module.setLEDs(0xC000);
        break;
      case 3:
        module.setLEDs(0xE000);
        break;
      case 4:
        module.setLEDs(0xF000);
        break;
      case 5:
        module.setLEDs(0xF808); //TM1638_COLOR_GREEN + TM1638_COLOR_RED
        break;
      case 6:
        module.setLEDs(0xFC0C);
        break;
      case 7:
        module.setLEDs(0xF80E);
        break;
      case 8:
        module.setLEDs(0x00FF); //TM1638_COLOR_RED
        break;
    }

    //DISPLAY: Show
    module.setDisplayToDecNumber(SpeedometerInfo.Speed, 0, false);
    module.setDisplayDigit(SpeedometerInfo.Shift, 0, false);
  }
}

/*
bitfield method
#define GET_BIT(var, n) ((var >> n) & 0x1)

    for(int i = 0; i < 8; i++)
    {
      if( GET_BIT(SpeedometerInfo.Leds, i) == 1 )
      {
        switch(i)
        {
          case 0: case 1: case 2: case 3:
            module.setLED(TM1638_COLOR_GREEN, i);
          case 4:
            module.setLED(TM1638_COLOR_GREEN + TM1638_COLOR_RED, 4);
          case 5: case 6:
            module.setLED(TM1638_COLOR_RED, i);
          case 7:
            module.setLEDs(0x00FF); //Light up all the red LEDs
        }
      }
      else
      {
        module.setLED(0, i); //Turn off all LEDs
      }
    }
*/
