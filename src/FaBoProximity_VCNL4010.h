/**
 @file FaBoProximity_VCNL4010.h
 @brief This is a library for the FaBo Proximity I2C Brick.

   http://fabo.io/205.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#ifndef FABOPROXIMITY_VCNL4010_H
#define FABOPROXIMITY_VCNL4010_H

#include <Arduino.h>
#include <Wire.h>

#define VCNL4010_SLAVE_ADDRESS 0x13 ///< I2C Slave Address
#define VCNL4010_DEVICE_ID 0x21 ///< Product,Revision ID Value

/// @name Register Addresses
/// @{
#define VCNL4010_REG_CMD 0x80
#define VCNL4010_REG_ID 0x81
#define VCNL4010_REG_PROX_RATE 0x82
#define VCNL4010_REG_LED_CRNT 0x83
#define VCNL4010_REG_AMBI_PARM 0x84
#define VCNL4010_REG_AMBI_DATA_H 0x85
#define VCNL4010_REG_AMBI_DATA_L 0x86
#define VCNL4010_REG_PROX_DATA_H 0x87
#define VCNL4010_REG_PROX_DATA_L 0x88
#define VCNL4010_REG_INT_CTRL 0x89
#define VCNL4010_REG_INT_LOW_H 0x8A
#define VCNL4010_REG_INT_LOW_L 0x8B
#define VCNL4010_REG_INT_HIGH_H 0x8C
#define VCNL4010_REG_INT_HIGH_H 0x8D
#define VCNL4010_REG_INT_STAT 0x8E
#define VCNL4010_REG_PROX_ADJ 0x8F
/// @}

/// @name Commands
/// @{
#define VCNL4010_CMD_SELFTIMED_EN 0x01
#define VCNL4010_CMD_PROX_EN 0x02
#define VCNL4010_CMD_ALS_EN 0x04
#define VCNL4010_CMD_PROX_OD 0x08
#define VCNL4010_CMD_ALS_OD 0x10
#define VCNL4010_CMD_PROX_DRDY 0x20
#define VCNL4010_CMD_ALS_DRDY 0x40
/// @}

/// @name Proximity Measurement Rate
/// @{
#define VCNL4010_PROX_RATE_1   0x00
#define VCNL4010_PROX_RATE_3   0x01
#define VCNL4010_PROX_RATE_7   0x02
#define VCNL4010_PROX_RATE_16  0x03
#define VCNL4010_PROX_RATE_31  0x04
#define VCNL4010_PROX_RATE_62  0x05
#define VCNL4010_PROX_RATE_125 0x06
#define VCNL4010_PROX_RATE_250 0x07
/// @}

/// @name Ambient Light Parameter
/// @{
#define VCNL4010_AMBI_CONT_CONV_MODE 0x80
#define VCNL4010_AMBI_RATE_1  0x00
#define VCNL4010_AMBI_RATE_2  0x10
#define VCNL4010_AMBI_RATE_3  0x20
#define VCNL4010_AMBI_RATE_4  0x30
#define VCNL4010_AMBI_RATE_5  0x40
#define VCNL4010_AMBI_RATE_6  0x50
#define VCNL4010_AMBI_RATE_8  0x60
#define VCNL4010_AMBI_RATE_10 0x70
#define VCNL4010_AMBI_AUTO_OFFSET 0x08
#define VCNL4010_AMBI_AVE_NUM_1   0x00
#define VCNL4010_AMBI_AVE_NUM_2   0x01
#define VCNL4010_AMBI_AVE_NUM_4   0x02
#define VCNL4010_AMBI_AVE_NUM_8   0x03
#define VCNL4010_AMBI_AVE_NUM_16  0x04
#define VCNL4010_AMBI_AVE_NUM_32  0x05
#define VCNL4010_AMBI_AVE_NUM_64  0x06
#define VCNL4010_AMBI_AVE_NUM_128 0x07
/// @}


/**
 @class FaBoProximity
 @brief FaBo Proximity I2C Controll class
*/
class FaBoProximity {
  public:
    FaBoProximity(uint8_t addr = VCNL4010_SLAVE_ADDRESS);
    bool begin(void);
    bool searchDevice(void);
    void configuration(void);
    void setCommand(uint8_t config);
    void setProxRate(uint8_t config);
    void setLedCurrent(uint8_t config);
    void setAmbiParm(uint8_t config);
    bool checkProxReady(void);
    bool checkAmbiReady(void);
    uint16_t readProx(void);
    uint16_t readAmbi(void);
    void dumpReg(void);
  private:
    uint8_t _i2caddr;
    void writeI2c(uint8_t address, uint8_t data);
    uint8_t readI2c(uint8_t address);
    void print_byte(uint8_t val);
};

#endif // FABOPROXIMITY_VCNL4010_H
