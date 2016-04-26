/**
 @file FaBoProximity_VCNL4010.cpp
 @brief This is a library for the FaBo Proximity I2C Brick.

   http://fabo.io/205.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include "FaBoProximity_VCNL4010.h"

/**
 @brief Constructor
*/
FaBoProximity::FaBoProximity(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();
}

/**
 @brief Begin Device
 @retval true normaly done
 @retval false device error
*/
bool FaBoProximity::begin() {
  if ( searchDevice() ) {
    configuration();
    return true;
  } else {
    return false;
  }
}

/**
 @brief Search Device
 @retval true device connected
 @retval false device error
*/
bool FaBoProximity::searchDevice() {
  if ( readI2c(VCNL4010_REG_ID) == VCNL4010_DEVICE_ID ) {
    return true;
  } else {
    return false;
  }
}

/**
 @brief Configure Device
*/
void FaBoProximity::configuration() {
  setCommand(
    VCNL4010_CMD_SELFTIMED_EN |
    VCNL4010_CMD_PROX_EN |
    VCNL4010_CMD_ALS_EN );
  setProxRate(VCNL4010_PROX_RATE_250);
  setLedCurrent(20);
  setAmbiParm(
    VCNL4010_AMBI_RATE_10 |
    VCNL4010_AMBI_AUTO_OFFSET |
    VCNL4010_AMBI_AVE_NUM_128 );
}

/**
 @brief Set Command Register
 @param [in] config Configure Parameter
*/
void FaBoProximity::setCommand(uint8_t config) {
  writeI2c(VCNL4010_REG_CMD, config);
}

/**
 @brief Proximity Rate Register Setting
 @param [in] config Configure Parameter
*/
void FaBoProximity::setProxRate(uint8_t config) {
  writeI2c(VCNL4010_REG_PROX_RATE, config);
}

/**
 @brief IR LED Current Setting
 @param [in] config Configure Parameter
*/
void FaBoProximity::setLedCurrent(uint8_t config) {
  writeI2c(VCNL4010_REG_LED_CRNT, config);
}

/**
 @brief Ambient Light Parameter Register Setting
 @param [in] config Configure Parameter
*/
void FaBoProximity::setAmbiParm(uint8_t config) {
  writeI2c(VCNL4010_REG_AMBI_PARM, config);
}

/**
 @brief Check Proximity Data Ready
 @retval true Data is Ready
 @retval false Data is Not Ready
*/
bool FaBoProximity::checkProxReady() {
  if ( readI2c(VCNL4010_REG_CMD) & VCNL4010_CMD_PROX_DRDY ) {
    return true;
  }
  return false;
}

/**
 @brief Check Ambient Light Data Ready
 @retval true Data is Ready
 @retval false Data is Not Ready
*/
bool FaBoProximity::checkAmbiReady() {
  if ( readI2c(VCNL4010_REG_CMD) & VCNL4010_CMD_ALS_DRDY ) {
    return true;
  }
  return false;
}

/**
 @brief Read Proximity Data
 @param [out] value Proximity Data
*/
uint16_t FaBoProximity::readProx() {
  uint16_t value;
  value = readI2c(VCNL4010_REG_PROX_DATA_H);
  value <<= 8;
  value |= readI2c(VCNL4010_REG_PROX_DATA_L);
  return value;
}

/**
 @brief Read Ambient Light Data
 @param [out] value Ambient Light Data
*/
uint16_t FaBoProximity::readAmbi() {
  uint16_t value;
  value = readI2c(VCNL4010_REG_AMBI_DATA_H);
  value <<= 8;
  value |= readI2c(VCNL4010_REG_AMBI_DATA_L);
  return value;
}


void FaBoProximity::dumpReg() {
  uint8_t data;
  int i;
  for (i=0x80;i<=0x90;i++){
    Serial.print("0x");
    Serial.print(i, HEX);
    Serial.print(": ");
    data = readI2c(i);
    print_byte(data);
    Serial.println("");
  }
}

void FaBoProximity::print_byte(uint8_t val) {
  int i;
  Serial.print("B");
  for(i=7; i>=0; i--){
    Serial.print(val >> i & 1, BIN);
  }
}



/**
 @brief Write I2C
 @param [in] address register address
 @param [in] data write data
*/
void FaBoProximity::writeI2c(uint8_t address, uint8_t data) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

/**
 @brief Read I2C
 @param [in] address register address
 @param [out] data read data
*/
uint8_t FaBoProximity::readI2c(uint8_t address) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, (uint8_t)1);
  while(!Wire.available());
  return Wire.read();
}
