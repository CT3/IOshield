// Example code for Centipede Library
// Works with Centipede Shield or MCP23017 on Arduino I2C port
 
#include <Wire.h>
#include <64shield.h>
 
 
/* Available commands
  .digitalWrite([0...127], [LOW...HIGH]) - Acts like normal digitalWrite
  .digitalRead([0...127]) - Acts like normal digitalRead
  .pinMode([0...127], [INPUT...OUTPUT]) - Acts like normal pinMode
  .portWrite([0...7], [0...65535]) - Writes 16-bit value to one port (chip)
  .portRead([0...7]) - Reads 16-bit value from one port (chip)
  .portMode([0...7], [0...65535]) - Write I/O mask to one port (chip)
  .pinPullup([0...127], [LOW...HIGH]) - Sets pullup on input pin
  .portPullup([0...7], [0...65535]) - Sets pullups on one port (chip)
  .init() - Sets all registers to initial values
 
  Examples
  IO.init();
  IO.pinMode(0,OUTPUT);
  IO.digitalWrite(0, HIGH);
  int recpin = IO.digitalRead(0);
  IO.portMode(0, 0b0111111001111110); // 0 = output, 1 = input
  IO.portWrite(0, 0b1000000110000001); // 0 = LOW, 1 = HIGH
  int recport = IO.portRead(0);
  IO.pinPullup(1,HIGH);
  IO.portPullup(0, 0b0111111001111110); // 0 = no pullup, 1 = pullup
*/
 
64shield IO; // create 64shield object
 
 
void setup()
{
  Wire.begin(); // start I2C
 
  IO.initialize(); // set all registers to default
 
  IO.portMode(0, 0b0000000000000000); // set all pins on chip 0 to output
 
  //TWBR = 12; // uncomment for 400KHz I2C (on 16MHz Arduinos)
 
}
 
 
void loop()
{  
  for (int i = 0; i < 15; i++) {
    IO.digitalWrite(i, HIGH);
    delay(10);
  }
 
  for (int i = 0; i < 15; i++) {
    IO.digitalWrite(i, LOW);
    delay(10);
  } 
}
