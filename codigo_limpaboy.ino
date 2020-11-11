#include <Servo.h>        
#include <NewPing.h>      

// Pinos motor driver L298N
const int motorEsquerdaFrente = 4;
const int motorEsquerdaTras = 5;
const int motorDireitaFrente = 6;
const int motorDireitaTras = 7;

#define TRIGGER_PIN  A1
#define ECHO_PIN     A2
#define MAX_DISTANCE 250 Distancia maxima para pingar

Servo servo_motor;  // Nome do servo
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

boolean goesForward = false;
int distancia = 100;

void setup()
{
  // Pinos motor driver L298N como output
  pinMode(motorDireitaFrente, OUTPUT);
  pinMode(motorEsquerdaFrente, OUTPUT);
  pinMode(motorEsquerdaTras, OUTPUT);
  pinMode(motorDireitaTras, OUTPUT);
  
  servo_motor.attach(10);   
  servo_motor.write(115);   // Deixa o servo a 115 graus
  delay(2000);              // Espera 2 segundos
  distancia = lerPing();    // Lê distancia do ping
  delay(100);               // Espera 100ms
  distancia = lerPing();
  delay(100);
  distancia = lerPing();
  delay(100);
  distancia = lerPing();
  delay(100);
}

void loop()
{  
  int distanciaDireita = 0;
  int distanciaEsquerda = 0;
  delay(50);

  if (distancia <= 20)
  {
    movParar();
    delay(300);
    movTras();
    delay(400);
    movParar();
    delay(300);
    distanciaDireita = olharDireita();
    delay(300);
    distanciaEsquerda = olharEsquerda();
    delay(300);

    if (distanciaDireita >= distanciaEsquerda)
    {
      virarDireita();
      delay(900);
      movParar();
    }
    else
    {
      virarEsquerda();
      delay(900);
      movParar();
    }
  
  }
  else
  {
    movFrente(); 
  }

    distancia = lerPing();
}

int olharDireita()     // Gira o servo para direita
{  
  servo_motor.write(50);
  delay(500);
  int distancia = lerPing();
  delay(100);
  servo_motor.write(115);
  return distancia;
}

int olharEsquerda()      // Gira o servo para esquerda
{
  servo_motor.write(180);
  delay(500);
  int distancia = lerPing();
  delay(100);
  servo_motor.write(115);
  return distancia;
}

int lerPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Espera 100ms para cada ping
  int cm = sonar.ping_cm();   // Envia ping e recebe a distancia em cm
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void movParar()       // Faz o driver parar os motores
{
  digitalWrite(motorDireitaFrente, LOW);
  digitalWrite(motorDireitaTras, LOW);
  digitalWrite(motorEsquerdaFrente, LOW);
  digitalWrite(motorEsquerdaTras, LOW);
}

void movFrente()    // Faz o driver mover os motores para frente
{
    digitalWrite(motorDireitaFrente, HIGH);
    digitalWrite(motorDireitaTras, LOW);
    digitalWrite(motorEsquerdaFrente, HIGH);
    digitalWrite(motorEsquerdaTras, LOW);
}

void movTras()   // Faz o driver mover os motores inversamente
{
  digitalWrite(motorDireitaFrente, LOW);
  digitalWrite(motorDireitaTras, HIGH);
  digitalWrite(motorEsquerdaFrente, LOW);
  digitalWrite(motorEsquerdaTras, HIGH);
}

void virarDireita()      // Faz o driver mover o robô para direita
{
  digitalWrite(motorDireitaFrente, LOW);
  digitalWrite(motorDireitaTras, HIGH);
  digitalWrite(motorEsquerdaFrente, HIGH);
  digitalWrite(motorEsquerdaTras, LOW);
}

void virarEsquerda()       // Faz o driver mover o robô para esquerda
{
  digitalWrite(motorDireitaFrente, HIGH);
  digitalWrite(motorDireitaTras, LOW);
  digitalWrite(motorEsquerdaFrente, LOW);
  digitalWrite(motorEsquerdaTras, HIGH);
}