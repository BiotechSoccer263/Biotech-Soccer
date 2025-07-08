void atacante() {
  SeguirBola();  // Função que faz o robô seguir a bola detectada pelo sensor infravermelho

  if (digitalRead(chavecurso) == 1) {  // Se a chave física estiver pressionada
    conduzirBola(135);                 // Executa a função de alinhamento com o gol
  }
}

void goleiro() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  int refletanciaEsq = analogRead(EsqR);
  int refletanciaDir = analogRead(DirR);
  bool linhaDetectadaEsq = (refletanciaEsq >= BrancoMin && refletanciaEsq <= BrancoMax);
  bool linhaDetectadaDir = (refletanciaDir >= BrancoMin && refletanciaDir <= BrancoMax);

  if (linhaDetectadaEsq && linhaDetectadaDir) {
    frentePID(120, 250);
  } else if (linhaDetectadaEsq && !linhaDetectadaDir) {
    lateralPID("d", 120, 500);
  } else if (linhaDetectadaDir && !linhaDetectadaEsq) {
    lateralPID("e", 120, 500);
  }

  manterDistanciaTrasPID(120);
  corrigirAlinhamento(gol);

  if (digitalRead(chavecurso) == 1) {
    chutargoleiro();
  }

  if (ballDirecao < 5 && UEsq.read() >= 35) {
    lateralPID("e", 110, 500);
  } else if (ballDirecao > 5 && UDir.read() >= 35) {
    lateralPID("d", 110, 500);
  } else if (ballDirecao == 5 && UTrs.read() <= 65) {
    corrigirAlinhamento(gol);
    frentePID(140, 250);
  }
}

void manterDistanciaTrasPID(int velocidadeBase) {
  const float Kp = 2.0;
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();
  int headingAlvo = gol + 10;

  while (true) {
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    ballDirecao = InfraredBall.Direction;
    ballIntensi = InfraredBall.Strength;
    int distancia = UTrs.read();

    if (distancia >= 35 && distancia <= 50) {
      parar();  // Dentro da margem desejada
      break;
    }

    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = 0, velDir = 0;

    if (distancia > 35) {
      // Está muito perto → anda para trás
      velEsq = constrain(velocidadeBase + ajuste, 0, 255);
      velDir = constrain(velocidadeBase - ajuste, 0, 255);
      setMotoresTras(velEsq, velDir);
    } else if (distancia < 50) {
      // Está muito longe → anda para frente
      velEsq = constrain(velocidadeBase - ajuste, 0, 255);
      velDir = constrain(velocidadeBase + ajuste, 0, 255);
      setMotoresFrente(velEsq, velDir);
    }

    delay(30);
  }

  parar();
}

void corrigirAlinhamento(int alvo) {
  ReadCompassSensor();

  int BX = alvo + 1;
  int BN = alvo - 1;

  if (Bussola >= BN && Bussola <= BX) {
    parar();
    return;
  } else if (quebra == 'E') {
    if (BN <= Bussola && Bussola < limite) {
      rotacionar("e", VeloCurva);
    } else {
      rotacionar("d", VeloCurva);
    }
  } else {
    if (BX >= Bussola && Bussola > limite) {
      rotacionar("d", VeloCurva);
    } else {
      rotacionar("e", VeloCurva);
    }
  }
}