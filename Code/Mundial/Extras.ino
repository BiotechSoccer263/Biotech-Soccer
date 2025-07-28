void SeguirBola() {
  // Lê a direção e intensidade da bola usando o sensor infravermelho
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  // Lê refletâncias
  int refletanciaFrt = analogRead(FrtR);
  bool linhaDetectadaFrt = (refletanciaFrt >= BrancoMin && refletanciaFrt <= BrancoMax);

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
  if (ballDirecao == 5 || ballDirecao == 6 || ballDirecao == 4) {
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
  else if (ballDirecao == 0 || ballIntensi <= 25 || ballIntensi == 0) {
    frente(VeloFrente);  // Continua indo para frente para procurar a bola
  }
}

void chutarTeam() {
  const float Kp = 2.0;
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  const unsigned long tempoLimite = 2000;  // Tempo máximo do chute
  unsigned long inicio = millis();

  ReadCompassSensor();
  int headingAlvo = gol + 15;  // Objetivo: direção do gol

  while (1) {
    if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
      parar();
      break;
    } else {
      alinhar();
    }
  }

  while ((millis() - inicio) < tempoLimite) {
    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain((VeloFrente + 70) - ajuste, 0, 225);
    int velDir = constrain((VeloFrente + 70) + ajuste, 0, 225);

    setMotoresFrente(velEsq, velDir);

    // Critério de parada imediato se algo estiver muito próximo à frente
    if (UFrt.read() <= 40) {
      analogWrite(ENA_DRIBLER, 225);
      digitalWrite(IN1_DRIBLER, LOW);
      digitalWrite(IN2_DRIBLER, HIGH);
      break;
    }

    delay(30);
  }

  analogWrite(ENA_DRIBLER, 225);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);
  delay(150);
  parar();
  delay(100);
  dribler("On", 225);
  delay(250);
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
  int headingAlvo = gol - 10;  // Objetivo: direção do gol

  while ((millis() - inicio) < tempoLimite) {
    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain((VeloFrente + 90) - ajuste, 0, 225);
    int velDir = constrain((VeloFrente + 90) + ajuste, 0, 225);

    setMotoresFrente(velEsq, velDir);

    if ((millis() - inicio) > (tempoLimite / 2)) {
      analogWrite(ENA_DRIBLER, 225);
      digitalWrite(IN1_DRIBLER, LOW);
      digitalWrite(IN2_DRIBLER, HIGH);
    }

    // Critério de parada imediato se algo estiver muito próximo à frente
    if (UFrt.read() <= 35) {
      analogWrite(ENA_DRIBLER, 225);
      digitalWrite(IN1_DRIBLER, LOW);
      digitalWrite(IN2_DRIBLER, HIGH);
      break;
    }

    delay(30);
  }

  parar();
  delay(100);
  tras(130);
  delay(500);
  parar();
  delay(100);
  dribler("On", 225);
  delay(250);
}

void chutargoleiro() {
  frentePID(200, 750);

  analogWrite(ENA_DRIBLER, 255);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  parar();
  delay(100);
  dribler("On", 225);
}