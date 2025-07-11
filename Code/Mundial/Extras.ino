void SeguirBola() {
  // Lê a direção e intensidade da bola usando o sensor infravermelho
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  // Lê refletâncias
  int refletanciaFrt = analogRead(FrtR);
  // int refletanciaEsq = analogRead(EsqR);
  // int refletanciaDir = analogRead(DirR);

  // Se qualquer sensor detectar faixa branca (para não sair da área)
  bool linhaDetectadaFrt = (refletanciaFrt >= BrancoMin && refletanciaFrt <= BrancoMax);
  // bool linhaDetectadaEsq = (refletanciaEsq >= BrancoMin && refletanciaEsq <= BrancoMax);
  // bool linhaDetectadaDir = (refletanciaDir >= BrancoMin && refletanciaDir <= BrancoMax);

  // if (linhaDetectadaEsq && !linhaDetectadaDir && !linhaDetectadaFrt) {
  //   tras(110);
  //   delay(350);
  //   rotacionar("d", 90);  // Fugir para o lado oposto ao que detectou
  //   delay(200);
  //   return;
  // }

  // if (linhaDetectadaDir && !linhaDetectadaEsq && !linhaDetectadaFrt) {
  //   tras(110);
  //   delay(350);
  //   rotacionar("e", 90);  // Fugir para o lado oposto ao que detectou
  //   delay(200);
  //   return;
  // }

  if (linhaDetectadaFrt) {
    parar();
    delay(50);
    tras(VeloFrente);
    delay(350);
    return;
  }

  // Mostra no Serial a intensidade e direção da bola
  Serial.println(ballIntensi);
  Serial.println(ballDirecao);

  // Se a bola está à frente (direção entre 4 e 6) e com intensidade razoável
  if (ballDirecao >= 4 && ballDirecao <= 6 && ballIntensi >= 25) {
    frente(VeloFrente);  // Move para frente na velocidade definida
  }
  // Se a bola está à esquerda (direção <4)
  else if (ballDirecao < 4) {
    rotacionar("e", VeloCurva);  // Rotaciona para a esquerda
  }
  // Se a bola está à direita (direção >6)
  else if (ballDirecao > 6) {
    rotacionar("d", VeloCurva);  // Rotaciona para a direita
  }
  // Se não detectou a bola (direção 0 ou intensidade muito baixa)
  else if (ballDirecao == 0 || ballIntensi <= 10) {
    frente(VeloFrente);  // Continua indo para frente para procurar a bola
  }
}

void chutar() {
  const float Kp = 2.0;
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  const unsigned long tempoLimite = 3000;  // Tempo máximo do chute
  unsigned long inicio = millis();

  ReadCompassSensor();
  int headingAlvo = gol-10;  // Objetivo: direção do gol

  while ((millis() - inicio) < tempoLimite) {
    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain((VeloFrente+25) - ajuste, 0, 225);
    int velDir = constrain((VeloFrente+25) + ajuste, 0, 225);

    setMotoresFrente(velEsq, velDir);

    if ((millis() - inicio) > (tempoLimite / 2)) {
      analogWrite(ENA_DRIBLER, 225);
      digitalWrite(IN1_DRIBLER, LOW);
      digitalWrite(IN2_DRIBLER, HIGH);
    }

    // Critério de parada imediato se algo estiver muito próximo à frente
    if (UFrt.read() <= 30) {
      break;
    }

    delay(30);
  }

  analogWrite(ENA_DRIBLER, 225);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  parar();
  delay(100);
  tras(150);
  delay(400);

  parar();
  dribler("On", 225);
  delay(150);
}

void chutargoleiro() {
  frentePID(200, 450);

  analogWrite(ENA_DRIBLER, 255);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  parar();
  delay(100);
  dribler("On", 225);
}