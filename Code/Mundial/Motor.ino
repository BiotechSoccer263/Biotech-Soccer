void frente(int velocidade) {
  // Motores do lado esquerdo para andar para frente
  digitalWrite(IN1_ESQ, LOW);
  digitalWrite(IN2_ESQ, HIGH);
  digitalWrite(IN3_ESQ, HIGH);
  digitalWrite(IN4_ESQ, LOW);
  analogWrite(ENA_ESQ, velocidade);
  analogWrite(ENB_ESQ, velocidade);

  // Motores do lado direito para andar para frente
  digitalWrite(IN1_DIR, LOW);
  digitalWrite(IN2_DIR, HIGH);
  digitalWrite(IN3_DIR, HIGH);
  digitalWrite(IN4_DIR, LOW);
  analogWrite(ENA_DIR, velocidade);
  analogWrite(ENB_DIR, velocidade);
}

void tras(int velocidade) {
  // Motores do lado esquerdo para andar para trás
  digitalWrite(IN1_ESQ, HIGH);
  digitalWrite(IN2_ESQ, LOW);
  digitalWrite(IN3_ESQ, LOW);
  digitalWrite(IN4_ESQ, HIGH);
  analogWrite(ENA_ESQ, velocidade);
  analogWrite(ENB_ESQ, velocidade);

  // Motores do lado direito para andar para trás
  digitalWrite(IN1_DIR, HIGH);
  digitalWrite(IN2_DIR, LOW);
  digitalWrite(IN3_DIR, LOW);
  digitalWrite(IN4_DIR, HIGH);
  analogWrite(ENA_DIR, velocidade);
  analogWrite(ENB_DIR, velocidade);
}

void parar() {
  // Desliga todos os motores do lado esquerdo
  digitalWrite(IN1_ESQ, LOW);
  digitalWrite(IN2_ESQ, LOW);
  digitalWrite(IN3_ESQ, LOW);
  digitalWrite(IN4_ESQ, LOW);

  // Desliga todos os motores do lado direito
  digitalWrite(IN1_DIR, LOW);
  digitalWrite(IN2_DIR, LOW);
  digitalWrite(IN3_DIR, LOW);
  digitalWrite(IN4_DIR, LOW);
}

void rotacionar(String lado, int velocidade) {
  if (lado == "e") {  // Rotacionar para ESQUERDA (sentido horário)
    // Motores da esquerda para trás
    digitalWrite(IN1_ESQ, HIGH);
    digitalWrite(IN2_ESQ, LOW);
    digitalWrite(IN3_ESQ, LOW);
    digitalWrite(IN4_ESQ, HIGH);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    // Motores da direita para frente
    digitalWrite(IN1_DIR, LOW);
    digitalWrite(IN2_DIR, HIGH);
    digitalWrite(IN3_DIR, HIGH);
    digitalWrite(IN4_DIR, LOW);
    analogWrite(ENA_DIR, velocidade);
    analogWrite(ENB_DIR, velocidade);

  } else if (lado == "d") {  // Rotacionar para DIREITA (sentido anti-horário)
    // Motores da esquerda para frente
    digitalWrite(IN1_ESQ, LOW);
    digitalWrite(IN2_ESQ, HIGH);
    digitalWrite(IN3_ESQ, HIGH);
    digitalWrite(IN4_ESQ, LOW);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    // Motores da direita para trás
    digitalWrite(IN1_DIR, HIGH);
    digitalWrite(IN2_DIR, LOW);
    digitalWrite(IN3_DIR, LOW);
    digitalWrite(IN4_DIR, HIGH);
    analogWrite(ENA_DIR, velocidade);
    analogWrite(ENB_DIR, velocidade);
  }
}

void lateral(String lado, int velocidade) {
  if (lado == "e") {  // Movimento lateral para ESQUERDA
    // Motores do lado esquerdo para frente e do lado direito para trás (movimento diagonal)
    digitalWrite(IN1_ESQ, LOW);
    digitalWrite(IN2_ESQ, HIGH);
    digitalWrite(IN3_ESQ, LOW);
    digitalWrite(IN4_ESQ, HIGH);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    digitalWrite(IN1_DIR, LOW);
    digitalWrite(IN2_DIR, HIGH);
    digitalWrite(IN3_DIR, LOW);
    digitalWrite(IN4_DIR, HIGH);
    analogWrite(ENA_DIR, velocidade);
    analogWrite(ENB_DIR, velocidade);

  } else if (lado == "d") {  // Movimento lateral para DIREITA
    // Motores do lado esquerdo para trás e do lado direito para frente (movimento diagonal)
    digitalWrite(IN1_ESQ, HIGH);
    digitalWrite(IN2_ESQ, LOW);
    digitalWrite(IN3_ESQ, HIGH);
    digitalWrite(IN4_ESQ, LOW);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    digitalWrite(IN1_DIR, HIGH);
    digitalWrite(IN2_DIR, LOW);
    digitalWrite(IN3_DIR, HIGH);
    digitalWrite(IN4_DIR, LOW);
    analogWrite(ENA_DIR, velocidade);
    analogWrite(ENB_DIR, velocidade);
  }
}

void lateralGoleiroPorTempo(String lado, int velocidadeBase, unsigned long tempoMovimento) {
  const float Kp = 1.5;
  const float Ki = 0.0;
  const float Kd = 0.003;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();
  int headingAlvo = gol;

  unsigned long tempoInicio = millis();

  while ((millis() - tempoInicio) < tempoMovimento) {
    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velocidadeCorrigida = constrain(velocidadeBase - ajuste, 0, 255);

    if (lado == "e") {
      lateralvv("e", velocidadeCorrigida, velocidadeCorrigida);
    } else if (lado == "d") {
      lateralvv("d", (velocidadeCorrigida-20), velocidadeCorrigida);
    }

    delay(30);  // Pequena pausa para estabilidade do loop
  }

  parar();
}

void lateralvv(String lado, int velocidade, int velocidadeB) {
  if (lado == "e") {  // Movimento lateral para ESQUERDA
    // Motores do lado esquerdo para frente e do lado direito para trás (movimento diagonal)
    digitalWrite(IN1_ESQ, HIGH);
    digitalWrite(IN2_ESQ, LOW);
    digitalWrite(IN3_ESQ, HIGH);
    digitalWrite(IN4_ESQ, LOW);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    digitalWrite(IN1_DIR, LOW);
    digitalWrite(IN2_DIR, HIGH);
    digitalWrite(IN3_DIR, LOW);
    digitalWrite(IN4_DIR, HIGH);
    analogWrite(ENA_DIR, velocidade);
    analogWrite(ENB_DIR, velocidade);

  } else if (lado == "d") {  // Movimento lateral para DIREITA
    // Motores do lado esquerdo para frente e do lado direito para trás (movimento diagonal)
    digitalWrite(IN1_ESQ, LOW);
    digitalWrite(IN2_ESQ, HIGH);
    digitalWrite(IN3_ESQ, LOW);
    digitalWrite(IN4_ESQ, HIGH);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    digitalWrite(IN1_DIR, HIGH);
    digitalWrite(IN2_DIR, LOW);
    digitalWrite(IN3_DIR, HIGH);
    digitalWrite(IN4_DIR, LOW);
    analogWrite(ENA_DIR, velocidadeB);
    analogWrite(ENB_DIR, velocidadeB);
  }
}