/**
 * @file  FaBoProximity_VCNL4010.h
 * @brief fabo libtary of VCNL4010
 * @author Akira Sasaki
 * @date 2,10, 2016
 */
#ifndef FABOPROXIMITY_VCNL4010_H
  #define FABOPROXIMITY_VCNL4010_H

  #include <Arduino.h>
  #include <Wire.h>

  /** SLAVE_ADDRESS Register */
  #define VCNL4010_SLAVE_ADDRESS 0x13

  /** Command Register */
  #define VCNL4010_COMMAND 0x80
  /** Product ID Revision Register */
  #define VCNL4010_ID 0x81
  /** Rate of Proximity Measurement */
  #define VCNL4010_PROX_RATE 0x82
  /** LED Current Setting for Proximity Mode */
  #define VCNL4010_PROX_CURRENT 0x83
  /** ALS(Ambient Light Sensor) Parameter Register */
  #define VCNL4010_AMBI_PARAMETER 0x84
  /** ALS Result Register */
  #define VCNL4010_AMBI_VALUE 0x85
  /** Proximity Measurement Result Register */
  #define VCNL4010_PROX_VALUE 0x87
  /** Interrupt Control Register */
  #define VCNL4010_INTERRUPT_CONTROL 0x89
  /** Low Threshold */
  #define VCNL4010_INTERRUPT_LOW_THRES 0x8A
  /** High Threshold */
  #define VCNL4010_INTERRUPT_HIGH_THRES 0x8C
  /** Interrupt Status Register */
  #define VCNL4010_INTERRUPT_STATUS 0x8E
  /** Proximity Modulator Timing Adjustment */
  #define VCNL4010_PROX_TIMING 0x8F

  /** Command All Disable */
  #define VCNL4010_COMMAND_ALL_DISABLE 0x00
  /** Command Seleftimed Enable */
  #define VCNL4010_COMMAND_SELFTIMED_MODE_ENABLE 0x01
  /** Command Proximity Enable */
  #define VCNL4010_COMMAND_PROX_ENABLE 0x02
  /** Command ALS Enable */
  #define VCNL4010_COMMAND_AMBI_ENABLE 0x04
  /** Command Proximity ON-DEMAND */
  #define VCNL4010_COMMAND_PROX_ON_DEMAND 0x08
  /** Command ALS ON-DEMAND */
  #define VCNL4010_COMMAND_AMBI_ON_DEMAND 0x10
  /** Command Proximity Mask Data */
  #define VCNL4010_COMMAND_MASK_PROX_DATA_READY 0x20
  /** Command ALS Mask Data */
  #define VCNL4010_COMMAND_MASK_AMBI_DATA_READY 0x40
  /** Command ALS Mask Data */
  #define VCNL4010_COMMAND_MASK_LOCK 0x80

  /** Rate of Proximity Rate 1.95 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_2 0x00
  /** Rate of Proximity Rate 3.90625 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_4 0x01
  /** Rate of Proximity Rate 7.8125 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_8 0x02
  /** Rate of Proximity Rate 16.625 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_16 0x03
  /** Rate of Proximity Rate 31.25 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_31 0x04
  /** Rate of Proximity Rate 62.5 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_62 0x05
  /** Rate of Proximity Rate 125 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_125 0x06
  /** Rate of Proximity Rate 250 */
  #define VCNL4010_PROX_MEASUREMENT_RATE_250 0x07
  /** Rate of Proximity Rate Mask */
  #define VCNL4010_PROX_MASK_MEASUREMENT_RATE 0x07

  /** ALS Parameter Average 1 */
  #define VCNL4010_AMBI_PARA_AVERAGE_1 0x00
  /** ALS Parameter Average 2 */
  #define VCNL4010_AMBI_PARA_AVERAGE_2 0x01
  /** ALS Parameter Average 4 */
  #define VCNL4010_AMBI_PARA_AVERAGE_4 0x02
  /** ALS Parameter Average 8 */
  #define VCNL4010_AMBI_PARA_AVERAGE_8 0x03
  /** ALS Parameter Average 16 */
  #define VCNL4010_AMBI_PARA_AVERAGE_16 0x04
  /** ALS Parameter Average 32 */
  #define VCNL4010_AMBI_PARA_AVERAGE_32 0x05
  /** ALS Parameter Average 64 */
  #define VCNL4010_AMBI_PARA_AVERAGE_64 0x06
  /** ALS Parameter Average 128 */
  #define VCNL4010_AMBI_PARA_AVERAGE_128 0x07
  /** ALS Parameter Average MASK */
  #define VCNL4010_AMBI_MASK_PARA_AVERAGE 0x07
  /** ALS Parameter OFFSET enable */
  #define VCNL4010_AMBI_PARA_AUTO_OFFSET_ENABLE 0x08
  /** ALS Parameter OFFSET MASK */
  #define VCNL4010_AMBI_MASK_PARA_AUTO_OFFSET 0x08
  /** ALS Parameter Measurement Rate 1 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_1 0x00
  /** ALS Parameter Measurement Rate 2 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_2 0x10
  /** ALS Parameter Measurement Rate 3 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_3 0x20
  /** ALS Parameter Measurement Rate 4 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_4 0x30
  /** ALS Parameter Measurement Rate 5 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_5 0x40
  /** ALS Parameter Measurement Rate 6 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_6 0x50
  /** ALS Parameter Measurement Rate 8 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_8 0x60
  /** ALS Parameter Measurement Rate 10 */
  #define VCNL4010_AMBI_PARA_MEAS_RATE_10 0x70
  /** ALS Parameter Measurement Rate MASK */
  #define VCNL4010_AMBI_MASK_PARA_MEAS_RATE 0x70
  /** ALS Parameter Continuous conversions Enable */
  #define VCNL4010_AMBI_PARA_CONT_CONV_ENABLE 0x80
  /** ALS Parameter Continuous conversions MASK */
  #define VCNL4010_AMBI_MASK_PARA_CONT_CONV 0x80

  /** Interrupt Threshold Proximity */
  #define VCNL4010_INTERRUPT_THRES_SEL_PROX 0x00
  /** Interrupt Threshold ALS */
  #define VCNL4010_INTERRUPT_THRES_SEL_ALS 0x01
  /** Interrupt Threshold Enable */
  #define VCNL4010_INTERRUPT_THRES_ENABLE 0x02
  /** Interrupt Threshold ALS Ready Enable */
  #define VCNL4010_INTERRUPT_ALS_READY_ENABLE 0x04
  /** Interrupt Threshold Proximity Ready Enable */
  #define VCNL4010_INTERRUPT_PROX_READY_ENABLE 0x08
  /** Interrupt count exceed 1 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_1 0x00
  /** Interrupt count exceed 2 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_2 0x20
  /** Interrupt count exceed 4 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_4 0x40
  /** Interrupt count exceed 8 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_8 0x60
  /** Interrupt count exceed 16 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_16 0x80
  /** Interrupt count exceed 32 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_32 0xa0
  /** Interrupt count exceed 64 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_64 0xc0
  /** Interrupt count exceed 128 */
  #define VCNL4010_INTERRUPT_COUNT_EXCEED_128 0xe0
  /** Interrupt count exceed MASK */
  #define VCNL4010_INTERRUPT_MASK_COUNT_EXCEED 0xe0
  /** Interrupt Status threshold HIGH */
  #define VCNL4010_INTERRUPT_STATUS_THRES_HI 0x01
  /** Interrupt Status threshold LOW */
  #define VCNL4010_INTERRUPT_STATUS_THRES_LO 0x02
  /** Interrupt Threshold Status ALS Ready Enable */
  #define VCNL4010_INTERRUPT_STATUS_ALS_READY 0x04
  /** Interrupt Threshold Status Proximity Ready Enable */
  #define VCNL4010_INTERRUPT_STATUS_PROX_READY 0x08
  /** Interrupt Status threshold HIGH MASK */
  #define VCNL4010_INTERRUPT_MASK_STATUS_THRES_HI 0x01
  /** Interrupt Status threshold LOW MASK */
  #define VCNL4010_INTERRUPT_MASK_THRES_LO 0x02
  /** Interrupt ALS Ready */
  #define VCNL4010_INTERRUPT_MASK_ALS_READY 0x04
  /** Interrupt Proximity Ready */
  #define VCNL4010_INTERRUPT_MASK_PROX_READY 0x08

  /**
   * @class FaBoProximity
   * @brief VCNL4010 Control
   */
  class FaBoProximity {
    public:
      FaBoProximity(uint8_t addr = VCNL4010_SLAVE_ADDRESS);
      bool searchDevice(void);
      uint8_t readId();
      void configuration(void);
      void setCurrent(uint8_t current);
      uint8_t readCurrent();
      void setCommand(uint8_t command);
      uint8_t readCommand(void);
      void setProxRate(uint8_t rate);
      void setAmbiConfig(uint8_t config);
      bool isProxDataReady(void);
      bool isAmbiDataReady(void);
      uint16_t readProxValue(void);
      uint16_t readAmbiValue(void);
    private:
      /** set VCNL4010 Devise address*/
      uint8_t _i2caddr;
      void writeI2c(uint8_t address, uint8_t data);
      uint8_t readI2c(uint8_t address);
  };

#endif // FABOPROXIMITY_VCNL4010_H
