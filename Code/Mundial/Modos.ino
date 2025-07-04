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

  Serial.println(ballDirecao);

  if (digitalRead(chavecurso) == 1) {
    chutargoleiro();
  }

  ReadCompassSensor();
  corrigirAlinhamento();

  int distTraseiro = UTrs.read();

  if (distTraseiro >= 55) {
    tras(VeloFrente);
    delay(200);
  } else if (distTraseiro <= 40) {
    frente(VeloFrente);
    delay(200);
  }

  // Corrigir alinhamento novamente após movimento
  ReadCompassSensor();
  corrigirAlinhamento();

  if (ballDirecao < 5 && UEsq.read() >= 40) {
    lateralGoleiroPorTempo("e", VeloFrente, 500);
  } else if (ballDirecao > 5 && UDir.read() >= 40) {
    lateralGoleiroPorTempo("d", VeloFrente, 500);
  } else if (ballDirecao == 5) {
    parar();
  }
}

void corrigirAlinhamento() {
  if (quebra == 'E') {
    if (BMin <= Bussola && Bussola < limite) {
      rotacionar("e", VeloCurva);
    } else {
      rotacionar("d", VeloCurva);
    }
  } else {
    if (BMax >= Bussola && Bussola > limite) {
      rotacionar("d", VeloCurva);
    } else {
      rotacionar("e", VeloCurva);
    }
  }
}