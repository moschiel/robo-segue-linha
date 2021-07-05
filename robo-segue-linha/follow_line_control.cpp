#include "follow_line_control.h"
#include "movements.h"
#include "ultrasom.h"
#include "remote_control.h"

#define LINE_RIGHT_Pin A0
#define LINE_CENTRAL_Pin A1
#define LINE_LEFT_Pin A2

#define LINE_SENSORS_DEBOUNCE 5//ms  //leve em conta q o debounce do ultrasom é cravado 12ms

#define INVALID -1

#define DISTANCE_STOP 20.0 //centimeters

struct LineSensors {
  bool Left_IN;     //IN = dentro da faixa
  bool Left_OUT;    //OUT = fora da faixa
  bool Central_IN;
  bool Central_OUT;
  bool Right_IN;
  bool Right_OUT;
};



LineSensors lineSensors;
bool flagObstacle = false;

void initFollowLineControlPinout(void){
  pinMode(LINE_LEFT_Pin, INPUT);
  pinMode(LINE_CENTRAL_Pin, INPUT);
  pinMode(LINE_RIGHT_Pin, INPUT);
}

bool thereIsObstacle() {
  static bool auxFlagObstacle = false;
  float dist = getUltrasomDistanceInCM();
  if(dist < DISTANCE_STOP){
    setMovement(MOV_STOP);
    flagObstacle = true;
  }else {
    flagObstacle = false;
  }

  if(auxFlagObstacle != flagObstacle){
    auxFlagObstacle = flagObstacle;
    if(flagObstacle) Serial.println("Obstaculo encontrado: " + String(dist) + " cm");
    else Serial.println("Obstaculo removido");
  }
  return flagObstacle;
}

void debounceSensorsLine(void) {
  int auxLeft = 0;
  int auxCentral = 0;
  int auxRight = 0;
  
  auxLeft = digitalRead(LINE_LEFT_Pin);
  auxCentral = digitalRead(LINE_CENTRAL_Pin);
  auxRight = digitalRead(LINE_RIGHT_Pin);
  
  delay(LINE_SENSORS_DEBOUNCE);  
  
  if(auxLeft == digitalRead(LINE_LEFT_Pin)) lineSensors.Left_IN = auxLeft;
  if(auxCentral == digitalRead(LINE_CENTRAL_Pin)) lineSensors.Central_IN = auxCentral;
  if(auxRight == digitalRead(LINE_RIGHT_Pin)) lineSensors.Right_IN = auxRight;

  lineSensors.Left_OUT = !lineSensors.Left_IN;
  lineSensors.Central_OUT = !lineSensors.Central_IN;
  lineSensors.Right_OUT = !lineSensors.Right_IN;

  readRemoteControl();//como essa funcao ta sempre rodando, coloquei aqui a leitura do controle

}

void waitAllSensors(){
  Serial.println("Move*: " + strMoves[MOV_STOP]);
  Serial.println("Aguardando todos sensores na faixa...");
  setMovement(MOV_STOP);
  debounceSensorsLine();
  while((lineSensors.Left_OUT || lineSensors.Central_OUT || lineSensors.Right_OUT) && !thereIsObstacle()){
    debounceSensorsLine();
    delay(2000);
    if(MANUAL_MODE) return;
  }  
}
void waitAnySensor(){
  Serial.println("Move*: " + strMoves[MOV_STOP]);
  Serial.println("Aguardando qualquer sensor na faixa...");
  setMovement(MOV_STOP);
  debounceSensorsLine();
  while(lineSensors.Left_OUT && lineSensors.Central_OUT && lineSensors.Right_OUT && !thereIsObstacle()){
    debounceSensorsLine();
    delay(2000);
    if(MANUAL_MODE) return;
  }  
}


void followLineControl(void) {
  static bool firstTime = true;
  static MOVEMENTS lastMove = INVALID; //usado apenas pra controlar excesso de Serial.println
  static CONTROL_DIRECTIONS lastDirection = INVALID; //usado para tentar voltar a faixa se sair totalmente
  MOVEMENTS movement = INVALID;
  
  debounceSensorsLine();
  
  if(thereIsObstacle()) { //tem obstaculo, fica parado e reseta variaveis
    lastMove = INVALID;
    lastDirection = INVALID;
    return;
  }
  
  if(firstTime){ //se primeira vez
    firstTime = false;
    waitAnySensor(); 
  }

  if(lineSensors.Left_IN && lineSensors.Central_IN && lineSensors.Right_IN) {
    movement = MOV_FORWARD;
    lastDirection = CTRL_FORWARD;
  }
  else if(lineSensors.Left_OUT && lineSensors.Central_IN && lineSensors.Right_IN) {
    movement = MOV_TURN_RIGHT_MEDIUM;
    lastDirection = CTRL_RIGHT;
  }
  else if(lineSensors.Left_OUT && lineSensors.Central_OUT && lineSensors.Right_IN) {
    movement = MOV_TURN_RIGHT_HARD;
    lastDirection = CTRL_RIGHT;
  }
  else if(lineSensors.Left_IN && lineSensors.Central_IN && lineSensors.Right_OUT){
    movement = MOV_TURN_LEFT_MEDIUM;
    lastDirection = CTRL_LEFT;
  }
  else if(lineSensors.Left_IN && lineSensors.Central_OUT && lineSensors.Right_OUT){
    movement = MOV_TURN_LEFT_HARD;
    lastDirection = CTRL_LEFT;
  }
  else if(lineSensors.Left_OUT && lineSensors.Central_OUT && lineSensors.Right_OUT){ // todos OUT
    //tenta voltar pra faixa baseado na ultima decisao
    if(searchLineAround(lastDirection) == false) {
      lastMove = MOV_STOP;
      lastDirection = CTRL_STOP;
      waitAnySensor(); //nao encontramos nada, entamos ficamos parado esperando o sensor
    }
    return;
  }

  if(movement != INVALID)
    setMovement(movement);

  if(movement != lastMove){
    lastMove = movement;
    Serial.println("Move: " + strMoves[movement]);
  }
}

bool searchLineAround(CONTROL_DIRECTIONS lastDirection){
  MOVEMENTS movement = INVALID;
  
  if(lastDirection == CTRL_RIGHT) {
     movement = MOV_TURN_RIGHT_TOTAL;
  }
  else if(lastDirection == CTRL_LEFT) {
    movement = MOV_TURN_LEFT_TOTAL;
  }
  else { //se era forward ou backward, nao tem como saber a direcao, então a gente so vira pra um lado qualquer pra ver se acha a faixa, nao ideal
    movement = MOV_TURN_LEFT_TOTAL;
  }

  setMovement(movement);
  Serial.println("Procurando algum sensor...");
  Serial.println("Move**: " + strMoves[movement]);
  

  unsigned long searchMillis = millis();
  while(lineSensors.Left_OUT && lineSensors.Central_OUT && lineSensors.Right_OUT){
      debounceSensorsLine();

      if(thereIsObstacle()) {
        return false;
      }
      
      if((millis() - searchMillis) > 2000){ //se nao encontreu depois de x tempo, retorna false
        Serial.println("Não encontrado");
        return false;
      }

      if(MANUAL_MODE) return;
  }

  Serial.println("Encontrado");
  return true;
}
