#include "remote_control.h"
#include <IRremote.h>  
#include <EEPROM.h>
#include "movements.h"

int RECV_PIN = 11;  
float armazenavalor;  
 
//valores manipulados remotamente
#define PWM_PROFILE_ADDR 0
#define PWM_PROFILE_MAX 5  // 0 á 5
#define PWM_PROFILE_DEFAULT 2
uint8_t PWM_PROFILE_VALUE; //%
bool MANUAL_MODE = false;

void initRemotePinout()  
{  
  IrReceiver.begin(RECV_PIN);  
  //init memory values
  PWM_PROFILE_VALUE = EEPROM.read(PWM_PROFILE_ADDR);
  if(PWM_PROFILE_VALUE > PWM_PROFILE_MAX)
    PWM_PROFILE_VALUE = PWM_PROFILE_DEFAULT;
}  

unsigned long int IrMillis;

void readRemoteControl() {
  static unsigned long int lastIrMillis = millis();
  IrMillis = millis();
  if((IrMillis - lastIrMillis) < 200) 
    return;
  lastIrMillis = IrMillis;
  
  
  if (IrReceiver.decode()) 
  {
    // Print a short summary of received data
    //IrReceiver.printIRResultShort(&Serial);
    Serial.print("Valor lido : ");  
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    

    switch(IrReceiver.decodedIRData.command){
      case BTN_MAIS:
        if(PWM_PROFILE_VALUE < PWM_PROFILE_MAX){
          PWM_PROFILE_VALUE++;
          EEPROM.write(PWM_PROFILE_ADDR, PWM_PROFILE_VALUE);
          Serial.println("PWM_PROFILE_VALUE: " + String(PWM_PROFILE_VALUE));
        }
        break;
      case BTN_MENOS:
        if(PWM_PROFILE_VALUE > 0){
          PWM_PROFILE_VALUE--;
          EEPROM.write(PWM_PROFILE_ADDR, PWM_PROFILE_VALUE);
          Serial.println("PWM_PROFILE_VALUE: " + String(PWM_PROFILE_VALUE));
        };
        break;
      case BTN_EQ:
        MANUAL_MODE = !MANUAL_MODE;
        Serial.println("MANUAL MODE: " + String(MANUAL_MODE));
        break;
      case BTN_2:
        if(MANUAL_MODE) 
          setMovement(MOV_FORWARD);
        break;
      case BTN_8:
        if(MANUAL_MODE) 
          setMovement(MOV_BACKWARD);
        break;
      case BTN_4:
        if(MANUAL_MODE) 
          setMovement(MOV_TURN_LEFT_TOTAL);
        break;
      case BTN_6:
        if(MANUAL_MODE) 
          setMovement(MOV_TURN_RIGHT_TOTAL);
        break;
    }

    IrReceiver.resume(); //habilita leitura do proximo valor  
  }
  else if (MANUAL_MODE) {
    setMovement(MOV_STOP);
  }
}
