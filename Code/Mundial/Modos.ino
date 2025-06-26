void atacante() {
  SeguirBola();

  if (digitalRead(chavecurso) == 1) {
    alinhar();
  }
}

void goleiro() {
  // Leitura do sensor infravermelho
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  Serial.println(ballDirecao);

  // Aciona chute se chave estiver pressionada
  if (digitalRead(chavecurso) == 1) {
    chutar();
  }

  // Movimentação com base nos sensores ultrassônicos frontal e traseiro
  if (UTrs.read() >= 55) {
    tras(150);
    delay(200);
  } else if (UTrs.read() <= 20 && ballDirecao >= 4 && ballDirecao <= 6) {
    frente(150);
    delay(200);
  }

  // Leitura da bússola e correção de alinhamento
  ReadCompassSensor();

  Alinhado = false;  // Sempre será reavaliado aqui

  if (quebra == 'E') {
    if (BMin <= Bussola && Bussola < limite) {
      Alinhado = false;
      rotacionar("e", VeloCurva);  // "e" para esquerda
      delay(50);
    } else {
      Alinhado = false;
      rotacionar("d", VeloCurva);  // "d" para direita
      delay(50);
    }
  } else {
    if (BMax >= Bussola && Bussola > limite) {
      Alinhado = false;
      rotacionar("d", VeloCurva);  // "d" para direita
      delay(50);
    } else {
      Alinhado = false;
      rotacionar("e", VeloCurva);  // "e" para esquerda
      delay(50);
    }
  }

  // Lateralidade com base na direção da bola e nos sensores laterais
  if (ballDirecao < 5 && UEsq.read() >= 40) {
    lateral("e", 140);
    delay(350);
  } else if (ballDirecao > 5 && UDir.read() >= 40) {
    lateral("d", 140);
    delay(350);
  } else {
    parar();
  }
}