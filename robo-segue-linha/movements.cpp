#include "movements.h"
#include "motor.h"

String strMoves[] = {
  "PARE",
  "FRENTE",
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
      setMotor(LEFT_MOTOR, FORWARD, 55);
      setMotor(RIGHT_MOTOR, FORWARD, 70);
      break; 
      
    case MOV_TURN_LEFT_WEAK:
      setMotor(LEFT_MOTOR, FORWARD, 50);
      setMotor(RIGHT_MOTOR, FORWARD, 75);
      break;
    case MOV_TURN_LEFT_MEDIUM:      
      setMotor(LEFT_MOTOR, FORWARD, 50);
      setMotor(RIGHT_MOTOR, FORWARD, 80);
      break;
    case MOV_TURN_LEFT_HARD:    
      setMotor(LEFT_MOTOR, FORWARD, 50);
      setMotor(RIGHT_MOTOR, FORWARD, 90);
      break;
    case MOV_TURN_LEFT_TOTAL:    
      setMotor(LEFT_MOTOR, BACKWARD, 50);
      setMotor(RIGHT_MOTOR, FORWARD, 60);
      break;
      
    case MOV_TURN_RIGHT_WEAK:
      setMotor(LEFT_MOTOR, FORWARD, 50);
      setMotor(RIGHT_MOTOR, FORWARD, 50);
      break;
    case MOV_TURN_RIGHT_MEDIUM:      
      setMotor(LEFT_MOTOR, FORWARD, 60);
      setMotor(RIGHT_MOTOR, FORWARD, 50);
      break;
    case MOV_TURN_RIGHT_HARD:    
      setMotor(LEFT_MOTOR, FORWARD, 75);
      setMotor(RIGHT_MOTOR, FORWARD, 50);
      break;
    case MOV_TURN_RIGHT_TOTAL:    
      setMotor(LEFT_MOTOR, FORWARD, 50);
      setMotor(RIGHT_MOTOR, BACKWARD, 65);
      break;
  }
}
