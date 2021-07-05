#include "motor.h"
#include "remote_control.h"

void initMotorsPinout(void){
  pinMode(EN_LEFT_MOTOR_Pin, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD_Pin, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD_Pin, OUTPUT);
  pinMode(EN_RIGHT_MOTOR_Pin, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD_Pin, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD_Pin, OUTPUT);
  stopMotors();
}

void setMotor(uint8_t motor, uint8_t dir, uint8_t pwm){
  Serial.println("motor: " + String(motor) + ", dir: " + String(dir) + ", pwm: " + String(pwm));

  if (PWM_PROFILE_VALUE == 0)
      pwm = 0;
  else if (PWM_PROFILE_VALUE == 1)
      pwm = pwm;
  else if (PWM_PROFILE_VALUE == 2)
      pwm = pwm + 60;
  else if (PWM_PROFILE_VALUE == 3)
      pwm = pwm + 80; //ajuste bateria
  else if (PWM_PROFILE_VALUE == 4)
      pwm = pwm * 2;
  else if (PWM_PROFILE_VALUE == 5)
      pwm = pwm * 3;
  
  if(pwm > 255) pwm = 255;
  if (dir == STOP_MOTOR) pwm = 0;
  
  if (motor == LEFT_MOTOR){
    if(dir == FORWARD_MOTOR){
      digitalWrite(LEFT_MOTOR_FORWARD_Pin, HIGH);
      digitalWrite(LEFT_MOTOR_BACKWARD_Pin, LOW);
      analogWrite(EN_LEFT_MOTOR_Pin, pwm);
    }
    else if(dir == BACKWARD_MOTOR){
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
    if(dir == FORWARD_MOTOR){
      digitalWrite(RIGHT_MOTOR_FORWARD_Pin, HIGH);
      digitalWrite(RIGHT_MOTOR_BACKWARD_Pin, LOW);
      analogWrite(EN_RIGHT_MOTOR_Pin, pwm);
    }
    else if(dir == BACKWARD_MOTOR){
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

void stopMotors(void){
  setMotor(BOTH_MOTOR, STOP_MOTOR, 0);
}
