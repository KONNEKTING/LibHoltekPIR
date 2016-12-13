#include "LibHoltekPIR.h"

// constructor
LibHoltekPIR::LibHoltekPIR(void) {
  
}

void LibHoltekPIR::init(TwoWire &wire) {
  _i2c = &wire;
  _i2c->begin();
}

uint16_t LibHoltekPIR::readRawValue(byte registerPointer) {
  _i2c->beginTransmission(PIR_ADDRESS);
  _i2c->write(registerPointer); 
  _i2c->endTransmission();
  byte toRead, msb, lsb;
  toRead = _i2c->requestFrom(PIR_ADDRESS, 2);
  msb = _i2c->read();
  lsb = _i2c->read();
  uint16_t rawValue = ((uint16_t) msb << 8) | (uint16_t) lsb;
  return rawValue;
}
//Read termperature from register 0x0
int8_t LibHoltekPIR::readTemperature(){
	uint16_t rawValue = readRawValue(POINTER_BITS_CONFIG_STANDBY_WITH_DETECTING_MODE);
	return rawValue >> 8;
}

/*
float LibHoltekPIR::readBrighness(){
	uint16_t rawValue = readRawValue(POINTER_BITS_OPTICAL_SENSOR_AD_RAW_DATA);
	float voltage = (float)rawValue * (VCC_VOLTAGE / 4095);
	return voltage; //ToDo
}


float LibHoltekPIR::readTemperature(){
	uint16_t rawValue = readRawValue(POINTER_BITS_TEMPERATURE_SENSOR_AD_RAW_DATA);
	float voltage = (float)rawValue * (VCC_VOLTAGE / 4095);
	return voltage; //ToDo
}


void LibHoltekPIR::readStatus(bool &init, bool &lvd, bool &blumi, bool &fnoise, bool &fagtrg){
	uint16_t rawValue = readRawValue(POINTER_BITS_TRIG_REGISTER);
	init = rawValue >> 15;
}
*/

uint16_t LibHoltekPIR::readManufactorID(){
    //Request a ManufactorID
	return readRawValue(POINTER_BITS_MANUFACTORE_ID);  
}

uint16_t LibHoltekPIR::readFirmwareVersion(){
    //Request a Firmware Version
	return readRawValue(POINTER_BITS_DEVICE_ID_REVISION_REGISTER);  
}

LibHoltekPIR HoltekPIR;
