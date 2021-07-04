#include "motor.h"

void setup() {
  // put your setup code here, to run once:


  initMotorsPinout();
  //while(1);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  setMotor(BOTH_MOTOR, FORWARD, 70);
  //setMotor(RIGHT_MOTOR, FORWARD, 70); 
}
