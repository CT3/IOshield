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
  64.init();
  64.pinMode(0,OUTPUT);
  64.digitalWrite(0, HIGH);
  int recpin = 64.digitalRead(0);
  64.portMode(0, 0b0111111001111110); // 0 = output, 1 = input
  64.portWrite(0, 0b1000000110000001); // 0 = LOW, 1 = HIGH
  int recport = 64.portRead(0);
  64.pinPullup(1,HIGH);
  64.portPullup(0, 0b0111111001111110); // 0 = no pullup, 1 = pullup
*/
 
64shield 64; // create 64shield object
 
 
void setup()
{
  Wire.begin(); // start I2C
 
  64.initialize(); // set all registers to default
 
  64.portMode(0, 0b0000000000000000); // set all pins on chip 0 to output
 
  //TWBR = 12; // uncomment for 400KHz I2C (on 16MHz Arduinos)
 
}
 
 
void loop()
{  
  for (int i = 0; i < 15; i++) {
    64.digitalWrite(i, HIGH);
    delay(10);
  }
 
  for (int i = 0; i < 15; i++) {
    64.digitalWrite(i, LOW);
    delay(10);
  } 
}
