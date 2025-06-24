// Rotacionar sobre seu eixo
// Mover sentido lateral
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

// Mover ao sentido vertical
void diagonal(String lado, String sentido, byte velocidade) {  // Define "diagonal" exigindo 'lado' e 'sentido' e 'velocidade'...
  EsqF.setSpeed(velocidade);                                   // Define velocida Esquerda Frente
  EsqT.setSpeed(velocidade);                                   // Define velocida Esquerdo Traseiro
  DirF.setSpeed(velocidade);                                   // Define velocida Direita Frente
  DirT.setSpeed(velocidade);                                   // Define velocida Direito Traseiro

  parar();  // Parar qualquer tipo de movimentação

  if (lado == "Esq" && sentido == "frente") EsqT.run(FORWARD);   // Caso 'lado' = [Esquerda] e 'sentido' = [Frente] ele irá movimentar sentido Horário
  if (lado == "Esq" && sentido == "frente") DirF.run(BACKWARD);  // Caso 'lado' = [Esquerda] e 'sentido' = [Frente] ele irá movimentar sentido Ant-Horário
  if (lado == "Esq" && sentido == "tras") EsqF.run(FORWARD);     // Caso 'lado' = [Esquerda] e 'sentido' = [tras] ele irá movimentar sentido Horário
  if (lado == "Esq" && sentido == "tras") DirT.run(BACKWARD);    // Caso 'lado' = [Esquerda] e 'sentido' = [tras] ele irá movimentar sentido Ant-Horário

  if (lado == "Dir" && sentido == "frente") EsqT.run(FORWARD);   // Caso 'lado' = [Direita] e 'sentido' = [Frente] ele irá movimentar sentido Horário
  if (lado == "Dir" && sentido == "frente") DirF.run(BACKWARD);  // Caso 'lado' = [Direita] e 'sentido' = [Frente] ele irá movimentar sentido Ant-Horário
  if (lado == "Dir" && sentido == "tras") EsqF.run(FORWARD);     // Caso 'lado' = [Direita] e 'sentido' = [tras] ele irá movimentar sentido Horário
  if (lado == "Dir" && sentido == "tras") DirT.run(BACKWARD);    // Caso 'lado' = [Direita] e 'sentido' = [tras] ele irá movimentar sentido Ant-Horário
}
