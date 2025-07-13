#include <HTInfraredSeeker.h>
#include <Ultrasonic.h>
#include <Wire.h>

// === Ultrasonic Sensors ===
Ultrasonic UFrt(43, 42);  // Front ultrasonic sensor
Ultrasonic UTrs(41, 40);  // Rear ultrasonic sensor
Ultrasonic UEsq(45, 47);  // Left ultrasonic sensor
Ultrasonic UDir(44, 46);  // Right ultrasonic sensor

// === Left Side Motors ===
const int ENA_ESQ = 2;  // Enable left motor 1
const int ENB_ESQ = 3;  // Enable left motor 2
const int IN1_ESQ = 4;  // H-bridge input 1 for left motor 1
const int IN3_ESQ = 5;  // H-bridge input 3 for left motor 2
const int IN2_ESQ = 6;  // H-bridge input 2 for left motor 1
const int IN4_ESQ = 7;  // H-bridge input 4 for left motor 2

// === Right Side Motors ===
const int ENA_DIR = 8;   // Enable right motor 1
const int ENB_DIR = 9;   // Enable right motor 2
const int IN1_DIR = 10;  // H-bridge input 1 for right motor 1
const int IN3_DIR = 11;  // H-bridge input 3 for right motor 2
const int IN2_DIR = 12;  // H-bridge input 2 for right motor 1
const int IN4_DIR = 13;  // H-bridge input 4 for right motor 2

// === Dribbler H-Bridge ===
const int ENA_DRIBLER = 15;  // Enable dribbler motor
const int IN1_DRIBLER = 14;  // H-bridge input 1 for dribbler
const int IN2_DRIBLER = 17;  // H-bridge input 2 for dribbler

// Control and states
boolean PrimeiraLeitura = true;  // If it's the first sensor reading
boolean Sensores = true;         // If sensors are enabled
boolean Alinhado = false;        // If the robot is aligned
int estado;                      // Current robot state

// Compass
const int compassAddress = 0x01;  // I2C address of the compass
int Bussola;                      // Current compass value
int gol;                          // Goal direction variable
int limite;                       // Compass threshold
int BMax;                         // Maximum compass value
int BMin;                         // Minimum compass value
char quebra;                      // Character for newline or state delimiter

// Speed
int VeloCurva = 55;    // Speed for left turn
int VeloCurvaD = 45;   // Speed for right turn
int VeloFrente = 125;  // Speed to move forward

// Reflectance
const int FrtR = A0;  // Front reflectance sensor
const int EsqR = A2;  // Left reflectance sensor
const int DirR = A3;  // Right reflectance sensor
int BrancoMin = 15;   // Minimum value for white surface
int BrancoMax = 300;  // Maximum value for white surface
int refletancia;      // Value read from reflectance sensor

// Ultrasonic
int distance;      // Distance measured by ultrasonic sensors
int PLado = 70;    // Side reference point
int PFrente = 70;  // Front reference point
int ParedeLados = 80;

// Infrared
int ballDirecao;      // Ball direction detected by infrared sensor
int ballIntensi;      // Signal strength of the ball
int IntensiMin = 80;  // Minimum intensity to consider ball detected

// Switches
const int chavecurso = 28;    // Pin for start/course switch
int leituraSensores = false;  // Sensor reading state
int modo = 1;
int robo = 2;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Wire.begin();        // Initialize I2C communication

  Serial.println("Starting...");

  if (robo == 1) {
    VeloCurva = 55;
    VeloCurvaD = 45;
    VeloFrente = 125;
  } else {
    VeloCurva = 70;
    VeloCurvaD = 60;
    VeloFrente = 135;
  }

  dribler("On", 255);  // Turn on dribbler with speed 220

  // Sensors and switches configuration
  pinMode(chavecurso, INPUT);
  pinMode(FrtR, INPUT);
  pinMode(EsqR, INPUT);
  pinMode(DirR, INPUT);

  // Left motors configuration
  pinMode(IN1_ESQ, OUTPUT);
  pinMode(IN2_ESQ, OUTPUT);
  pinMode(IN3_ESQ, OUTPUT);
  pinMode(IN4_ESQ, OUTPUT);
  pinMode(ENA_ESQ, OUTPUT);
  pinMode(ENB_ESQ, OUTPUT);

  // Right motors configuration
  pinMode(IN1_DIR, OUTPUT);
  pinMode(IN2_DIR, OUTPUT);
  pinMode(IN3_DIR, OUTPUT);
  pinMode(IN4_DIR, OUTPUT);
  pinMode(ENA_DIR, OUTPUT);
  pinMode(ENB_DIR, OUTPUT);

  // Dribbler motor configuration
  pinMode(ENA_DRIBLER, OUTPUT);
  pinMode(IN1_DRIBLER, OUTPUT);
  pinMode(IN2_DRIBLER, OUTPUT);

  Serial.println("Motors OK!");

  if (Sensores == true) {
    Serial.println("Sensors");
    InfraredSeeker::Initialize();  // Initialize HiTechnic infrared sensor
    ReadCompassSensor();           // Read compass value
    Serial.println("HiTech sensors ready!");
  }

  Serial.println("Setup Complete");
  delay(1000);  // Wait 1 second before entering loop
}

void loop() {
  //atacante();
  goleiro();
}

void teste() {
  Serial.println("Test");  // Print 'Test' to indicate diagnostics start

  Serial.print("Front Reflectance - ");
  Serial.println(analogRead(FrtR));  // Read and print front reflectance value

  Serial.print("Left Reflectance - ");
  Serial.println(analogRead(EsqR));  // Read and print left reflectance value

  Serial.print("Right Reflectance - ");
  Serial.println(analogRead(DirR));  // Read and print right reflectance value

  distance = UFrt.read();  // Read distance from front ultrasonic sensor
  Serial.print("Ultra Front - ");
  Serial.println(distance);

  distance = UTrs.read();  // Read distance from rear ultrasonic sensor
  Serial.print("Ultra Rear - ");
  Serial.println(distance);

  distance = UEsq.read();  // Read distance from left ultrasonic sensor
  Serial.print("Ultra Left - ");
  Serial.println(distance);

  distance = UDir.read();  // Read distance from right ultrasonic sensor
  Serial.print("Ultra Right - ");
  Serial.println(distance);

  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Read data from HiTechnic IR sensor
  ballDirecao = InfraredBall.Direction;                    // Update ball direction
  ballIntensi = InfraredBall.Strength;                     // Update ball signal strength
  Serial.print("Infrared - ");
  Serial.println(ballDirecao);

  ReadCompassSensor();  // Update compass reading
  Serial.print("Compass - ");
  Serial.println(Bussola);

  Serial.print("Switch - ");
  Serial.println(digitalRead(chavecurso));  // Read and print switch state

  Serial.println("");  // Blank line to separate readings in serial monitor
  delay(600);          // Wait 600 ms before next reading
}