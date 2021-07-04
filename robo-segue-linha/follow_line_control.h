#include <Arduino.h>

enum CONTROL_DIRECTIONS {
  CTRL_FORWARD,
  CTRL_BACKWARDS,
  CTRL_LEFT,
  CTRL_RIGHT,
  CTRL_STOP
};

void initFollowLineControlPinout(void);
void followLineControl(void);
bool searchLineAround(CONTROL_DIRECTIONS lastDirection);
