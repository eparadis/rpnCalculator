
int dataPin = 9;
int clockPin = 8;
int rclockPin = 7;
byte keypadPin = 0;  // analog0 

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

// populate the given display buffer with the value of the passed int
void convertLongInt( long int num, byte segData[])
{
  byte digit;
  long int modulo = 1;
  
  for( int i = 0; i<8; i += 1)
  {
    digit = num % (modulo*10L) / modulo;
    modulo *= 10;
    
    segData[i] = byteToSegDigit( digit);
  }
}

void convertFloat( float num, byte segData[])
{
  // if num is too large, display an overflow error indication of sorts
  if( num > 9999999.0 || num < -999999.0)
  {
    for( byte i = 0; i < 8; i += 1)
      segData[i] = 0b11111101;  // zero with decimal point
    return;
  }
  
  char cbuf[16];
  for( byte i = 0; i < 16; i += 1)
    cbuf[i] = ' ';
  
  // dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf)
  dtostrf(num, 9, 4, cbuf);
  
  byte i = 0;
  byte j = 0;
  while( i < 8)
  {
    if(cbuf[j] == '.')
    {
      segData[7-i+1] |= 0x01;  // set the decimal point (LSB) of the previous digit
      j += 1;  // move to the next ascii character
    } else if( cbuf[j] == ' ')
    {
      segData[7-i] = 0x00;
      i += 1; 
      j += 1;
    } else if( cbuf[j] == '-')
    {
      segData[7-i] = 0b00000010;
      i += 1; 
      j += 1;
    } else if( cbuf[j] == '\0')
    {
      i = 8;  // stop this crazy train cause we've run out of things to parse! 
    }
    else
    {
      segData[7-i] &= 0x01;  // blank out the segments, but save the decimal point
      segData[7-i] |= byteToSegDigit( cbuf[j] - '0' );
      i += 1;  // move to next display digit
      j += 1;  // move to next ascii character
    }
  }
}

void blankDisplay( byte segData[])
{
  for( byte i = 0; i < 8; i += 1)
    segData[i] = 0x00;
}

byte scanKeypad()
{
  int val = analogRead(keypadPin) / 10;

  byte buttonValues[] = { 0, 4, 8, 13, 18, 22, 27, 31, 36, 41, 45, 50, 54, 59, 64, 68, 73, 1023 };  // the 1023 is to make sure we never go out of range
 
  // find which lookup values we're between 
  byte i = 0;
  while( val > buttonValues[i])
    i++;
  
  // special case incase i == 0
  if( i==0)
    return 0;
  
  // return the index of the lookup value we're closest to
  if( buttonValues[i] - val < val - buttonValues[i-1] )
    return i;
  else 
    return i-1;
}
  
long int count = 1;
long int lastTime = 0;
byte displayData[8] = { 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
void loop()
{  
  blankDisplay( displayData);
  //convertLongInt( count, displayData);
  //convertFloat( sin(count/360.0), displayData);
  //convertFloat( 10.0/(count%10+1) , displayData);
  //convertFloat( pow( 3.14, count/4.0) , displayData);
  convertLongInt( analogRead(keypadPin)/10 + (int)scanKeypad()*1000, displayData);
  displayAllSegments(displayData);  // call this as fast as possible to avoid obvious scanning
  
  if( millis() > lastTime + 200)
  { 
    count += 1;
    lastTime = millis();
  }
}

void setup()
{
  pinMode( dataPin, OUTPUT);
  pinMode( clockPin, OUTPUT);
  pinMode( rclockPin, OUTPUT);

  digitalWrite( rclockPin, HIGH);  // clock reset is active LOW
  digitalWrite( clockPin, LOW);    // shift occurs on rising edge of clock
 
  //blankDisplay( displayData); 
}
