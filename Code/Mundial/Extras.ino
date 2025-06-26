void SeguirBola() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  int chave = digitalRead(chavecurso);
  refletancia = analogRead(FrtR);

  if (refletancia <= BrancoMax && refletancia >= BrancoMin) {
    tras(150);
    delay(350);
    return;
  }

  Serial.println(ballIntensi);
  Serial.println(ballDirecao);

  if (ballDirecao >= 4 && ballDirecao <= 6 && ballIntensi >= 25) {
    frente(VeloFrente);
  } else if (ballDirecao < 4) {
    rotacionar("e", VeloCurva);
    delay(50);
  } else if (ballDirecao > 6) {
    rotacionar("d", VeloCurva);
    delay(50);
  } else if (ballDirecao == 0 || ballIntensi <= 10) {
    frente(VeloFrente);
  }

  delay(100);
}

void chutar() {
  analogWrite(ENA_DRIBLER, 220);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  frente(220);
  delay(400);
  tras(180);
  delay(500);
  parar();
  dribler("On", 225);
}