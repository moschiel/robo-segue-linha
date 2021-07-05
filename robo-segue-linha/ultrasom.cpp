#include "ultrasom.h"

#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 3
#define pino_echo 2
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

float getUltrasomDistanceInCM()
{
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  //Exibe informacoes no serial monitor
  //Serial.print("Distancia em cm: ");
  //Serial.print(cmMsec);
  //Serial.print(" - Distancia em polegadas: ");
  //Serial.println(inMsec);
  //delay(1000);
  return cmMsec;
}
 
