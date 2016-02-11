#include "FaBoProximity_VCNL4010.h"

FaBoProximity::FaBoProximity(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
}

bool FaBoProximity::searchDevice(void) {
  if ( readId() == 0x21 ) {
    return true;
  } else {
    return false;
  }
}

uint8_t FaBoProximity::readId(void) {
  return readI2c(VCNL4010_ID);
}

void FaBoProximity::configuration(void) {
  setCurrent(20);
  setCommand(VCNL4010_COMMAND_ALL_DISABLE);
  setProxRate(VCNL4010_PROX_MEASUREMENT_RATE_31);
  setCommand(VCNL4010_COMMAND_PROX_ENABLE |
             VCNL4010_COMMAND_AMBI_ENABLE |
             VCNL4010_COMMAND_SELFTIMED_MODE_ENABLE);
  setAmbiConfig(VCNL4010_AMBI_PARA_AVERAGE_32 |
                VCNL4010_AMBI_PARA_AUTO_OFFSET_ENABLE |
                VCNL4010_AMBI_PARA_MEAS_RATE_2);
}

void FaBoProximity::setCurrent(uint8_t current) {
  if ( current > 20 ) {
    current = 20;
  }
  writeI2c(VCNL4010_PROX_CURRENT, current);
}

uint8_t FaBoProximity::readCurrent(void) {
  return readI2c(VCNL4010_PROX_CURRENT);
}

void FaBoProximity::setCommand(uint8_t command) {
  writeI2c(VCNL4010_COMMAND, command);
}

uint8_t FaBoProximity::readCommand(void) {
  return readI2c(VCNL4010_COMMAND);
}

void FaBoProximity::setProxRate(uint8_t rate) {
  writeI2c(VCNL4010_PROX_RATE, rate);
}

void FaBoProximity::setAmbiConfig(uint8_t config) {
  writeI2c(VCNL4010_AMBI_PARAMETER, config);
}

bool FaBoProximity::isProxDataReady(void) {
  if (readCommand() & VCNL4010_COMMAND_MASK_PROX_DATA_READY) {
    return true;
  }
  return false;
}

bool FaBoProximity::isAmbiDataReady(void) {
  if (readCommand() & VCNL4010_COMMAND_MASK_AMBI_DATA_READY) {
    return true;
  }
  return false;
}

uint16_t FaBoProximity::readProxValue(void) {
  uint16_t value;
  value = readI2c(VCNL4010_PROX_VALUE);
  value <<= 8;
  value |= readI2c(VCNL4010_PROX_VALUE+1);
  return value;
}

uint16_t FaBoProximity::readAmbiValue(void) {
  uint16_t value;
  value = readI2c(VCNL4010_AMBI_VALUE);
  value <<= 8;
  value |= readI2c(VCNL4010_AMBI_VALUE+1);
  return value;
}

////////////////////////////////////////////////////////////////

uint8_t FaBoProximity::readI2c(uint8_t address) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, (uint8_t)1);
  while(!Wire.available());
  return Wire.read();
}

void FaBoProximity::writeI2c(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}
