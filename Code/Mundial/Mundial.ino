#include <HTInfraredSeeker.h>
#include <Ultrasonic.h>
#include <Wire.h>

// === Sensores Ultrassônicos ===
Ultrasonic UFrt(43, 42);  // Sensor ultrassônico frontal
Ultrasonic UTrs(41, 40);  // Sensor ultrassônico traseiro
Ultrasonic UEsq(45, 47);  // Sensor ultrassônico esquerdo
Ultrasonic UDir(44, 46);  // Sensor ultrassônico direito

// === Motores do lado esquerdo ===
const int ENA_ESQ = 2;  // Enable motor esquerdo 1
const int ENB_ESQ = 3;  // Enable motor esquerdo 2
const int IN1_ESQ = 4;  // Entrada 1 ponte H motor esquerdo 1
const int IN3_ESQ = 5;  // Entrada 3 ponte H motor esquerdo 2
const int IN2_ESQ = 6;  // Entrada 2 ponte H motor esquerdo 1
const int IN4_ESQ = 7;  // Entrada 4 ponte H motor esquerdo 2

// === Motores do lado direito ===
const int ENA_DIR = 8;   // Enable motor direito 1
const int ENB_DIR = 9;   // Enable motor direito 2
const int IN1_DIR = 10;  // Entrada 1 ponte H motor direito 1
const int IN3_DIR = 11;  // Entrada 3 ponte H motor direito 2
const int IN2_DIR = 12;  // Entrada 2 ponte H motor direito 1
const int IN4_DIR = 13;  // Entrada 4 ponte H motor direito 2

// === Ponte H do Dribler ===
const int ENA_DRIBLER = 15;  // Enable do motor do dribler
const int IN1_DRIBLER = 14;  // Entrada 1 ponte H do dribler
const int IN2_DRIBLER = 17;  // Entrada 2 ponte H do dribler

// Controle e estados
boolean PrimeiraLeitura = true;  // Se é a primeira leitura do sensor
boolean Sensores = true;         // Se os sensores estão ativados
boolean Alinhado = false;        // Se o robô está alinhado
int estado;                      // Estado atual do robô
int Modo = 1;                    // Modo de operação do robô

// Bússola
const int compassAddress = 0x01;  // Endereço I2C da bússola
int Bussola;                      // Valor atual da bússola
int gol;                          // Variável para direção do gol
int limite;                       // Limite da bússola
int BMax;                         // Valor máximo da bússola
int BMin;                         // Valor mínimo da bússola
char quebra;                      // Caractere para quebra de linha ou estado

// Velocidade
const int VeloCurva = 55;    // Velocidade para curva à esquerda
const int VeloCurvaD = 45;   // Velocidade para curva à direita
const int VeloFrente = 145;  // Velocidade para andar para frente

// Refletância
const int FrtR = A0;  // Sensor de refletância frontal
const int EsqR = A2;  // Sensor de refletância esquerdo
const int DirR = A3;  // Sensor de refletância direito
int BrancoMin = 15;   // Valor mínimo para cor branca
int BrancoMax = 200;  // Valor máximo para cor branca
int refletancia;      // Valor lido da refletância

// Ultrassônico
int distance;      // Distância medida pelos sensores ultrassônicos
int PLado = 70;    // Ponto de referência lateral
int PFrente = 70;  // Ponto de referência frontal
int ParedeLados = 80;

// Infravermelho
int ballDirecao;      // Direção da bola detectada pelo sensor infravermelho
int ballIntensi;      // Intensidade do sinal da bola
int IntensiMin = 80;  // Intensidade mínima para considerar a bola detectada

// Chaves
const int chavecurso = 28;    // Pino para a chave de início/curso
int leituraSensores = false;  // Estado de leitura dos sensores

void setup() {
  Serial.begin(9600);  // Inicializa comunicação serial
  Wire.begin();        // Inicializa comunicação I2C

  Serial.println("Iniciando...");

  dribler("On", 255);  // Liga o dribler com velocidade 220

  // Configuração dos sensores e chaves
  pinMode(chavecurso, INPUT);
  pinMode(FrtR, INPUT);
  pinMode(EsqR, INPUT);
  pinMode(DirR, INPUT);

  // Configuração dos motores do lado esquerdo
  pinMode(IN1_ESQ, OUTPUT);
  pinMode(IN2_ESQ, OUTPUT);
  pinMode(IN3_ESQ, OUTPUT);
  pinMode(IN4_ESQ, OUTPUT);
  pinMode(ENA_ESQ, OUTPUT);
  pinMode(ENB_ESQ, OUTPUT);

  // Configuração dos motores do lado direito
  pinMode(IN1_DIR, OUTPUT);
  pinMode(IN2_DIR, OUTPUT);
  pinMode(IN3_DIR, OUTPUT);
  pinMode(IN4_DIR, OUTPUT);
  pinMode(ENA_DIR, OUTPUT);
  pinMode(ENB_DIR, OUTPUT);

  // Configuração do motor do dribler
  pinMode(ENA_DRIBLER, OUTPUT);
  pinMode(IN1_DRIBLER, OUTPUT);
  pinMode(IN2_DRIBLER, OUTPUT);

  Serial.println("Motores ok!");

  if (Sensores == true) {
    InfraredSeeker::Initialize();  // Inicializa sensor infravermelho HiTechnic
    ReadCompassSensor();           // Lê o valor da bússola
    Serial.println("Sensores HiTech!");
  }

  Serial.println("Setup Feito");
  delay(1000);  // Aguarda 1 segundo antes de iniciar loop
}

void loop() {
  //conduzirBola(120);
  //goleiro();  // Função para lógica do goleiro (está comentada, não executa)
  //teste();     // Função de teste dos sensores e atuadores (está comentada)
  atacante();  // Função para executar a lógica do atacante
  //SeguirBola(); // Função para seguir a bola (está comentada)
}

void teste() {
  Serial.println("Teste");  // Imprime 'Teste' para indicar início do diagnóstico

  Serial.print("Refletância Frente - ");
  Serial.println(analogRead(FrtR));  // Lê e exibe valor do sensor de refletância frontal

  Serial.print("Refletância Esquerda - ");
  Serial.println(analogRead(EsqR));  // Lê e exibe valor do sensor de refletância esquerdo

  Serial.print("Refletância Direita - ");
  Serial.println(analogRead(DirR));  // Lê e exibe valor do sensor de refletância direito

  distance = UFrt.read();  // Lê distância do sensor ultrassônico frontal
  Serial.print("Ultra Frente - ");
  Serial.println(distance);

  distance = UTrs.read();  // Lê distância do sensor ultrassônico traseiro
  Serial.print("Ultra Traseiro - ");
  Serial.println(distance);

  distance = UEsq.read();  // Lê distância do sensor ultrassônico esquerdo
  Serial.print("Ultra Esq - ");
  Serial.println(distance);

  distance = UDir.read();  // Lê distância do sensor ultrassônico direito
  Serial.print("Ultra Dir - ");
  Serial.println(distance);

  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Lê dados do sensor infravermelho HiTechnic
  ballDirecao = InfraredBall.Direction;                    // Atualiza direção da bola detectada
  ballIntensi = InfraredBall.Strength;                     // Atualiza intensidade do sinal da bola
  Serial.print("Infrared - ");
  Serial.println(ballDirecao);

  ReadCompassSensor();  // Atualiza leitura da bússola
  Serial.print("Compass - ");
  Serial.println(Bussola);

  Serial.print("Chave - ");
  Serial.println(digitalRead(chavecurso));  // Lê e exibe estado da chave física

  Serial.println("");  // Linha em branco para separar leituras no monitor serial
  delay(600);          // Aguarda 600 ms antes da próxima leitura
}