#include <Arduino.h>

#define EN_LEFT_MOTOR_Pin         10  //PWM
#define LEFT_MOTOR_FORWARD_Pin    9   //digital
#define LEFT_MOTOR_BACKWARD_Pin   8   //digital
#define EN_RIGHT_MOTOR_Pin        5   //PWM
#define RIGHT_MOTOR_FORWARD_Pin   6   //digital
#define RIGHT_MOTOR_BACKWARD_Pin  7   //digital

enum MOTORS {
  LEFT_MOTOR,
  RIGHT_MOTOR,
  BOTH_MOTOR
};
enum MOTORS_DIRECTION {
  FORWARD,
  BACKWARD,
  STOP
};

void initMotorsPinout(void);
void setMotor(uint8_t motor, uint8_t dir, uint8_t pwm);
void stopMotors(void);
