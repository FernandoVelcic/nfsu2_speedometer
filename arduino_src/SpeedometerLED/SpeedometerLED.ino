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

  for(int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
  
  pinMode(5, OUTPUT);
}

void loop()
{
  if(Serial.available() >= 4)
  {
    //SERIAL: Read
    SpeedometerInfo.Speed = (Serial.read() << 0) | (Serial.read() << 8);
    SpeedometerInfo.Shift = Serial.read();
    SpeedometerInfo.Leds = Serial.read();
   
    for(int i = 0; i < SpeedometerInfo.Leds; i++) {
      digitalWrite(13-i, HIGH);
    }
    
    for(int i = SpeedometerInfo.Leds; i < 8; i++) {
      digitalWrite(13-i, LOW); 
    }
    
    if(SpeedometerInfo.Speed > 100)
      digitalWrite(5, HIGH);
    else
      digitalWrite(5, LOW);
  }
}
