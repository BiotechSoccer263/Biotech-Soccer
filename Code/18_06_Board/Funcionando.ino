// Incluindo as bibliotecas que iremos utilizar
#include <HTInfraredSeeker.h>  // Biblioteca do Infravermelho
#include <Ultrasonic.h>        // Biblioteca do Ultrassônico
#include <Wire.h>              // Biblioteca padrão Arduino

// Variáveis de Motores (Motor Shield)
const int DIN1 = 2;  // Pino de controle do Motor A
const int DIN2 = 3;  // Pino de controle do Motor A
const int DIN3 = 4;  // Pino de controle do Motor B
const int DIN4 = 5;  // Pino de controle do Motor B

const int DENA = 6;  // Pino de controle de velocidade do Motor A
const int DENB = 7;  // Pino de controle de velocidade do Motor B

const int EIN1 = 8;   // Pino de controle do Motor C
const int EIN2 = 9;   // Pino de controle do Motor C
const int EIN3 = 10;  // Pino de controle do Motor D
const int EIN4 = 11;  // Pino de controle do Motor D

const int EENA = 12;  // Pino de controle de velocidade do Motor C
const int EENB = 13;  // Pino de controle de velocidade do Motor D

const int DRIN1 = 50;  // Pino de controle do Motor E
const int DRIN2 = 51;  // Pino de controle do Motor E
const int DRENB = 48;  // Pino de controle de velocidade do Motor E

// Variável Ultrassonico Lateral
Ultrasonic UltraF(35, 34);  // Ultrassônico Frente
Ultrasonic UltraE(23, 22);  // Ultrassônico Esquerda
Ultrasonic UltraD(25, 24);  // Ultrassônico Direita
Ultrasonic UltraT(27, 26);  // Ultrassônico Atrás
const int ParedeT = 25;     // Distância Parede Atrás
const int ParedeE = 55;     // Distância Parede Esquerda
const int ParedeD = 55;     // Distância Parede Direita
const int ParedeF = 60;     // Distância Parede Frente
// ----------------- // ----------------- //

// Variáveis de Sensores de Refletância
const int RefleEsq = A8;  // Sensor Direita
const int RefleDrt = A9;  // Sensor Esquerda

// Variáveis de Controle
boolean PrimeiraLeitura = true;  // Variável de leitura Bússola
boolean Sensores = true;         // Variável de Ativação Sensores
boolean testeMotores = false;    // Variável de teste de Motores
boolean Alinhado = false;        // Variável de Alinhamento
int estado;                      // Variável de estado Infravermelho
int Modo = 1;                    // Modo desejado da programação [Atacante/Goleiro]

// Variáveis de Bússola
const int compassAddress = 0x01;  // Endereço da Bussola
int Bussola;                      // Valor atual da Bússola
int gol;                          // Valor do Gol Oponente
int limite;                       // Valor Limite da Bússola
int BMax;                         // Valor Máximo da Bússola
int BMin;                         // Valor Mínimo da Bússola
char quebra;                      // Valor da Quebra

const int Curvas = 60;   // Velocidade para Curvas
const int Correr = 100;  // Velocidade para Correr

int BrancoMin = 50;   // Valor Branco Mínimo
int BrancoMax = 150;  // Valor Branco Máximo
int refletancia;      // Valor Armazenamento Refletância

// Variáveis de Infravermelho
int ballDirecao;       // Direção Infravermelho
int ballIntensi;       // Intensidade Infravermelho
int IntensiMin = 100;  // Intensidade Mínima

// Variáveis do Chave Curso
const int chavecurso = 52;    // Porta Chave fim de Curso
const int botaoSensor = 53;   // Porta Botão Leitura
int leituraSensores = false;  // Estado Botão Leitura

// Variáveis Armazenamento Ultrassônicos
byte UF;   // Armazenamento Ultrassônico Frente
byte LUD;  // Armazenamento Ultrassônico Direito
byte LUE;  // Armazenamento Ultrassônico Esquerdo

void setup() {
  // Inicialização Geral
  Serial.begin(9600);            // Inicialização do Serial
  pinMode(botaoSensor, OUTPUT);  // Definindo Botão Sensor
  pinMode(chavecurso, INPUT);    // Definindo botão ChaveFimDeCurso
  // Ativar pinos Ponte H
  pinMode(EIN1, OUTPUT);   // Definindo o pino EIN1 como saída
  pinMode(EIN2, OUTPUT);   // Definindo o pino EIN2 como saída
  pinMode(EIN3, OUTPUT);   // Definindo o pino EIN3 como saída
  pinMode(EIN4, OUTPUT);   // Definindo o pino EIN4 como saída
  pinMode(DIN1, OUTPUT);   // Definindo o pino DIN1 como saída
  pinMode(DIN2, OUTPUT);   // Definindo o pino DIN2 como saída
  pinMode(DIN3, OUTPUT);   // Definindo o pino DIN3 como saída
  pinMode(DIN4, OUTPUT);   // Definindo o pino DIN4 como saída
  pinMode(DRIN1, OUTPUT);  // Definindo o pino DRIN1 como saída
  pinMode(DRIN1, OUTPUT);  // Definindo o pino DRIN1 como saída
  // Pinos de Velocidade
  pinMode(EENA, OUTPUT);   // Definindo o pino EENA como saída
  pinMode(EENB, OUTPUT);   // Definindo o pino EENB como saída
  pinMode(DENA, OUTPUT);   // Definindo o pino DENA como saída
  pinMode(DENB, OUTPUT);   // Definindo o pino DENB como saída
  pinMode(DRENB, OUTPUT);  // Definindo o pino DRENB como saída
  // Sensores Inicialização
  if (Sensores == true) {  // Caso Sensores Ativado...
    // Inicialização do "Wire"
    Wire.begin();                            // Iniciar Wire
    Wire.beginTransmission(compassAddress);  // Captar Informações do endereço
    Wire.write(0x00);                        // Escrever informações
    Wire.endTransmission();                  // Encerrar Transmissão
    // Inicialização do Infravermelho
    InfraredSeeker::Initialize();  // Iniciar HiTech Infrared Seeker
    // Loop para exigir sensores
    ReadCompassSensor();            // Leitura Inicial Bússola
    while (Wire.available() > 0) {  // Caso informações recebidas...
      Wire.read();                  // Wire lerá elas
    }
  }
  DriblerAtivar(200);             // Ativar Dribler na força [Máxima]
  Serial.println("Setup Feito");  // Retornar no Serial Conclusão
}

void loop() {
  if (testeMotores == true) {  // Definindo função de Loop [Infinito]...
    lateral("Dir", Correr);    // Função de movimento para frente com velocidade definida
    delay(200);                // Atraso de 200ms
    return;
  }
  leituraSensores = digitalRead(botaoSensor);  // 'leituraSensores' será valor retornado do pino 'botaoSensor'
  if (leituraSensores) {                       // Caso 'leituraSensores' seja verdadeira...
    parar();                                   // Executar função de parada
    testeSensor();                             // Executar teste de sensores
  } else {                                     // Senão...
    if (Modo == 1) {                           // Caso 'Modo' esteja [Atacante]...
      atacante();                              // Executar funções 'atacante'
    } else {                                   // Senão...
      goleiro();                               // Executar funções 'goleiro'
    }
  }
}

void atacante() {                          // Define função 'atancante'...
  estado = digitalRead(chavecurso);        // Define 'estado' para leitura da porta 'chavecurso'
  if (estado == HIGH) {                    // Caso 'estado' esteja falso [LOW]...
    Serial.println("Bússola Executando");  // Retorna Serial de ação
    ReadCompassSensor();                   // Executa função 'ReadCompassSensor'
  } else {                                 // Senão...
    Serial.println("Função Executando");   // Retorna Serial de ação
    seguebola();                           // Executa função 'seguebola'
  }
}

void goleiro() {                     // Define função 'goleiro'...
  estado = digitalRead(chavecurso);  // Define 'estado' para leitura da porta 'chavecurso'
  if (estado == HIGH) {              // Caso 'estado' esteja falso [LOW]...
    frente(200);
    delay(250);
    DriblerAtivar2(255);
    chutar();         // Executa função 'ReadCompassSensor'
  } else {            // Senão...
    goleiro_infra();  // Executa função 'seguebola'
  }
}
