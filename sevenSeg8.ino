
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


byte count = 1;
byte digit = 1;
void loop()
{
  resetShiftReg();
  shiftOutByte( digit);  // digit
  shiftOutByte( ~count );   // segment (inverted)
  count = count << 1;
  if( count == 0)
  {
    count = 1;
    digit = digit << 1;
  }
  if( digit == 0)
    digit = 1;
  delay(100);
  
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
    delay(1);
    digitalWrite( clockPin, HIGH);
    delay(1);  
    
  }
}

void resetShiftReg()
{
  digitalWrite( rclockPin, LOW);
  delay( 1);
  digitalWrite( rclockPin, HIGH);
  delay( 1);
}
