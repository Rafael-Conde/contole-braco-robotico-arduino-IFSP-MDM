
// inclui bibilioteca do servomotor
#include <Servo.h> 

// define pinos dos servos
#define pinServ1 2
#define pinServ2 3
#define pinServ3 4
#define pinServ4 5

// define as portas dos potenciometros
#define pot1 A0
#define pot2 A1
#define pot3 A2
// #define pot4 A3

// nomeia os servos
Servo serv1,serv2,serv3,serv4;

// cria as variavies dos angulos de cada motor
int motor1,motor2,motor3,motor4;
int pino_botao{6};
bool botao_apertado{false};

unsigned long mostradorTimer = 1;
const unsigned long intervaloMostrador = 5000;

void setup() {

  //inicia o monitor serial
  Serial.begin(9600); 
  pinMode(pino_botao, INPUT_PULLUP);
  // atribui pinos dos servos
  serv1.attach(pinServ1);
  serv2.attach(pinServ2);
  serv3.attach(pinServ3);
  serv4.attach(pinServ4);
  serv4.write(50);

}

void loop(){

  // leitura dos potenciometros
  motor1 = map(analogRead(pot1),0,1023,0,180);
  motor2 = map(analogRead(pot2),0,1023,0,85);
  motor3 = map(analogRead(pot3),0,1023,45,180);
  // motor4 = map(analogRead(pot4),0,1023,0,43);

  // posicionamento dos potenciometros 
  serv1.write(motor1);
  serv2.write(motor2);
  serv3.write(motor3);
  if(!digitalRead(pino_botao))
  {
    botao_apertado = !botao_apertado;
    if(botao_apertado)
    {
      serv4.write(0); 
    }
    else
    {
      serv4.write(50);
    }
  }
  // serv4.write(motor4);


  if ((millis() - mostradorTimer) >= intervaloMostrador) {

    // envio para o monitor serial do posicionamentos dos motores
    Serial.println("**********************************************");

    Serial.print("Pot1:");
    Serial.print(analogRead(pot1));
    Serial.print(" Angulo Motor1:");
    Serial.println(motor1);

    Serial.print("Pot2:");
    Serial.print(analogRead(pot2));
    Serial.print(" Angulo Motor2:");
    Serial.println(motor2);

    Serial.print("Pot3:");
    Serial.print(analogRead(pot3));
    Serial.print(" Angulo Motor3:");
    Serial.println(motor3);


    mostradorTimer = millis();
  }

  // tempo de espera para recomeçar
  delay(100);

}
