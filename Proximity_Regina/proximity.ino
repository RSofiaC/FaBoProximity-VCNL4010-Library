#include <FaBoProximity_VCNL4010.h> //THE SENSOR'S LIBRARY
#include <Wire.h> // This library allows you to communicate with I2C / TWI devices.

FaBoProximity faboProximity; 
int sensorValue;
int mappedValue;
const int fanPin = 10; //WHERE THE OUTPUT IS ATTACHED
void setup() {
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();

  faboProximity.begin();
}

void loop() {
  // proximity
  if(faboProximity.checkProxReady()){
  sensorValue = faboProximity.readProx();
  Serial.print("Prox:");
  Serial.println(faboProximity.readProx());
  }

  mappedValue = map(sensorValue,1800,34000,0,255); //THIS MAPPING WORKS BUT WHY IS IT SO HIGH? HOW DO I READ MY SENSOR'S SPECS TO KNOW THIS?
  Serial.println(mappedValue);

 analogWrite(fanPin, mappedValue); //IT LOOKS LIKE PROXIMITY STARTS A LOOP

// TO USE THE SENSOR AS A DIGITAL SWICH
// if(mappedValue>2){
// analogWrite(fanPin, 255); }
// else {
// analogWrite(fanPin, 0);}

  // ambient DONT KNOW IF I NEED THIS AND FOR WHAT
  if(faboProximity.checkAmbiReady()){
  Serial.print("Ambi:");
  Serial.println(faboProximity.readAmbi());
  }

 //delay(1000);
}
