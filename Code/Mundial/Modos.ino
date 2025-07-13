void atacante() {
  SeguirBola();  // Function that makes the robot follow the ball detected by the IR sensor

  if (digitalRead(chavecurso) == 1) {  // If the physical switch is pressed
    conduzirBola(135);                 // Executes goal alignment function
  }
}

void goleiro() {
  // Read ball data from the IR seeker
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  // Read reflectance sensors to detect white boundary lines
  int refletanciaEsq = analogRead(EsqR);
  int refletanciaDir = analogRead(DirR);
  bool linhaDetectadaEsq = (refletanciaEsq >= BrancoMin && refletanciaEsq <= BrancoMax);
  bool linhaDetectadaDir = (refletanciaDir >= BrancoMin && refletanciaDir <= BrancoMax);

  // React based on line detection
  if (linhaDetectadaEsq && linhaDetectadaDir) {
    // Both sensors detected line → move forward to return to field
    frentePID(VeloFrente, 250);
  } else if (linhaDetectadaEsq && !linhaDetectadaDir) {
    // Only left detected line → shift right
    lateralPID("d", VeloFrente, 500);
    return;
  } else if (linhaDetectadaDir && !linhaDetectadaEsq) {
    // Only right detected line → shift left
    lateralPID("e", VeloFrente, 500);
    return;
  }

  // Maintain a safe distance from the back wall using PID
  manterDistanciaTrasPID(VeloFrente);

  // Align to face forward
  alinhar();

  // If course switch is pressed, execute kick
  if (digitalRead(chavecurso) == 1) {
    chutargoleiro();
  }

  // If the ball is in an irrelevant or unreachable direction
  if (ballDirecao == 9 || ballDirecao == 0 || ballDirecao == 1) {
    return;
  }

  // Move laterally based on ball direction and side distances
  if (ballDirecao < 5 && UEsq.read() >= 55) {
    lateralPID("e", VeloFrente, 500);  // Ball is on the left
  } else if (ballDirecao > 5 && UDir.read() >= 55) {
    lateralPID("d", VeloFrente, 500);  // Ball is on the right
  } else if (ballDirecao == 5 && UTrs.read() <= 65) {
    alinhar();                         // Ball directly in front and close to goal
    frentePID(VeloFrente, 250);       // Move forward to block or clear
  }
}

void manterDistanciaTrasPID(int velocidadeBase) {
  // PID constants for compass correction
  const float Kp = 2.0;
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();
  int headingAlvo = gol + 10;  // Target heading slightly offset from goal

  while (true) {
    // Read ball position (for future extension or adaptive behavior)
    InfraredResult InfraredBall = InfraredSeeker::ReadAC();
    ballDirecao = InfraredBall.Direction;
    ballIntensi = InfraredBall.Strength;

    // Read rear distance sensor
    int distancia = UTrs.read();

    // If within acceptable range, stop
    if (distancia >= 35 && distancia <= 50) {
      parar();
      break;
    }

    // PID orientation correction
    ReadCompassSensor();
    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = 0, velDir = 0;

    if (distancia > 50) {
      // Too far → move forward
      velEsq = constrain(velocidadeBase - ajuste, 0, 255);
      velDir = constrain(velocidadeBase + ajuste, 0, 255);
      setMotoresFrente(velEsq, velDir);
    } else if (distancia < 35) {
      // Too close → move backward
      velEsq = constrain(velocidadeBase + ajuste, 0, 255);
      velDir = constrain(velocidadeBase - ajuste, 0, 255);
      setMotoresTras(velEsq, velDir);
    }

    delay(30);
  }

  parar();  // Stop motors after exiting loop
}