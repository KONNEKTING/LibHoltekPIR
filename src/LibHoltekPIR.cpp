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

uint16_t LibHoltekPIR::readRawPirData(){
	return readRawValue(POINTER_BITS_PIR_AD_RAW_DATA);
}

uint16_t LibHoltekPIR::readRawBrightness(){
	return readRawValue(POINTER_BITS_OPTICAL_SENSOR_AD_RAW_DATA);
}

uint16_t LibHoltekPIR::readRawTemperature(){
	return readRawValue(POINTER_BITS_TEMPERATURE_SENSOR_AD_RAW_DATA);
}

uint16_t LibHoltekPIR::readManufactorID(){
    //Request a ManufactorID
	return readRawValue(POINTER_BITS_MANUFACTORE_ID);  
}

uint16_t LibHoltekPIR::readFirmwareVersion(){
    //Request a Firmware Version
	return readRawValue(POINTER_BITS_DEVICE_ID_REVISION_REGISTER);  
}

void LibHoltekPIR::writeRawValue(byte registerPointer, uint16_t value){
    byte msb, lsb;
	msb = value >> 8;
	lsb = value & 0F;
	_i2c->beginTransmission(PIR_ADDRESS);
    _i2c->write(registerPointer); 
	_i2c->write(msb); 
    _i2c->write(lsb);
    _i2c->endTransmission();
}

void LibHoltekPIR::setLvdVoltage(byte value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0xE000; //use only bits 15-13
	value << 13; //fill bits 15-13
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

void LibHoltekPIR::setLvden(bool value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0x1000; //use only bit 12
	value << 12; //fill bit 12
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

void LibHoltekPIR::setPiren(bool value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0x0800; //use only bit 11
	value << 11; //fill bit 11
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

void LibHoltekPIR::setTrigerMode(bool value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0x0200; //use only bit 9
	value << 9; //fill bit 9
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

void LibHoltekPIR::setActen(bool value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0x0100; //use only bit 8
	value << 8; //fill bit 8
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

void LibHoltekPIR::setActen(byte value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0x00E0; //use only bits 7-5
	value << 5; //fill bits 7-5
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

void LibHoltekPIR::setGainControl(uint8_t value){
	uint16_t currentConfig = readRawValue(POINTER_BITS_CONFIGURATION_REGISTER);
	currentConfig &= 0x001F; //use only bits 4-0
	currentConfig |= value;
	writeRawValue(POINTER_BITS_CONFIGURATION_REGISTER,currentConfig);
}

LibHoltekPIR HoltekPIR;
