// Seguir o infravermelho da bola
void seguebola() {                                         // Define 'seguebola' para...
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Inicia leitura de infravermelho
  ballDirecao = InfraredBall.Direction;                    // 'ballDirecao' será definida pela direção recebida pelo infravermelho
  ballIntensi = InfraredBall.Strength;                     // 'ballIntensi' será definida para força recebida do infravermelho

  linhas();  // Executa função 'linhas'

  if (ballDirecao == 0) {  // Se 'ballDirecao' estiver [Desligada/Longe]...
    frente(120);           // Andar para frente na velocidade [120]
    Serial.println("0");   // Retorna Serial
    delay(50);             // Esperar Tempo
  }

  if (ballDirecao <= 9 && ballDirecao >= 6) {  // Se 'ballDirecao' estiver a [Direita]...
    rotacionar("Dir", Curvas);                 // Rotacionar para [Direita] na velocidade [Curvas]
    Serial.println("A");                       // Retorna Serial
    delay(50);                                 // Esperar Tempo
  }
  if (ballDirecao >= 1 && ballDirecao <= 4) {  // Se 'ballDirecao' estiver a [Esquerda]...
    rotacionar("Esq", Curvas);                 // Rotacionar para [Esquerda] na velocidade [Curvas]
    Serial.println("B");                       // Retorna Serial
    delay(50);                                 // Esperar Tempo
  }
  if (ballDirecao == 5 || ballIntensi >= IntensiMin) {  // Se 'ballDirecao' estiver a [Frente]...
    frente(Correr);                                     // Movimentar a frente na velocidade [Correr]
    Serial.println("C");                                // Retorna Serial
    delay(50);                                          // Esperar Tempo
  }
}

// Impedir que saia das linhas Brancas
void linhas() {  // Define 'linhas' para...
  // InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Inicia leitura de infravermelho
  // ballDirecao = InfraredBall.Direction;                    // 'ballDirecao' será definida pela direção recebida pelo infravermelho
  // ballIntensi = InfraredBall.Strength;                     // 'ballIntensi' será definida para força recebida do infravermelho

  // if (UltraF.read() < 15 && ballIntensi < IntensiMin) {
  //   tras(110);
  //   delay(300);
  // }
  refletancia = analogRead(RefleEsq);                          // 'refletancia' para leitura de analógico de 'SensorFrtE'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' for maior ou igual que [BrancoMin] e 'refletancia' for menor ou igual que [BrancoMax]...
    tras(110);                                                 // Movimentar atrás na velocidade [110]
    delay(300);                                                // Esperar [300] milissegundos
  }
  refletancia = analogRead(RefleDrt);                          // 'refletancia' para leitura de analógico de 'SensorFrtD'
  if (refletancia >= BrancoMin && refletancia <= BrancoMax) {  // Caso 'refletancia' seja maior ou igual que [BrancoMin] e 'refletancia' menor ou igual que [BrancoMax]...
    tras(110);                                                 // Movimentar atrás na velocidade [110]
    delay(300);                                                // Esperar [300] milissegundos
  }
}

void ReadCompassSensor() {                 // Define 'ReadCompassSensor' para...
  Wire.beginTransmission(compassAddress);  // Iniciar trasmissão da bússola
  Wire.write(0x44);                        // Modo de escrita
  Wire.endTransmission();                  // Terminar trasmissão

  Wire.requestFrom(compassAddress, 2);  // Requirir 2 valores da bússola
  while (Wire.available() < 2)          // Caso informação chegue
    ;
  byte lowbyte = Wire.read();         // 'lowbyte' será valor lido
  byte highbyte = Wire.read();        // 'highbyte' será valor lido
  Bussola = word(highbyte, lowbyte);  // 'Bussola' será a junção de 'highbyte' e 'lowbyte'

  if (PrimeiraLeitura == true) {                                 // Caso 'PrimeiraLeitura' for verdadeira...
    gol = Bussola;                                               // 'gol' será bússola
    limite = gol > 180 ? gol - 180 : gol + 180;                  // 'limite' será definido para 'gol-180' caso 'gol' menor que 180, se não, 'limite' = 'gol + 180'
    quebra = gol > 180 ? 'D' : 'E';                              // 'quebra' será 'D' caso 'gol' maior que 180, se não, 'quebra' será 'E'
    BMax = gol + 3;                                              // 'BMax' será 'gol + 2'
    BMin = gol - 3;                                              // 'BMin' será 'gol - 2'
    PrimeiraLeitura = false;                                     // 'PrimeiraLeitura' será 'False'
  } else {                                                       // Senão...
    if (Bussola == gol || Bussola >= BMin && Bussola <= BMax) {  // Caso 'Bussola' igual a 'gol' ou 'Bussola' maior/igual que 'BMin' e 'Bussola' menor/igual que 'BMax' ...
      Alinhado = true;                                           // 'Alinhado' será verdadeiro
      parar();                                                   // 'parar' será acionado
    } else if (quebra == 'E') {                                  // Senão se 'quebra' for igual a 'E'...
      if (BMin < Bussola && Bussola < limite) {                  // Se 'BMin' for menor que 'Bussola' e 'Bussola' maior que limite'...
        Alinhado = false;                                        // 'Alinhado' será falso
        rotacionar("Esq", Curvas);                               // 'rotacionar' para [Esquerda] na velocidade [Curvas]
        delay(50);                                               // Esperar
      } else {                                                   // Senão...
        Alinhado = false;                                        // 'Alinhado' será falso
        rotacionar("Dir", Curvas);                               // 'rotacionar' para [Direita] na velocidade [Curvas]
        delay(50);                                               // Esperar
      }
    } else {                                     // Senão...
      if (BMax > Bussola && Bussola > limite) {  // Se 'BMax' for menor que 'Bussola' e 'Bussola' maior que 'limite'...
        Alinhado = false;                        // 'Alinhado' será falso
        rotacionar("Dir", Curvas);               // 'rotacionar' para [Direita] na velocidade [Curvas]
        delay(50);                               // Esperar
      } else {                                   // Senão...
        Alinhado = false;                        // 'Alinhado' será falso
        rotacionar("Esq", Curvas);               // 'rotacionar' para [Esquerda] na velocidade [Curvas]
        delay(50);                               // Esperar
      }
    }

    estado = digitalRead(chavecurso);  // 'estado' será a leitura digital da porta [chavecurso]

    if (!Alinhado && estado == HIGH) {        // Se 'Alinhado' for diferente e 'estado' for [LOW]...
      ReadCompassSensor();                    // Acionar 'ReadCompassSensor'
    } else if (Alinhado && estado == HIGH) {  // Senão se 'Alinhado' e 'estado' for [LOW]...
      int ULT = UltraF.read();
      if (ULT > 20 && ULT < 75) {
        chutar();
        return;
      } else {
        frente(150);
        delay(150);
        return;
      }
      // if (UltraD.read() < ParedeD && UltraE.read() > ParedeE) {
      //   rotacionar("Drt", 65);
      //   delay(150);
      //   lateral("Esq", 150);
      //   delay(400);
      //   return;
      // } else if (UltraE.read() < ParedeE && UltraD.read() > ParedeD) {
      //   rotacionar("Esq", 65);
      //   delay(150);
      //   lateral("Drt", 150);
      //   delay(400);
      //   return;
      // }
    }
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

  if (Modo == 1) {
    estado = digitalRead(chavecurso);
    Serial.print("Chave: ");
    Serial.print(estado);
    Serial.println("");

    Serial.print("Ultra Frente: ");
    Serial.print(UltraF.read());
    Serial.println("");
    /////////////
    Serial.print("Ultra Direita: ");
    Serial.print(UltraD.read());
    Serial.println("");
    /////////////
    Serial.print("Ultra Frente: ");
    Serial.print(UltraF.read());
    Serial.println("");

    refletancia = analogRead(RefleEsq);
    Serial.print("Sensor Frente Esquerda: ");
    Serial.print(refletancia);
    Serial.println("");

    refletancia = analogRead(RefleDrt);
    Serial.print("Sensor Frente Direita: ");
    Serial.print(refletancia);
    Serial.println("\n");
  } else {
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
  }

  delay(700);
}
