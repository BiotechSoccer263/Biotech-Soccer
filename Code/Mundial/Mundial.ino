#include <HTInfraredSeeker.h>
#include <Ultrasonic.h>
#include <Wire.h>
// === Sensores Ultrassônicos ===
Ultrasonic UFrt(43, 42);
Ultrasonic UTrs(41, 40);
Ultrasonic UEsq(45, 47);
Ultrasonic UDir(44, 46);

// === Motores Esquerda ===
const int ENA_ESQ = 2;
const int ENB_ESQ = 3;
const int IN1_ESQ = 4;
const int IN3_ESQ = 5;
const int IN2_ESQ = 6;
const int IN4_ESQ = 7;

// === Motores Direita ===
const int ENA_DIR = 8;
const int ENB_DIR = 9;
const int IN1_DIR = 10;
const int IN3_DIR = 11;
const int IN2_DIR = 12;
const int IN4_DIR = 13;

// === Ponte H do Dribler ===
const int ENA_DRIBLER = 15;
const int IN1_DRIBLER = 14;
const int IN2_DRIBLER = 17;

// Controle e estados
boolean PrimeiraLeitura = true;
boolean Sensores = true;
boolean Alinhado = false;
int estado;
int Modo = 1;

// Bússola
const int compassAddress = 0x01;
int Bussola;
int gol;
int limite;
int BMax;
int BMin;
char quebra;

// Velocidade
const int VeloCurva = 65;
const int VeloFrente = 120;

// Refletância
const int FrtR = A0;
const int EsqR = A2;
const int DirR = A3;
int BrancoMin = 15;
int BrancoMax = 200;
int refletancia;

// Ultrassônico
int distance;
int PLado = 70;
int PFrente = 55;

// Infravermelho
int ballDirecao;
int ballIntensi;
int IntensiMin = 80;

// Chaves
const int chavecurso = 28;
int leituraSensores = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Iniciando...");

  dribler("On", 220);

  //Sensores Extras
  pinMode(chavecurso, INPUT);
  pinMode(FrtR, INPUT);
  pinMode(EsqR, INPUT);
  pinMode(DirR, INPUT);

  // Motores esquerda
  pinMode(IN1_ESQ, OUTPUT);
  pinMode(IN2_ESQ, OUTPUT);
  pinMode(IN3_ESQ, OUTPUT);
  pinMode(IN4_ESQ, OUTPUT);
  pinMode(ENA_ESQ, OUTPUT);
  pinMode(ENB_ESQ, OUTPUT);

  // Motores direita
  pinMode(IN1_DIR, OUTPUT);
  pinMode(IN2_DIR, OUTPUT);
  pinMode(IN3_DIR, OUTPUT);
  pinMode(IN4_DIR, OUTPUT);
  pinMode(ENA_DIR, OUTPUT);
  pinMode(ENB_DIR, OUTPUT);

  // Dribler
  pinMode(ENA_DRIBLER, OUTPUT);
  pinMode(IN1_DRIBLER, OUTPUT);
  pinMode(IN2_DRIBLER, OUTPUT);

  Serial.println("Motores ok!");

  if (Sensores == true) {
    InfraredSeeker::Initialize();
    ReadCompassSensor();
    Serial.println("Sensores HiTech!");
  }

  Serial.println("Setup Feito");
  delay(1000);
}

void loop() {
  goleiro();
  //teste();
  //atacante();
  //SeguirBola();
}

void teste() {
  Serial.println("Teste");

  Serial.print("Refletância Frente - ");
  Serial.println(analogRead(FrtR));

  Serial.print("Refletância Esquerda - ");
  Serial.println(analogRead(EsqR));

  Serial.print("Refletância Direita - ");
  Serial.println(analogRead(DirR));

  distance = UFrt.read();
  Serial.print("Ultra Frente - ");
  Serial.println(distance);

  distance = UTrs.read();
  Serial.print("Ultra Traseiro - ");
  Serial.println(distance);

  distance = UEsq.read();
  Serial.print("Ultra Esq - ");
  Serial.println(distance);

  distance = UDir.read();
  Serial.print("Ultra Dir - ");
  Serial.println(distance);

  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;
  Serial.print("Infrared - ");
  Serial.println(ballDirecao);

  ReadCompassSensor();
  Serial.print("Compass - ");
  Serial.println(Bussola);

  Serial.print("Chave - ");
  Serial.println(digitalRead(chavecurso));

  Serial.println("");
  delay(600);
}
