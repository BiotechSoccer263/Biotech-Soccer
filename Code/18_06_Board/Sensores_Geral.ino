// Função para seguir a bola com sensor infravermelho
void seguebola() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Lê o sinal de infravermelho
  ballDirecao = InfraredBall.Direction;                    // Define a direção da bola
  ballIntensi = InfraredBall.Strength;                     // Define a intensidade do sinal da bola

  linhas();  // Executa a função de proteção contra saída das linhas

  // if (ballDirecao == 0) {   // Caso a bola esteja fora do alcance...
  //   rotacionar("Esq", 120);            // Avança em linha reta em velocidade 120
  //   Serial.println("0");    // Exibe o estado no monitor serial
  //   delay(150);
  // }

  if (ballDirecao <= 9 && ballDirecao > 6) {  // Se a bola estiver à direita...
    rotacionar("Dir", Curvas);                // Gira para a direita na velocidade definida por Curvas
    Serial.println("A");
    delay(50);
  }
  if (ballDirecao >= 1 && ballDirecao < 4) {  // Se a bola estiver à esquerda...
    rotacionar("Esq", Curvas);                // Gira para a esquerda
    Serial.println("B");
    delay(50);
  }
  if (ballDirecao >= 4 && ballDirecao <= 6 || ballIntensi >= IntensiMin) {  // Se a bola estiver à frente ou com intensidade mínima...
    frente(Correr);                                                         // Move-se para frente em velocidade de corrida
    Serial.println("C");
    delay(50);
  }
}

// Função para impedir que o robô saia das linhas brancas do campo
void linhas() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  refletancia = analogRead(RefleEsq);  // Leitura do sensor de refletância esquerdo
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {
    tras(110);
    delay(300);
  }

  refletancia = analogRead(RefleDrt);  // Leitura do sensor de refletância direito
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {
    tras(110);
    delay(300);
  }
}

// Função para ler e ajustar o sensor de bússola
void ReadCompassSensor() {
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);
  Wire.endTransmission();

  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2)
    ;
  byte lowbyte = Wire.read();
  byte highbyte = Wire.read();
  Bussola = word(highbyte, lowbyte);

  if (PrimeiraLeitura == true) {
    gol = Bussola;
    limite = gol > 180 ? gol - 180 : gol + 180;
    quebra = gol > 180 ? 'D' : 'E';
    BMax = gol + 2;
    BMin = gol - 2;
    PrimeiraLeitura = false;
  } else {
    if (Bussola == gol || Bussola >= BMin && Bussola <= BMax) {
      Alinhado = true;
      parar();
    } else if (quebra == 'E') {
      if (BMin < Bussola && Bussola < limite) {
        Alinhado = false;
        rotacionar("Esq", Curvas);
        delay(50);
      } else {
        Alinhado = false;
        rotacionar("Dir", Curvas);
        delay(50);
      }
    } else {
      if (BMax > Bussola && Bussola > limite) {
        Alinhado = false;
        rotacionar("Dir", Curvas);
        delay(50);
      } else {
        Alinhado = false;
        rotacionar("Esq", Curvas);
        delay(50);
      }
    }

    estado = digitalRead(chavecurso);

    if (!Alinhado && estado == HIGH) {
      ReadCompassSensor();
    } else if (Alinhado && estado == HIGH) {

      if (UltraF.read() < 25) {
        tras(160);
        delay(500);
        return;
      }

      if (UltraD.read() < ParedeD && UltraE.read() > ParedeE) {
        lateral("Esq", 110);
        delay(700);
        return;
      } else if (UltraE.read() < ParedeE && UltraD.read() > ParedeD) {
        lateral("Dir", 110);
        delay(700);
        return;
      }

      int ULT = UltraF.read();
      if (ULT > 20 && ULT < 60) {
        Alinhamento();
        return;
      } else if (ULT > 25) {
        frente(170);
        delay(500);
        return;
      } else {
        tras(160);
        delay(500);
        return;
      }
    }
  }
}

// Função para testar os sensores do robô e mostrar os valores no serial
void testeSensor() {
  if (Sensores == true) {
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    ballDirecao = InfraredBall.Direction;
    ballIntensi = InfraredBall.Strength;

    Wire.beginTransmission(compassAddress);
    Wire.write(0x44);
    Wire.endTransmission();

    Wire.requestFrom(compassAddress, 2);
    while (Wire.available() < 2)
      ;
    byte lowbyte = Wire.read();
    byte highbyte = Wire.read();
    Bussola = word(highbyte, lowbyte);

    Serial.print("Bussola: ");
    Serial.print(Bussola);
    Serial.println("");

    Serial.print("Intensidade: ");
    Serial.print(ballIntensi);
    Serial.println("");

    Serial.print("Direção: ");
    Serial.print(ballDirecao);
    Serial.println("");
  }

  estado = digitalRead(chavecurso);
  Serial.print("Chave: ");
  Serial.print(estado);
  Serial.println("");

  Serial.print("Ultra Frente: ");
  Serial.print(UltraF.read());
  Serial.println("");

  Serial.print("Ultra Esquerda: ");
  Serial.print(UltraE.read());
  Serial.println("");

  Serial.print("Ultra Direita: ");
  Serial.print(UltraD.read());
  Serial.println("");

  Serial.print("Ultra Traseiro: ");
  Serial.print(UltraT.read());
  Serial.println("");

  refletancia = analogRead(RefleEsq);
  Serial.print("Sensor Esquerda: ");
  Serial.print(refletancia);
  Serial.println("");

  refletancia = analogRead(RefleDrt);
  Serial.print("Sensor Direita: ");
  Serial.print(refletancia);
  Serial.println("\n");
  delay(400);
}
