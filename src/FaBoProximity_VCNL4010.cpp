/**
 * @file  FaBoProximity_VCNL4010.cpp
 * @brief fabo libtary of VCNL4010
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#include "FaBoProximity_VCNL4010.h"

/**
 * @brief VCNL4010 processing Start
 * @param addr : VCNL4010 Slave Address
 */
FaBoProximity::FaBoProximity(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
}

/**
 * @brief Search Device VCNL4010
 * @retval true  : found
 * @retval false : Not found
 */
bool FaBoProximity::searchDevice(void) {
  if ( readId() == 0x21 ) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Read product ID and product revision
 * @retval true  : found
 * @retval false : Not found
 */
uint8_t FaBoProximity::readId(void) {
  return readI2c(VCNL4010_ID);
}

/**
 * @brief Set Config
 */
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

/**
 * @brief LED Current Setting for Proximity
 * @param [in] current : IR LED current value
 */
void FaBoProximity::setCurrent(uint8_t current) {
  if ( current > 20 ) {
    current = 20;
  }
  writeI2c(VCNL4010_PROX_CURRENT, current);
}

/**
 * @brief Read LED Current for Proximity
 * @return uint8_t : IR LED current value
 */
uint8_t FaBoProximity::readCurrent(void) {
  return readI2c(VCNL4010_PROX_CURRENT);
}

/**
 * @brief Set Command Data
 * @param [in] command : set command data
 */
void FaBoProximity::setCommand(uint8_t command) {
  writeI2c(VCNL4010_COMMAND, command);
}

/**
 * @brief Read Command Data
 * @return uint8_t : read command value
 */
uint8_t FaBoProximity::readCommand(void) {
  return readI2c(VCNL4010_COMMAND);
}

/**
 * @brief Set Proximity Rate
 * @param [in] rate : set rate value
 */
void FaBoProximity::setProxRate(uint8_t rate) {
  writeI2c(VCNL4010_PROX_RATE, rate);
}

/**
 * @brief Set Ambient Light Config
 * @param [in] config : set config data
 */
void FaBoProximity::setAmbiConfig(uint8_t config) {
  writeI2c(VCNL4010_AMBI_PARAMETER, config);
}

/**
 * @brief Detect Proximity Data Ready
 * @retval true  : Ready
 * @retval false : Not Ready
 */
bool FaBoProximity::isProxDataReady(void) {
  if (readCommand() & VCNL4010_COMMAND_MASK_PROX_DATA_READY) {
    return true;
  }
  return false;
}

/**
 * @brief Detect Ambient Light Data Ready
 * @retval true  : Ready
 * @retval false : Not Ready
 */
bool FaBoProximity::isAmbiDataReady(void) {
  if (readCommand() & VCNL4010_COMMAND_MASK_AMBI_DATA_READY) {
    return true;
  }
  return false;
}

/**
 * @brief Read Proximity
 * @return uint8_t : Proximity value
 */
uint16_t FaBoProximity::readProxValue(void) {
  uint16_t value;
  value = readI2c(VCNL4010_PROX_VALUE);
  value <<= 8;
  value |= readI2c(VCNL4010_PROX_VALUE+1);
  return value;
}

/**
 * @brief Read Command Data
 * @return uint8_t : Ambient Light value
 */
uint16_t FaBoProximity::readAmbiValue(void) {
  uint16_t value;
  value = readI2c(VCNL4010_AMBI_VALUE);
  value <<= 8;
  value |= readI2c(VCNL4010_AMBI_VALUE+1);
  return value;
}

////////////////////////////////////////////////////////////////

/**
 * @brief Write I2C Data
 * @param [in] address : Write Register Address
 * @param [in] data    : Write Data
 */
void FaBoProximity::writeI2c(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

/**
 * @brief Read I2C Data
 * @param [in] register_addr : register address
 * @return uint8_t : Read Data
 */
uint8_t FaBoProximity::readI2c(uint8_t address) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, (uint8_t)1);
  while(!Wire.available());
  return Wire.read();
}
