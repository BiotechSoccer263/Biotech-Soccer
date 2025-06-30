void SeguirBola() {
  // Lê a direção e intensidade da bola usando o sensor infravermelho
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  // Lê o estado da chave e a refletância do sensor frontal
  int chave = digitalRead(chavecurso);
  refletancia = analogRead(FrtR);

  // Se detectar faixa branca à frente (usado para não sair da área)
  if (refletancia <= BrancoMax && refletancia >= BrancoMin) {
    tras(150);          // Move o robô para trás
    delay(350);         // Espera 350ms
    return;             // Sai da função, não executa o resto
  }

  // Mostra no Serial a intensidade e direção da bola
  Serial.println(ballIntensi);
  Serial.println(ballDirecao);

  // Se a bola está à frente (direção entre 4 e 6) e com intensidade razoável
  if (ballDirecao >= 4 && ballDirecao <= 6 && ballIntensi >= 25) {
    frente(VeloFrente); // Move para frente na velocidade definida
  }
  // Se a bola está à esquerda (direção <4)
  else if (ballDirecao < 4) {
    rotacionar("e", VeloCurva); // Rotaciona para a esquerda
    delay(80);                  // Pequena pausa para o movimento acontecer
  }
  // Se a bola está à direita (direção >6)
  else if (ballDirecao > 6) {
    rotacionar("d", VeloCurva); // Rotaciona para a direita
    delay(80);
  }
  // Se não detectou a bola (direção 0 ou intensidade muito baixa)
  else if (ballDirecao == 0 || ballIntensi <= 10) {
    frente(VeloFrente); // Continua indo para frente para procurar a bola
  }

  delay(100); // Pausa para evitar atualizações muito rápidas
}

void chutar() {
  // Liga o dribler em reverso (para empurrar a bola)
  analogWrite(ENA_DRIBLER, 220);
  digitalWrite(IN1_DRIBLER, LOW);
  digitalWrite(IN2_DRIBLER, HIGH);

  // Avança rapidamente para dar o chute
  frente(220);
  delay(400);

  // Recuo após o chute para reposicionar
  tras(180);
  delay(500);

  // Para completamente os motores
  parar();

  // Liga o dribler novamente para segurar a bola
  dribler("On", 225);
}