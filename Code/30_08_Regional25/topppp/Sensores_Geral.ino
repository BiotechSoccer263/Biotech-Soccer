// Seguir o infravermelho da bola
void seguebola() {  
Serial.println(ballIntensi);// Define 'seguebola' para...
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Inicia leitura de infravermelho
  ballDirecao = InfraredBall.Direction;                    // 'ballDirecao' será definida pela direção recebida pelo infravermelho
  ballIntensi = InfraredBall.Strength;                     // 'ballIntensi' será definida para força recebida do infravermelho
// Executa função 'linhas'
  if(ballIntensi > 20){
    int correr = 100;
  } 

  if (ballDirecao == 0) {  // Se 'ballDirecao' estiver [Desligada/Longe]...
    frente(120);           // Andar para frente na velocidade [120]
    Serial.println("0");   // Retorna Serial
               // Esperar Tempo
  }

  if (ballDirecao <= 9 && ballDirecao >= 6) {  // Se 'ballDirecao' estiver a [Direita]...
    rotacionar("Dir", Curvas);                 // Rotacionar para [Direita] na velocidade [Curvas]
    Serial.println("A");                       // Retorna Serial
                                     // Esperar Tempo
  }
  if (ballDirecao >= 1 && ballDirecao <= 4) {  // Se 'ballDirecao' estiver a [Esquerda]...
    rotacionar("Esq", Curvas);                 // Rotacionar para [Esquerda] na velocidade [Curvas]
    Serial.println("B");                       // Retorna Serial
                                     // Esperar Tempo
  }
  if (ballDirecao == 5 ) {  // Se 'ballDirecao' estiver a [Frente]...
    frente(Correr);                                     // Movimentar a frente na velocidade [Correr]
    Serial.println("C");                                // Retorna Serial
                                             // Esperar Tempo
  }
  int correr = 220;
  linhas();
}

// Impedir que saia das linhas Brancas
void linhas() {                                            // Define 'linhas' para...
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Inicia leitura de infravermelho
  ballDirecao = InfraredBall.Direction;                    // 'ballDirecao' será definida pela direção recebida pelo infravermelho
  ballIntensi = InfraredBall.Strength;
      if (UltraF.read() < 15 && ballIntensi < IntensiMin) {
    tras(210);
    delay(400);
  }                   // 'ballIntensi' será definida para força recebida do infravermelho
  refletancia = analogRead(RefleFrt);                          // 'refletancia' para leitura de analógico de 'SensorFrtD'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' seja maior ou igual que [BrancoMin] e 'refletancia' menor ou igual que [BrancoMax]...
    tras(250);                                                 // Movimentar atrás na velocidade [110]
    delay(300);                                                // Esperar [300] milissegundos
  }
  refletancia = analogRead(RefleEsq);                          // 'refletancia' para leitura de analógico de 'SensorFrtE'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' for maior ou igual que [BrancoMin] e 'refletancia' for menor ou igual que [BrancoMax]...
    lateral("Dir", 110);
     delay(100);
    tras(250);                                                    // Movimentar atrás na velocidade [110]
    delay(400);                                                // Esperar [300] milissegundos
  }
  refletancia = analogRead(RefleDrt);                          // 'refletancia' para leitura de analógico de 'SensorFrtD'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' seja maior ou igual que [BrancoMin] e 'refletancia' menor ou igual que [BrancoMax]...
    lateral("Dir", 110);
    delay(100);
    tras(250);                                                      // Movimentar atrás na velocidade [110]
    delay(400);                                                // Esperar [300] milissegundos
  }
}


// Teste Sensores
void testeSensor() {
  if (Sensores == true) {
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    ballDirecao = InfraredBall.Direction;
    ballIntensi = InfraredBall.Strength;

    Wire.beginTransmission(compassAddress);  // Iniciar trasmissão da bússola
    Wire.write(0x44);                        // Modo de escrita
    Wire.endTransmission();                  // Terminar trasmissão

    Wire.requestFrom(compassAddress, 2);  // Requirir 2 valores da bússola
    while (Wire.available() < 2)          // Caso informação chegue
      ;
    byte lowbyte = Wire.read();         // 'lowbyte' será valor lido
    byte highbyte = Wire.read();        // 'highbyte' será valor lido
    Bussola = word(highbyte, lowbyte);  // 'Bussola' será a junção de 'highbyte' e 'lowbyte'

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

  Serial.print("Chave: ");
  Serial.print(estado);
  Serial.println("");

  Serial.print("Ultra Frente: ");
  Serial.print(UltraF.read());
  Serial.println("");
  /////////////
  Serial.print("Ultra Esquerda: ");
  Serial.print(UltraE.read());
  Serial.println("");
  /////////////
  Serial.print("Ultra Direita: ");
  Serial.print(UltraD.read());
  Serial.println("");
  /////////////
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
  delay(700);
}


void conduzir() {
  Serial.println(F("🚀 Indo em direção ao gol com correção mínima..."));

  // Variáveis de alinhamento
  static bool PrimeiraLeitura = true;
  static int gol, limite, BMax, BMin;
  static char quebra;

  while (!chutou) {
    // --- Ler sensores ---
    int frenteDist   = UltraF.read();
    int direitaDist  = UltraD.read();
    int esquerdaDist = UltraE.read();

    // --- Ler bússola ---
    Wire.beginTransmission(compassAddress);
    Wire.write(0x44);
    Wire.endTransmission();
    Wire.requestFrom(compassAddress, 2);
    while (Wire.available() < 2);

    byte low = Wire.read();
    byte high = Wire.read();
    int Bussola = word(high, low) % 360;

    // --- Definir referência de gol na primeira leitura ---
    if (PrimeiraLeitura) {
      gol = Bussola;
      limite = (gol > 180) ? gol - 180 : gol + 180;
      quebra = (gol > 180) ? 'D' : 'E';
      BMax = gol + TOLERANCIA_ANGULAR;
      BMin = gol - TOLERANCIA_ANGULAR;
      PrimeiraLeitura = false;
    }

    // --- Verifica se está perto do gol ---
    if (frenteDist <= 20) {
      parar();
      Serial.println(F("🟨 Perto do gol! Fazendo alinhamento final..."));

      // === Alinhamento final ===
      while (true) {
        // Ler novamente a bússola
        Wire.beginTransmission(compassAddress);
        Wire.write(0x44);
        Wire.endTransmission();
        Wire.requestFrom(compassAddress, 2);
        while (Wire.available() < 2);

        byte low = Wire.read();
        byte high = Wire.read();
        Bussola = word(high, low) % 360;

        Serial.print(F("🎯 Alinhamento Final | Bússola: "));
        Serial.println(Bussola);

        // Dentro da faixa de alinhamento
        if (Bussola >= BMin && Bussola <= BMax) {
          parar();
          Serial.println(F("✅ Alinhado no gol! CHUTANDO..."));
          delay(300);
          chutar();
          chutou = true;
          break;
        }

        // Fora da faixa → corrija pelo lado definido
        if (quebra == 'E') {
          if (BMin < Bussola && Bussola < limite) rotacionar("Esq", VELOCIDADE_ROTACAO);
          else rotacionar("Dir", VELOCIDADE_ROTACAO);
        } else {
          if (BMax > Bussola && Bussola > limite) rotacionar("Dir", VELOCIDADE_ROTACAO);
          else rotacionar("Esq", VELOCIDADE_ROTACAO);
        }

        delay(50);
      }

      break; // sai do while principal após chute
    }

    // --- Movimento normal com correção ---
    int diferenca = (gol - Bussola + 360) % 360;
    int diferencaAbs = (diferenca > 180) ? 360 - diferenca : diferenca;

    if (diferencaAbs > 25) {
      Serial.println(F("⚠️ Grande desalinhamento. Corrigindo..."));
      parar();
      if (diferenca <= 180) rotacionar("Dir", VELOCIDADE_ROTACAO);
      else rotacionar("Esq", VELOCIDADE_ROTACAO);
    } else {
      // Correção leve usando ultrassônicos
      int difLateral = abs(direitaDist - esquerdaDist);

      if (difLateral <= 25) {
        Serial.println(F("✅ Indo para o gol com pequena correção..."));
        frente(190);
      } else if (direitaDist < esquerdaDist) {
        Serial.println(F("⬅️ Ligeira correção para a esquerda..."));
        lateral("Esq", 100);
      } else {
        Serial.println(F("➡️ Ligeira correção para a direita..."));
        lateral("Dir", 100);
      }
    }

    delay(100);
  }
}




 // tolerância em graus


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

    if (PrimeiraLeitura) {
        gol = Bussola;
        limite = gol > 180 ? gol - 180 : gol + 180;
        quebra = gol > 180 ? 'D' : 'E';
        BMax = gol + 5;
        BMin = gol - 5;
        PrimeiraLeitura = false;
    }

    // Loop até estar alinhado
    while (true) {
        // Atualiza a leitura da bússola
        Wire.beginTransmission(compassAddress);
        Wire.write(0x44);
        Wire.endTransmission();

        Wire.requestFrom(compassAddress, 2);
        while (Wire.available() < 2)
            ;
        lowbyte = Wire.read();
        highbyte = Wire.read();
        Bussola = word(highbyte, lowbyte);

        // Verifica alinhamento
        if (Bussola >= BMin && Bussola <= BMax) {
            Alinhado = true;
            parar(); // Para o movimento
            break;   // Sai do loop
        } else {
            Alinhado = false;
            if (quebra == 'E') {
                if (BMin < Bussola && Bussola < limite) rotacionar("Esq", Curvas);
                else rotacionar("Dir", Curvasa);
            } else {
                if (BMax > Bussola && Bussola > limite) rotacionar("Dir", Curvas);
                else rotacionar("Esq", Curvasa);
            }
        }
        delay(50); // Pequena pausa para estabilizar leitura
    }

    // Após alinhamento, verifica a chave e chuta
    estado = digitalRead(pinoChave);
    if (Alinhado && estado == HIGH) {
      delay(300);
      rotacionar("Esq", 110);
      delay(100);
      parar();
        chutar();
    }
}

void alinhar(byte velocidade) {
  ReadCompassSensor();

  while (true) {
    ReadCompassSensor();

    int dif = gol - Bussola;
    if (dif > 180) dif -= 360;
    if (dif < -180) dif += 360;

    Serial.print("Bussola: "); Serial.print(Bussola);
    Serial.print(" | Gol: "); Serial.print(gol);
    Serial.print(" | Dif: "); Serial.println(dif);

    if (abs(dif) <= tolerancia) break;

    if (dif > 0) {
      rotacionar("e", velocidade);  // precisa aumentar ângulo → gira esquerda
    } else {
      rotacionar("d", velocidade);  // precisa diminuir ângulo → gira direita
    }
  }

  parar();
  Alinhado = true;
}
void alinharNoMeioHorizontal(int velocidadeBase) {
  // --- Variáveis estáticas para o alinhamento de bússola ---
  static bool PrimeiraLeitura = true;
  static int gol, limite, BMax, BMin;
  static char quebra;

  // --- Primeira leitura da bússola define referência ---
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);
  Wire.endTransmission();
  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2);
  byte low = Wire.read();
  byte high = Wire.read();
  int Bussola = word(high, low) % 360;

  if (PrimeiraLeitura) {
    gol = Bussola;
    limite = (gol > 180) ? gol - 180 : gol + 180;
    quebra = (gol > 180) ? 'D' : 'E';
    BMax = gol + TOLERANCIA_ANGULAR;
    BMin = gol - TOLERANCIA_ANGULAR;
    PrimeiraLeitura = false;
  }

  unsigned long inicio = millis();
  const unsigned long tempoMaximo = 5000; // 5s cada etapa máx.

  // === ETAPA 1: Alinhamento pela bússola (girar) ===
  bool alinhadoBussola = false;
  while (!alinhadoBussola && (millis() - inicio < tempoMaximo)) {
    // Ler bússola
    Wire.beginTransmission(compassAddress);
    Wire.write(0x44);
    Wire.endTransmission();
    Wire.requestFrom(compassAddress, 2);
    while (Wire.available() < 2);
    low = Wire.read();
    high = Wire.read();
    Bussola = word(high, low) % 360;

    Serial.print(F("🎯 Bússola: "));
    Serial.println(Bussola);

    if (Bussola >= BMin && Bussola <= BMax) {
      alinhadoBussola = true;
      parar();
      Serial.println(F("✅ Alinhado pelo gol (rotação concluída)"));
      break;
    }

    if (quebra == 'E') {
      if (BMin < Bussola && Bussola < limite) rotacionar("Esq", velocidadeBase);
      else rotacionar("Dir", velocidadeBase);
    } else {
      if (BMax > Bussola && Bussola > limite) rotacionar("Dir", velocidadeBase);
      else rotacionar("Esq", velocidadeBase);
    }

    delay(50);
  }

  if (!alinhadoBussola) {
    parar();
    Serial.println(F("⏱ Timeout - Não alinhou pelo gol"));
    return;
  }

  // === ETAPA 2: Alinhamento lateral (ultrassônicos) ===
  bool centralizadoLateral = false;
  inicio = millis(); // reinicia cronômetro
  while (!centralizadoLateral && (millis() - inicio < tempoMaximo)) {
    int leituraEsq = UltraE.read();
    int leituraDir = UltraD.read();

    if (leituraEsq > 72 && leituraEsq < 83 &&
        leituraDir > 72 && leituraDir < 83) {
      centralizadoLateral = true;
      parar();
      Serial.println(F("✅ Centralizado lateralmente"));
      break;
    }

    int erroEsq = leituraEsq - 77;
    int erroDir = leituraDir - 77;

    int ajusteVel = min(velocidadeBase, abs(erroEsq - erroDir) * 3);
    ajusteVel = max(50, ajusteVel);

    if (erroEsq > 2 && erroDir < -2) {
      lateral("Esq", ajusteVel);
    }
    else if (erroEsq < -2 && erroDir > 2) {
      lateral("Dir", ajusteVel);
    }

    delay(50);
  }

  if (!centralizadoLateral) {
    parar();
    Serial.println(F("⏱ Timeout - Não centralizou lateral"));
  }
}

void linhagoleiro(){
  refletancia = analogRead(RefleFrt);                          // 'refletancia' para leitura de analógico de 'SensorFrtD'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' seja maior ou igual que [BrancoMin] e 'refletancia' menor ou igual que [BrancoMax]...
    frente(150);                                                 // Movimentar atrás na velocidade [110]
    delay(300);                                                // Esperar [300] milissegundos
  }
    refletancia = analogRead(RefleEsq);                          // 'refletancia' para leitura de analógico de 'SensorFrtE'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' for maior ou igual que [BrancoMin] e 'refletancia' for menor ou igual que [BrancoMax]...
    frente(150);                                                 // Movimentar atrás na velocidade [110]
                                                  // Esperar [300] milissegundos
  }
  refletancia = analogRead(RefleDrt);                          // 'refletancia' para leitura de analógico de 'SensorFrtD'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' seja maior ou igual que [BrancoMin] e 'refletancia' menor ou igual que [BrancoMax]...
    frente(150);                                                 // Movimentar atrás na velocidade [110]
                                                   // Esperar [300] milissegundos
  }
}


