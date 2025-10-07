// Parar toda movimentação
void parar() {  // Define função 'parar'...
  digitalWrite(EIN1, HIGH);
  digitalWrite(EIN2, HIGH);
  digitalWrite(EIN3, HIGH);
  digitalWrite(EIN4, HIGH);
  digitalWrite(DIN1, HIGH);
  digitalWrite(DIN2, HIGH);
  digitalWrite(DIN3, HIGH);
  digitalWrite(DIN4, HIGH);
}

// Mover a frente
void frente(int velocidade) {
  // Definir Velocidade //
  analogWrite(EENA, velocidade);
  analogWrite(EENB, velocidade);
  analogWrite(DENA, velocidade);
  analogWrite(DENB, velocidade);
  // Motores Esquerda //
  // Frente
  digitalWrite(EIN1, LOW);
  digitalWrite(EIN2, HIGH);
  // Traseiro
  digitalWrite(EIN3, HIGH);
  digitalWrite(EIN4, LOW);
  // Motores Direita //
  // Frente
  digitalWrite(DIN1, LOW);
  digitalWrite(DIN2, HIGH);
  // Traseiro
  digitalWrite(DIN3, LOW);
  digitalWrite(DIN4, HIGH);
}

void tras(int velocidade) {
  // Definir Velocidade //
  analogWrite(EENA, velocidade);
  analogWrite(EENB, velocidade);
  analogWrite(DENA, velocidade);
  analogWrite(DENB, velocidade);
  // Motores Esquerda //
  // Frente
  digitalWrite(EIN1, HIGH);
  digitalWrite(EIN2, LOW);
  // Traseiro
  digitalWrite(EIN3, LOW);
  digitalWrite(EIN4, HIGH);
  // Motores Direita //
  // Frente
  digitalWrite(DIN1, HIGH);
  digitalWrite(DIN2, LOW);
  // Traseiro
  digitalWrite(DIN3, HIGH);
  digitalWrite(DIN4, LOW);
}