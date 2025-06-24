// Incluindo as bibliotecas que iremos utilizar
#include <HTInfraredSeeker.h>  // Biblioteca do Infravermelho
#include <Ultrasonic.h>        // Biblioteca do Ultrassônico
#include <Wire.h>              // Biblioteca padrão Arduino

// Variáveis de Motores (Motor Shield)
const int DIN1 = 2;
const int DIN2 = 3;
const int DIN3 = 4;
const int DIN4 = 5;

const int DENA = 6;
const int DENB = 7;

const int EIN1 = 8;
const int EIN2 = 9;
const int EIN3 = 10;
const int EIN4 = 11;

const int EENA = 12;
const int EENB = 13;

const int DRIN1 = 50;
const int DRIN2 = 51;
const int DRENB = 48;

// Variável Ultrassonico Lateral
Ultrasonic UltraF(46, 47);  // Ultrassônico Frente
Ultrasonic UltraE(23, 22);  // Ultrassônico Esquerda
Ultrasonic UltraD(25, 24);  // Ultrassônico Direita
Ultrasonic UltraT(27, 26);  // Ultrassônico Atrás
const int ParedeT = 25;     // Distância Parede Atrás
const int ParedeE = 50;     // Distância Parede Esquerda
const int ParedeD = 50;     // Distância Parede Direita
const int ParedeF = 60;     // Distância Parede Frente
// ----------------- // ----------------- //

// Variáveis de Sensores de Refletância
const int RefleEsq = A8;  // Sensor Direita
const int RefleDrt = A9;  // Sensor Esquerda

// Variáveis de Controle
boolean PrimeiraLeitura = true;  // Variável de leitura Bússola
boolean Sensores = true;        // Variável de Ativação Sensores
boolean testeMotores = false;
boolean Alinhado = false;        // Variável de Alinhamento
int estado;                      // Variável de estado Infravermelho
int Modo = 1;                    // Modo desejado da programação [Atacante/Goleiro]

// Variáveis de Bússola
const int compassAddress = 0x01;  // Endereço da Bussola
int Bussola;                      // Valor atual
int gol;                          // Valor do Gol Oponente
int limite;                       // Valor Limite
int BMax;                         // Valor Máximo
int BMin;                         // Valor Mínimo
char quebra;                      // Valor da Quebra

const int Curvas = 60;   // Velocidade para Curvas
const int Correr = 115;  // Velocidade para Correr

int BrancoMin = 70;   // Valor Branco Mínimo
int BrancoMax = 340;  // Valor Branco Máximo
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
  pinMode(EIN1, OUTPUT);
  pinMode(EIN2, OUTPUT);
  pinMode(EIN3, OUTPUT);
  pinMode(EIN4, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);
  pinMode(DIN3, OUTPUT);
  pinMode(DIN4, OUTPUT);
  pinMode(DRIN1, OUTPUT);
  pinMode(DRIN1, OUTPUT);
  // Pinos de Velocidade
  pinMode(EENA, OUTPUT);
  pinMode(EENB, OUTPUT);
  pinMode(DENA, OUTPUT);
  pinMode(DENB, OUTPUT);
  pinMode(DRENB, OUTPUT);
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
  DriblerAtivar(200);  // Ativar Dribler na força [Máxima]
  Serial.println("Setup Feito");  // Retornar no Serial Conclusão
}

void loop() {  
  if (testeMotores == true) { // Definindo função de Loop [Infinito]...
    frente(Correr);
    delay(200);
    return;
   }
  leituraSensores = digitalRead(botaoSensor);  // 'leituraSensores' será valor retornado do pino 'botaoSensor'
  if (leituraSensores) {                       // Caso 'leituraSensores' seja verdadeira...
    parar();
    testeSensor();    // Executar teste de sensores
  } else {            // Senão...
    if (Modo == 1) {  // Caso 'Modo' esteja [Atacante]...
      atacante();     // Executar funções 'atacante'
    } else {          // Senão...
      goleiro();      // Executar funções 'goleiro'
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

void goleiro() {    // Define função 'goleiro'...
  estado = digitalRead(chavecurso);        // Define 'estado' para leitura da porta 'chavecurso'
  if (estado == HIGH) {                    // Caso 'estado' esteja falso [LOW]...
    chutar();                   // Executa função 'ReadCompassSensor'
  } else {                                 // Senão...
    goleiro_infra();                           // Executa função 'seguebola'
  }
}
