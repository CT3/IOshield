// 64shield Library
// Controls MCP23017 16-bit digital I/O chips

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "64shield.h"
#include <Wire.h>

uint8_t CSDataArray[2] = {0};

#define CSAddress 0b0100000

64shield::64shield()
{
  // no constructor tasks yet
}

// Set device to default values
void 64shield::initialize()
{

  for (int j = 0; j < 7; j++) {

    CSDataArray[0] = 255;
    CSDataArray[1] = 255;

    WriteRegisters(j, 0x00, 2);

    CSDataArray[0] = 0;
    CSDataArray[1] = 0;

    for (int k = 2; k < 0x15; k+=2) {
      WriteRegisters(j, k, 2);
    }

  }

}


void 64shield::WriteRegisters(int port, int startregister, int quantity) {

  Wire.beginTransmission(CSAddress + port);
#if defined(ARDUINO) && ARDUINO >= 100
    Wire.write((byte)startregister);
    for (int i = 0; i < quantity; i++) {
		Wire.write((byte)CSDataArray[i]);
    }
#else
    Wire.send((byte)startregister);
    for (int i = 0; i < quantity; i++) {
		Wire.send((byte)CSDataArray[i]);
    }
#endif

  Wire.endTransmission();

}

void 64shield::ReadRegisters(int port, int startregister, int quantity) {

  Wire.beginTransmission(CSAddress + port);
#if defined(ARDUINO) && ARDUINO >= 100
	Wire.write((byte)startregister);
	Wire.endTransmission();
	Wire.requestFrom(CSAddress + port, quantity);
	for (int i = 0; i < quantity; i++) {
		CSDataArray[i] = Wire.read();
	}
#else
	Wire.send((byte)startregister);
	Wire.endTransmission();
	Wire.requestFrom(CSAddress + port, quantity);
	for (int i = 0; i < quantity; i++) {
		CSDataArray[i] = Wire.receive();
	}
#endif

}


void 64shield::WriteRegisterPin(int port, int regpin, int subregister, int level) {

  ReadRegisters(port, subregister, 1); 
  
  if (level == 0) {
    CSDataArray[0] &= ~(1 << regpin);
  }
  else {
    CSDataArray[0] |= (1 << regpin);
  }
  
  WriteRegisters(port, subregister, 1);
  
}

void 64shield::pinMode(int pin, int mode) {
  
  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, subregister, mode ^ 1);
  
}

void 64shield::pinPullup(int pin, int mode) {
  
  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, 0x0C + subregister, mode);
  
}


void 64shield::digitalWrite(int pin, int level) {
  
  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, 0x12 + subregister, level);
  
}

int 64shield::digitalRead(int pin) {

  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  ReadRegisters(port, 0x12 + subregister, 1);

  int returnval = (CSDataArray[0] >> (pin - ((port << 1) + subregister)*8)) & 1;

  return returnval;

}

void 64shield::portMode(int port, int value) {
  
  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;
  
  WriteRegisters(port, 0x00, 2);
  
}

void 64shield::portWrite(int port, int value) {
  
  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;
  
  WriteRegisters(port, 0x12, 2);
  
}

void 64shield::portPullup(int port, int value) {
  
  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;
  
  WriteRegisters(port, 0x0C, 2);
  
}

int 64shield::portRead(int port) {

  ReadRegisters(port, 0x12, 2);

  int receivedval = CSDataArray[0];
  receivedval |= CSDataArray[1] << 8;

  return receivedval;  

}




