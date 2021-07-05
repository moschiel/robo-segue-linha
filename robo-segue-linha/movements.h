#include <Arduino.h>

enum MOVEMENTS {
  MOV_STOP,                 //para
  MOV_FORWARD,              //frente
  MOV_BACKWARD,              //frente
  MOV_TURN_LEFT_WEAK,       //giro leve a esqueda
  MOV_TURN_LEFT_MEDIUM,     //giro medio a esquerda
  MOV_TURN_LEFT_HARD,       //giro forte a esquerda
  MOV_TURN_LEFT_TOTAL,       //giro total a esquerda
  MOV_TURN_RIGHT_WEAK,      //giro leve a direita
  MOV_TURN_RIGHT_MEDIUM,    //giro medio a direita
  MOV_TURN_RIGHT_HARD,      //giro forte a direita
  MOV_TURN_RIGHT_TOTAL      //giro total a direita
};

extern String strMoves[];


void setMovement(MOVEMENTS movement);
