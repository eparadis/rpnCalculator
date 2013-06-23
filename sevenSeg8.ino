
int dataPin = 9;
int clockPin = 8;
int rclockPin = 7;

void setup()
{
  pinMode( dataPin, OUTPUT);
  pinMode( clockPin, OUTPUT);
  pinMode( rclockPin, OUTPUT);

  digitalWrite( rclockPin, HIGH);  // clock reset is active LOW
  digitalWrite( clockPin, LOW);    // shift occurs on rising edge of clock
  
}

void shiftOutByte( byte b)
{
  for( int i = 0; i < 8; i += 1)
  {
    if( b & 0x01)
      digitalWrite( dataPin, HIGH);
    else
      digitalWrite( dataPin, LOW);
    b = b >> 1;
  
    digitalWrite( clockPin, LOW);
    digitalWrite( clockPin, HIGH);
  }
}

void resetShiftReg()
{
  digitalWrite( rclockPin, LOW);
  digitalWrite( rclockPin, HIGH);
}

// given an array of 8 bytes, populate all the segments of the display
void displayAllSegments( byte data[] )
{
  byte digit = 1;
  for( byte i = 0; i < 8; i += 1)
  {
    resetShiftReg();
    shiftOutByte( digit);  // digit
    shiftOutByte( ~data[i] );   // segment (inverted)
    digit = digit << 1;
  }  
}

/*
MSB is A
LSB is decimal

    a
    _  
 f | | b
    - g
 e | | c
    _   .h
    d

 abcd efgh
*/
byte byteToSegDigit( byte num )
{
  num = num % 10;  // clamp that shiiiizzz
  //                   0            1           2            3           4          5           6            7         8           9
  byte lookup[] = { 0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11100110 };
  return lookup[num];
}
  
    

byte count = 1;
byte displayData[8] = { 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
int lastTime = 0;
void loop()
{
  displayData[0] = byteToSegDigit( count);
  displayAllSegments(displayData);  // call this as fast as possible to avoid obvious scanning
  
  if( millis() > lastTime + 1000)
  { 
    count += 1;
    lastTime = millis();
  }
}
