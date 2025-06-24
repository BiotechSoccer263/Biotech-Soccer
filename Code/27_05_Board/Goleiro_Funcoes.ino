void goleiro_infra() {                                     // Definir 'goleiro_infra' para...
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();  // Inicia leitura de infravermelho
  ballDirecao = InfraredBall.Direction;                    // 'ballDirecao' será definida pela direção recebida pelo infravermelho
  ballIntensi = InfraredBall.Strength;                     // 'ballIntensi' será definida para força recebida do infravermelho

  Wire.beginTransmission(compassAddress);  // Iniciar trasmissão da bússola
  Wire.write(0x44);                        // Modo de escrita
  Wire.endTransmission();                  // Terminar trasmissão

  Wire.requestFrom(compassAddress, 2);  // Requirir 2 valores da bússola
  while (Wire.available() < 2)          // Caso informação chegue
    ;
  byte lowbyte = Wire.read();         // 'lowbyte' será valor lido
  byte highbyte = Wire.read();        // 'highbyte' será valor lido
  Bussola = word(highbyte, lowbyte);  // 'Bussola' será a junção de 'highbyte' e 'lowbyte'

  parar();

  // Bússola
  if (Bussola <= BMax && Bussola >= BMin) {  // Se 'Bussola' for menor/igual que 'BMax' e 'Bussola' for maior/igual que 'BMin'...
    Alinhado = true;                         // 'Alinhado' será verdadeiro
  } else {                                   // Senão...
    Alinhado = false;                        // 'Alinhado' será falso
  }

  if (Alinhado) {                              // Se 'Alinhado'...
    parar();                                   // Parar movimentação
  } else if (quebra == 'E') {                  // Senão se 'quebra' for igual a 'E'...
    if (BMin < Bussola && Bussola < limite) {  // Se 'BMin' for menor que 'Bussola' e 'Bussola' maior que 'Limite'...
      rotacionar("Esq", 65);                   // 'rotacionar' para [Esquerda] na velocidade [45]
      return;                                  // Esperar
      delay(50);
    } else {                  // Senão...
      rotacionar("Dir", 65);  // 'rotacionar' para [Direita] na velocidade [45]
      delay(20);              // Esperar
      return;
    }
  } else {                                     // Senão...
    if (BMax > Bussola && Bussola > limite) {  // Se 'BMax' for maior que 'Bussola' e 'Bussola' maior que 'Limite'...
      rotacionar("Dir", 65);                   // 'rotacionar' para [Direita] na velocidade [45]
      delay(20);                               // Esperar
    } else {                                   // Senão...
      rotacionar("Esq", 65);                   // 'rotacionar' para [Esquerda] na velocidade [45]
      delay(20);                               // Esperar
    }
  }

  if (!Alinhado) return;  // Caso 'Alinhado' for diferente = Retornar função

  int Ultra = UltraT.read();
  if (Ultra < ParedeT) {
    frente(100);
    delay(50);
  } else if (Ultra >= 60 || Ultra > 35 && ballIntensi > 80) {
    tras(100);
    delay(50);
  }

  if (ballDirecao > 5) {
    lateral("Drt", 200);
    delay(200);
    return;
  } else if (ballDirecao < 5) {
    lateral("Esq", 200);
    delay(200);
    return;
  }
}