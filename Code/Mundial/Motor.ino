void frente(int velocidade) {
  // Motores da esquerda para frente
  digitalWrite(IN1_ESQ, LOW);
  digitalWrite(IN2_ESQ, HIGH);
  digitalWrite(IN3_ESQ, HIGH);
  digitalWrite(IN4_ESQ, LOW);
  analogWrite(ENA_ESQ, velocidade);
  analogWrite(ENB_ESQ, velocidade);

  // Motores da direita para frente
  digitalWrite(IN1_DIR, LOW);
  digitalWrite(IN2_DIR, HIGH);
  digitalWrite(IN3_DIR, HIGH);
  digitalWrite(IN4_DIR, LOW);
  analogWrite(ENA_DIR, velocidade);
  analogWrite(ENB_DIR, velocidade);
}

void tras(int velocidade) {
  // Motores da esquerda para frente
  digitalWrite(IN1_ESQ, HIGH);
  digitalWrite(IN2_ESQ, LOW);
  digitalWrite(IN3_ESQ, LOW);
  digitalWrite(IN4_ESQ, HIGH);
  analogWrite(ENA_ESQ, velocidade);
  analogWrite(ENB_ESQ, velocidade);

  // Motores da direita para frente
  digitalWrite(IN1_DIR, HIGH);
  digitalWrite(IN2_DIR, LOW);
  digitalWrite(IN3_DIR, LOW);
  digitalWrite(IN4_DIR, HIGH);
  analogWrite(ENA_DIR, velocidade);
  analogWrite(ENB_DIR, velocidade);
}

void parar() {
  // Motores da esquerda para frente
  digitalWrite(IN1_ESQ, LOW);
  digitalWrite(IN2_ESQ, LOW);
  digitalWrite(IN3_ESQ, LOW);
  digitalWrite(IN4_ESQ, LOW);

  // Motores da direita para frente
  digitalWrite(IN1_DIR, LOW);
  digitalWrite(IN2_DIR, LOW);
  digitalWrite(IN3_DIR, LOW);
  digitalWrite(IN4_DIR, LOW);
}

void rotacionar(String lado, int velocidade) {
  if (lado == "e") {
    // Motores da esquerda para frente
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

  } else if (lado == "d") {
    // Motores da esquerda para frente
    digitalWrite(IN1_ESQ, LOW);
    digitalWrite(IN2_ESQ, HIGH);
    digitalWrite(IN3_ESQ, HIGH);
    digitalWrite(IN4_ESQ, LOW);
    analogWrite(ENA_ESQ, velocidade);
    analogWrite(ENB_ESQ, velocidade);

    // Motores da direita para frente
    digitalWrite(IN1_DIR, HIGH);
    digitalWrite(IN2_DIR, LOW);
    digitalWrite(IN3_DIR, LOW);
    digitalWrite(IN4_DIR, HIGH);
    analogWrite(ENA_DIR, velocidade);
    analogWrite(ENB_DIR, velocidade);
  }
}

void lateral(String lado, int velocidade) {
  if (lado == "e") {
    // Movimento lateral para a ESQUERDA
    // Esquerda frente, Direita trás
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

  } else if (lado == "d") {
    // Movimento lateral para a DIREITA
    // Esquerda frente, Direita trás
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