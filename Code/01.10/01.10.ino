#include <Ultrasonic.h>        // Biblioteca do ultrassonico
#include <HTInfraredSeeker.h>  // Biblioteca do Infravermelho
#include <Wire.h>              // Biblioteca padrão Arduino


// Endereço da bússola (ajuste conforme seu módulo)
bool alinhado;

// Ajuste de offset da bússola (se precisar calibrar)
const int OFFSET_BUSSOLA = 0;      

// Ângulo do gol em graus (0-359)
 int ANGULO_DO_GOL = 0;     

// Tolerância para considerar que está alinhado
const int TOLERANCIA_ANGULAR = 5; 

// Velocidade de rotação usada para ajustes
const int VELOCIDADE_ROTACAO = 60;

// Flag do chute
bool chutou = false;
bool falha = false;

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

const int DRIN3 = 51;
const int DRIN4 = 48;
const int DRENB = 50;

// Variável Ultrassonico Lateral
Ultrasonic UltraF(32, 33);  // Ultrassônico Frente
Ultrasonic UltraE(30, 31);  // Ultrassônico Esquerda
Ultrasonic UltraD(34, 35);  // Ultrassônico Direita
Ultrasonic UltraT(26, 27);
Ultrasonic UltraF2(47, 46);   // Ultrassônico Atrás
const int ParedeT = 15;     // Distância Parede Atrás
const int ParedeE = 65;     // Distância Parede Esquerda
const int ParedeD = 60;     // Distância Parede Direita
const int ParedeF = 60;     // Distância Parede Frente
// ----------------- // ----------------- //
int tolerancia = 5;
// Variáveis de Sensores de Refletância
const int RefleEsq = A8;  // Sensor Direita
const int RefleDrt = A9; 
const int RefleFrt = A10;  // Sensor Esquerda

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
char quebra;     
                 // Valor da Quebra
const int Curvasa = 50;   // Velocidade para Curvas
const int Curvas = 80;   // Velocidade para Curvas
const int Correr = 220;  // Velocidade para Correr

int BrancoMin = 10;   // Valor Branco Mínimo
int BrancoMax = 300;  // Valor Branco Máximo
int refletancia;      // Valor Armazenamento Refletância

// Variáveis de Infravermelho
int ballDirecao;       // Direção Infravermelho
int ballIntensi;       // Intensidade Infravermelho
int IntensiMin = 100;  // Intensidade Mínima

// Variáveis do Chave Curso
const int pinoChave = 22;    // Porta Chave fim de Curso
const int botaoSensor = 52;   // Porta Botão Leitura
int leituraSensores = true;  // Estado Botão Leitura

// Variáveis Armazenamento Ultrassônicos
byte UF;   // Armazenamento Ultrassônico Frente
byte LUD;  // Armazenamento Ultrassônico Direito
byte LUE;  // Armazenamento Ultrassônico Esquerdo

void setup() {
  Serial.begin(9600);            // Inicialização do Serial
  pinMode(botaoSensor, OUTPUT);  // Definindo Botão Sensor
  pinMode(pinoChave, INPUT_PULLUP);    // Definindo botão ChaveFimDeCurso
  // Ativar pinos Ponte H
  pinMode(EIN1, OUTPUT);
  pinMode(EIN2, OUTPUT);
  pinMode(EIN3, OUTPUT);
  pinMode(EIN4, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);
  pinMode(DIN3, OUTPUT);
  pinMode(DIN4, OUTPUT);
  pinMode(DRIN3, OUTPUT);
  pinMode(DRIN4, OUTPUT);
  // Pinos de Velocidade
  pinMode(EENA, OUTPUT);
  pinMode(EENB, OUTPUT);
  pinMode(DENA, OUTPUT);
  pinMode(DENB, OUTPUT);
  pinMode(DRENB, OUTPUT);
  // Sensores Inicialização
  if (Sensores == true) { 
     // Caso Sensores Ativado...
    // Inicialização do "Wire"
    Wire.begin();                            // Iniciar Wire
    Wire.beginTransmission(compassAddress);  // Captar Informações do endereço
    Wire.write(0x00);                        // Escrever informações
    Wire.endTransmission();                  // Encerrar Transmissão
    // Inicialização do Infravermelho
    ReadCompassSensor();
    InfraredSeeker::Initialize(); 
     // Iniciar HiTech Infrared Seeker
    // Loop para exigir sensores
            // Leitura Inicial Bússola
    while (Wire.available() > 0) {  // Caso informações recebidas...
      Wire.read();                  // Wire lerá elas
    }
  }
  // Ativar Dribler na força [Máxima]
  DriblerAtivar(255);
  Serial.println("Setup Feito");  // Retornar no Serial Conclusão
}

void loop() {
  seguebola();  
// conduzir();
// goleiro();
// testeSensor();
// alinhar(80);
// atacante();
// frente(240);
}



void atacante() {                          // Define função 'atancante'...
if(digitalRead(pinoChave) == HIGH){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
Serial.println(" funcionando");
parar();
delay(200);
ReadCompassSensor();




   //ACENDE O LED
  }else{ //SENÃO, FAZ
    Serial.println("nao funcionando");
   seguebola(); //APAGA O LED
    DriblerAtivar(255);
  }
}

void goleiro() {    // Define função 'goleiro'...
goleiro_infra();
}