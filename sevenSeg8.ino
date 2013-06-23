
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


byte count = 1;
byte digit = 1;
byte displayData[8] = { 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
void loop()
{
  displayAllSegments(displayData);  // call this as fast as possible to avoid obvious scanning  
}
