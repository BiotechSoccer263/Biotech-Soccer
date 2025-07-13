void SeguirBola() {
  // Reads the direction and strength of the ball using the infrared sensor
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;  // Ball direction (0–9, where 5 is center)
  ballIntensi = InfraredBall.Strength;   // Ball signal strength

  // Reads reflectance from the front sensor to detect white line (field boundary)
  int refletanciaFrt = analogRead(FrtR);

  // Checks if white line is detected in front (to avoid leaving the field)
  bool linhaDetectadaFrt = (refletanciaFrt >= BrancoMin && refletanciaFrt <= BrancoMax);

  // If white line is detected in front, stop and move backward
  if (linhaDetectadaFrt) {
    parar();
    delay(50);
    tras(VeloFrente);
    delay(350);
    return;
  }

  // Print ball strength and direction to serial monitor for debugging
  Serial.println(ballIntensi);
  Serial.println(ballDirecao);

  // Movement logic based on ball direction
  if (ballDirecao >= 4 && ballDirecao <= 6 && ballIntensi >= 25) {
    // Ball is in front and strong enough
    frente(VeloFrente);
  } else if (ballDirecao < 4) {
    // Ball is to the left
    rotacionar("e", VeloCurva);
  } else if (ballDirecao > 6) {
    // Ball is to the right
    rotacionar("d", VeloCurva);
  } else if (ballDirecao == 0 || ballIntensi <= 10) {
    // Ball not detected, move forward to search
    frente(VeloFrente);
  }
}

void chutar() {
  // PID parameters for aligning with the goal
  const float Kp = 2.0;
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  const unsigned long tempoLimite = 3000;  // Max time allowed for alignment and kick
  unsigned long inicio = millis();

  ReadCompassSensor();             // Get initial compass reading
  int headingAlvo = gol - 10;      // Target heading: goal direction

  // PID control loop for alignment
  while ((millis() - inicio) < tempoLimite) {
    ReadCompassSensor();
    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    // Compute PID adjustment
    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain((VeloFrente + 25) - ajuste, 0, 225);
    int velDir = constrain((VeloFrente + 25) + ajuste, 0, 225);

    // Move forward while adjusting orientation
    setMotoresFrente(velEsq, velDir);

    // Activate dribbler in reverse after half of the time
    if ((millis() - inicio) > (tempoLimite / 2)) {
      analogWrite(ENA_DRIBLER, 225);
      digitalWrite(IN1_DRIBLER, LOW);
      digitalWrite(IN2_DRIBLER, HIGH);
    }

    // Stop immediately if something is too close in front
    if (UFrt.read() <= 30) {
      break;
    }

    delay(30);
  }

  // Ensure the dribbler runs in reverse to kick even after timeout
  analogWrite(ENA_DRIBLER, 225);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  // Brief retreat after the kick
  parar();
  delay(100);
  tras(150);
  delay(400);

  parar();
  dribler("On", 225);  // Reactivate dribbler in normal mode
  delay(150);
}

void chutargoleiro() {
  // Move forward in a straight line with PID for a fixed time/distance
  frentePID(200, 450);

  // Kick the ball by activating the dribbler in reverse
  analogWrite(ENA_DRIBLER, 255);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  // Stop briefly after the kick, then restart dribbler normally
  parar();
  delay(100);
  dribler("On", 225);
}