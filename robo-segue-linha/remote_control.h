#include <Arduino.h>

#define BTN_MAIS  0x15
#define BTN_MENOS 0x07
#define BTN_EQ    0x09
#define BTN_0 0x16
#define BTN_1 0x0C
#define BTN_2 0x18
#define BTN_3 0x5E
#define BTN_4 0x08
#define BTN_5 0x1C
#define BTN_6 0x5A
#define BTN_7 0x42
#define BTN_8 0x52
#define BTN_9 0x4A

extern uint8_t PWM_PROFILE_VALUE;
extern bool MANUAL_MODE;

void initRemotePinout();
void readRemoteControl();
