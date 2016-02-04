//
// FaBo Brick Example
//
// FaBo Proximity VCNL4010
//

#include <Wire.h>
#include <FaBoProximity_VCNL4010.h>

FaBoProximity_VCNL4010 fabo_proximity;

void setup() {
  Serial.begin(9600); // シリアルの開始

  Serial.println("Checking I2C device...");
  // I2Cデバイスチェック
  if (fabo_proximity.checkDevice()) {
    Serial.println("VCNL4010: Device found");
  } else {
    Serial.println("Device not found");
    while(1);
  }

  // デバイス初期化
  fabo_proximity.setupDevice();
}

void loop() {
  // proximityデータの出力
  if ( fabo_proximity.isProxDataReady() ) {
    Serial.print("Proximity(cts): ");
    Serial.println(fabo_proximity.readProxValue());
  }

  // ambientデータの出力
  if ( fabo_proximity.isAmbiDataReady() ) {
    Serial.print("Ambi: ");
    Serial.println(fabo_proximity.readAmbiValue());
  }

  delay(1000);
}
