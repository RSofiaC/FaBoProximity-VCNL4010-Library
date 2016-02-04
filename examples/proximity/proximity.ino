#include <Wire.h>
#include <FaBoProximity_VCNL4010.h>

FaBoProximity_VCNL4010 fabo_proximity;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("RESET");
  Serial.println();

  Serial.println("Checking I2C device...");
  if (fabo_proximity.checkDevice()) {
    Serial.println("VCNL4010: Device found");
  } else {
    Serial.println("Device not found");
    while(1);
  }

  fabo_proximity.setupDevice();
}

void loop() {
  if ( fabo_proximity.isProxDataReady() ) {
    Serial.print("Proximity(cts): ");
    Serial.println(fabo_proximity.readProxValue());
  }

  if ( fabo_proximity.isAmbiDataReady() ) {
    Serial.print("Ambi: ");
    Serial.println(fabo_proximity.readAmbiValue());
  }

  delay(1000);
}
