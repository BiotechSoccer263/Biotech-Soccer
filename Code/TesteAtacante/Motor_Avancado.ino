// Rotacionar sobre seu eixo
// Mover sentido lateral
void lateralg(String lado, byte velocidade) {  // Define "lateral" exigindo 'lado' e 'velocidade'...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);
  analogWrite(EENB, velocidade);
  analogWrite(DENA, velocidade);
  analogWrite(DENB, velocidade);

  if (lado == "Esq") {
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, HIGH);
    digitalWrite(EIN2, LOW);
    // Traseiro
    digitalWrite(EIN3, HIGH);
    digitalWrite(EIN4, LOW);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, HIGH);
    digitalWrite(DIN2, LOW);
    // Traseiro
    digitalWrite(DIN3, LOW);
    digitalWrite(DIN4, HIGH);
  } else {
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, LOW);
    digitalWrite(EIN2, HIGH);
    // Traseiro
    digitalWrite(EIN3, LOW);
    digitalWrite(EIN4, HIGH);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, LOW);
    digitalWrite(DIN2, HIGH);
    // Traseiro
    digitalWrite(DIN3, HIGH);
    digitalWrite(DIN4, LOW);
  }
}

void lateral(String lado, byte velocidade) {  // Define "lateral" exigindo 'lado' e 'velocidade'...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);
  analogWrite(EENB, velocidade);
  analogWrite(DENA, velocidade);
  analogWrite(DENB, velocidade);

  if (lado == "Esq") {
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, HIGH);
    digitalWrite(EIN2, LOW);
    // Traseiro
    digitalWrite(EIN3, HIGH);
    digitalWrite(EIN4, LOW);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, LOW);
    digitalWrite(DIN2, HIGH);
    // Traseiro
    digitalWrite(DIN3, HIGH);
    digitalWrite(DIN4, LOW);
  } else {
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, LOW);
    digitalWrite(EIN2, HIGH);
    // Traseiro
    digitalWrite(EIN3, LOW);
    digitalWrite(EIN4, HIGH);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, HIGH);
    digitalWrite(DIN2, LOW);
    // Traseiro
    digitalWrite(DIN3, LOW);
    digitalWrite(DIN4, HIGH);
  }
}

void rotacionar(String lado, byte velocidade) {  // Define "rotacionar" exigindo 'lado' e 'velocidade'...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);
  analogWrite(EENB, velocidade);
  analogWrite(DENA, velocidade);
  analogWrite(DENB, velocidade);

  if (lado == "Esq") {
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, HIGH);
    digitalWrite(EIN2, LOW);
    // Traseiro
    digitalWrite(EIN3, LOW);
    digitalWrite(EIN4, HIGH);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, LOW);
    digitalWrite(DIN2, HIGH);
    // Traseiro
    digitalWrite(DIN3, LOW);
    digitalWrite(DIN4, HIGH);
  } else {
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, LOW);
    digitalWrite(EIN2, HIGH);
    // Traseiro
    digitalWrite(EIN3, HIGH);
    digitalWrite(EIN4, LOW);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, HIGH);
    digitalWrite(DIN2, LOW);
    // Traseiro
    digitalWrite(DIN3, HIGH);
    digitalWrite(DIN4, LOW);
  }
}