#ifndef LIBHOLTEK_h
#define LIBHOLTEK_h

#define PIR_ADDRESS 0x4C

//Register Pointer
#define POINTER_BITS_CONFIG_STANDBY_WITH_DETECTING_MODE 0x0
#define POINTER_BITS_CONFIGURATION_REGISTER 0x1
#define POINTER_BITS_CONFIG_MODULE_ADDRESS 0x2
#define POINTER_BITS_CONFIG_TRIG_TIME_INTERVAL 0x3
#define POINTER_BITS_EEPROM_ACCESS 0x4
#define POINTER_BITS_PIR_AD_RAW_DATA 0x5
#define POINTER_BITS_OPTICAL_SENSOR_AD_RAW_DATA 0x6
#define POINTER_BITS_TEMPERATURE_SENSOR_AD_RAW_DATA 0x7
#define POINTER_BITS_TRIG_REGISTER 0x8
#define POINTER_BITS_MANUFACTORE_ID 0x9
#define POINTER_BITS_DEVICE_ID_REVISION_REGISTER 0xA
#define POINTER_BITS_TEST_RESULT_INQUIRE 0xB
#define POINTER_BITS_RESET_TEST_RESULT 0xC

//CONFIG_STANDBY_WITH_DETECTING_MODE
#define STANDBY_4MS 0x0
#define STANDBY_8MS 0x1
#define STANDBY_16MS 0x2
#define STANDBY_21MS 0x3

//CONFIGURATION_REGINSTER
//bit 15-13: Select LVD Voltage
#define LVD_VOLTAGE_2V0 0x0
#define LVD_VOLTAGE_2V2 0x1
#define LVD_VOLTAGE_2V4 0x2
#define LVD_VOLTAGE_2V7 0x3 //default
#define LVD_VOLTAGE_3V0 0x4
#define LVD_VOLTAGE_3V3 0x5
#define LVD_VOLTAGE_3V6 0x6
#define LVD_VOLTAGE_4V0 0x7
//bit 12: LVDEN, Turn on the low voltage detection function
#define LVDEN_ON 0x1 //default
#define LVDEN_OFF 0x0
//bit 11: PirEN: PIR detect
#define PIREN_ENABLE 0x1
#define PIREN_DISABLE 0x0
//bit 10 reserved
//bit 9: Trig mode
#define TRIGGER_COUNTINUOUS 0x1 //deafult
#define TRIGGER_SINGLE 0x0
//bit 8 ACTEN, ACT pin function
#define ACTEN_ENABLE 0x1 //default
#define ACTEN_DISABLE 0x0
//bit 7-5, Threshold Trigger 1-8
#define THRESHOLD_TRIGGER_1 0x0 //(offset +/- 0.2) default
#define THRESHOLD_TRIGGER_2 0x1 //(offset +/- 0.3) 
#define THRESHOLD_TRIGGER_3 0x2 //(offset +/- 0.4) 
#define THRESHOLD_TRIGGER_4 0x3 //(offset +/- 0.5) 
#define THRESHOLD_TRIGGER_5 0x4 //(offset +/- 0.6) 
#define THRESHOLD_TRIGGER_6 0x5 //(offset +/- 0.7) 
#define THRESHOLD_TRIGGER_7 0x6 //(offset +/- 0.8) 
#define THRESHOLD_TRIGGER_8 0x7 //(offset +/- 0.9) 
//bit 4-0: OPA2 Gain Control: gain = 32 + (PGAC × 2), Default gain = 64 

class LibHoltekPIR {

  public:
    LibHoltekPIR(void);
    void init(TwoWire &wire = Wire);
    int8_t readTemperature(void);
    uint16_t readRawPirData();
    uint16_t readRawBrightness();
    uint16_t readRawTemperature();
    uint16_t readManufactorID(void);
    uint16_t readFirmwareVersion(void);
    void setLvdVoltage(byte value);
    void setLvden(bool value);
    void setPiren(bool value);
    void setTrigerMode(bool value);
    void setActen(byte value);
    void setGainControl(uint8_t value);

  private:
    TwoWire *_i2c;
    uint16_t readRawValue(byte registerPointer);
    void writeRawValue(byte registerPointer, uint16_t value);
};

extern LibHoltekPIR HoltekPIR;

#endif
