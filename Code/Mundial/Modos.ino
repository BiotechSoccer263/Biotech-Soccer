void atacante() {
  SeguirBola();  // Função que faz o robô seguir a bola detectada pelo sensor infravermelho

  if (digitalRead(chavecurso) == 1) {  // Se a chave física estiver pressionada
    conduzirBola(135);  // Executa a função de alinhamento com o gol
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
    frentePID(VeloFrente, 250);
  } else if (linhaDetectadaEsq && !linhaDetectadaDir) {
    lateralPID("d", VeloFrente, 500);
    return;
  } else if (linhaDetectadaDir && !linhaDetectadaEsq) {
    lateralPID("e", VeloFrente, 500);
    return;
  }

  manterDistanciaTrasPID(VeloFrente);
  alinhar();

  if (digitalRead(chavecurso) == 1) {
    chutargoleiro();
  }

  if (ballDirecao == 9 || ballDirecao == 0 || ballDirecao == 1) {
    return;
  }

  if (ballDirecao < 5 && UEsq.read() >= 55) {
    lateralPID("e", VeloFrente, 500);
  } else if (ballDirecao > 5 && UDir.read() >= 55) {
    lateralPID("d", VeloFrente, 500);
  } else if (ballDirecao == 5 && UTrs.read() <= 65) {
    alinhar();
    frentePID(VeloFrente, 250);
  }
}

void manterDistanciaTrasPID(int velocidadeBase) {
  const float Kp = 2.0;
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();
  int headingAlvo = gol + 25;

  alinhar();
  delay(10);

  while (true) {
    if (digitalRead(Menu) == LOW && Tela == true) {
      break;
    }

    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    ballDirecao = InfraredBall.Direction;
    ballIntensi = InfraredBall.Strength;
    int distancia = UTrs.read();

    if (distancia >= 5 && distancia <= 50) {
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

    if (distancia > 50) {
      // Está muito perto → anda para trás
      velEsq = constrain(velocidadeBase + ajuste, 0, 255);
      velDir = constrain(velocidadeBase - ajuste, 0, 255);
      setMotoresTras(velEsq, velDir);
    } else if (distancia < 5) {
      // Está muito longe → anda para frente
      velEsq = constrain(velocidadeBase - ajuste, 0, 255);
      velDir = constrain(velocidadeBase + ajuste, 0, 255);
      setMotoresFrente(velEsq, velDir);
    }

    delay(30);
  }

  parar();
}