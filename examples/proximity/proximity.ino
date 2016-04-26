/**
 @file proximity.ino
 @brief This is an Example for the FaBo Proximity I2C Brick.

   http://fabo.io/205.html

   Released under APACHE LICENSE, VERSION 2.0

   http://www.apache.org/licenses/

 @author FaBo<info@fabo.io>
*/

#include <Wire.h>
#include <FaBoProximity_VCNL4010.h>

FaBoProximity faboProximity;

void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();

  faboProximity.begin();
}

void loop() {
  // proximityデータの出力
  if(faboProximity.checkProxReady()){
    Serial.print("Prox:");
    Serial.println(faboProximity.readProx());
  }

  // ambientデータの出力
  if(faboProximity.checkAmbiReady()){
    Serial.print("Ambi:");
    Serial.println(faboProximity.readAmbi());
  }

  delay(1000);
}
