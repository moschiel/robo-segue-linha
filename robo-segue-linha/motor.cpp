#include "motor.h"
void initMotorsPinout(void){
  pinMode(EN_LEFT_MOTOR_Pin, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD_Pin, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_Pin, OUTPUT);
  pinMode(EN_RIGHT_MOTOR_Pin, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_Pin, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_Pin, OUTPUT);
}

void setMotor(uint8_t motor, uint8_t dir, uint8_t pwm){
  if (motor == LEFT_MOTOR){
    if(dir == FORWARD){
      digitalWrite(LEFT_MOTOR_FORWARD_Pin, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD_Pin, LOW);
      analogWrite(EN_LEFT_MOTOR_Pin, pwm);
    }
    else if(dir == BACKWARD){
      digitalWrite(LEFT_MOTOR_FORWARD_Pin, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD_Pin, HIGH);
      analogWrite(EN_LEFT_MOTOR_Pin, pwm);
    }
    else { //stop
      digitalWrite(LEFT_MOTOR_FORWARD_Pin, LOW);
      digitalWrite(LEFT_MOTOR_BACKWARD_Pin, LOW);
      digitalWrite(EN_LEFT_MOTOR_Pin, LOW);
    }
  }
  else if (motor == RIGHT_MOTOR){
    if(dir == FORWARD){
      digitalWrite(RIGHT_MOTOR_FORWARD_Pin, HIGH);
      digitalWrite(RIGHT_MOTOR_BACKWARD_Pin, LOW);
      analogWrite(EN_RIGHT_MOTOR_Pin, pwm);
    }
    else if(dir == BACKWARD){
      digitalWrite(RIGHT_MOTOR_FORWARD_Pin, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD_Pin, HIGH);
      analogWrite(EN_RIGHT_MOTOR_Pin, pwm);
    }
    else { //stop
      digitalWrite(RIGHT_MOTOR_FORWARD_Pin, LOW);
      digitalWrite(RIGHT_MOTOR_BACKWARD_Pin, LOW);
      digitalWrite(EN_RIGHT_MOTOR_Pin, LOW);
    }
  }
  else { //BOTH_MOTOR
    setMotor(LEFT_MOTOR, dir, pwm);
    setMotor(RIGHT_MOTOR, dir, pwm);
  }
}
