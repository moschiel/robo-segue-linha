#include "motor.h"
#include "follow_line_control.h"
#include "remote_control.h"


void setup() {
  // put your setup code here, to run once:
  initMotorsPinout();
  initFollowLineControlPinout();
  initRemotePinout();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(String(digitalRead(A0)) + ", " + digitalRead(A1) + ", " + digitalRead(A2));
  if(MANUAL_MODE)
    readRemoteControl();
  else
    followLineControl();
}
