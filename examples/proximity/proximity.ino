//
// FaBo Brick Example
//
// FaBo Proximity VCNL4010
//

#include <Wire.h>
#include <FaBoProximity_VCNL4010.h>

FaBoProximity faboProximity;

void setup() {
  Serial.begin(9600); // シリアルの開始

  Serial.println("Checking I2C device...");
  // I2Cデバイスチェック
  if (faboProximity.searchDevice()) {
    Serial.println("VCNL4010: Device found");
  } else {
    Serial.println("Device not found");
    while(1);
  }

  // デバイス初期化
  faboProximity.configuration();
}

void loop() {
  // proximityデータの出力
  if ( faboProximity.isProxDataReady() ) {
    Serial.print("Proximity(cts): ");
    Serial.println(faboProximity.readProxValue());
  }

  // ambientデータの出力
  if ( faboProximity.isAmbiDataReady() ) {
    Serial.print("Ambi: ");
    Serial.println(faboProximity.readAmbiValue());
  }

  delay(1000);
}
