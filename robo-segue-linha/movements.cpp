#include "movements.h"
#include "motor.h"

String strMoves[] = {
  "PARE",
  "FRENTE",
  "RÉ",
  "GIRO LEVE ESQUERDA",
  "GIRO MEDIO ESQUERDA",
  "GIRO FORTE ESQUERDA",
  "GIRO TOTAL ESQUERDA",
  "GIRO LEVE DIREITA",
  "GIRO MEDIO DIREITA",
  "GIRO FORTE DIREITA",
  "GIRO TOTAL DIREITA"
};

void setMovement(MOVEMENTS movement){
  static int lastMove = -1;
  
  switch(movement){
    case MOV_STOP:
      stopMotors();
      break; 
      
    case MOV_FORWARD:
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 55);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 70);
      break;
    case MOV_BACKWARD:
      setMotor(LEFT_MOTOR, BACKWARD_MOTOR, 55);
      setMotor(RIGHT_MOTOR, BACKWARD_MOTOR, 70);
      break; 
      
    case MOV_TURN_LEFT_WEAK:
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 50);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 75);
      break;
    case MOV_TURN_LEFT_MEDIUM:      
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 50);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 80);
      break;
    case MOV_TURN_LEFT_HARD:    
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 50);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 90);
      break;
    case MOV_TURN_LEFT_TOTAL:    
      setMotor(LEFT_MOTOR, BACKWARD_MOTOR, 50);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 60);
      break;
      
    case MOV_TURN_RIGHT_WEAK:
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 50);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 50);
      break;
    case MOV_TURN_RIGHT_MEDIUM:      
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 60);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 50);
      break;
    case MOV_TURN_RIGHT_HARD:    
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 75);
      setMotor(RIGHT_MOTOR, FORWARD_MOTOR, 50);
      break;
    case MOV_TURN_RIGHT_TOTAL:    
      setMotor(LEFT_MOTOR, FORWARD_MOTOR, 50);
      setMotor(RIGHT_MOTOR, BACKWARD_MOTOR, 65);
      break;

    default:
      stopMotors();
  }
}
