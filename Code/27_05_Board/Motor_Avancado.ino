// Mover sentido lateral
void lateral(String lado, byte velocidade) {  // Define "lateral" exigindo 'lado' e 'velocidade'...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);  // Define a velocidade do Motor C
  analogWrite(EENB, velocidade);  // Define a velocidade do Motor D
  analogWrite(DENA, velocidade);  // Define a velocidade do Motor A
  analogWrite(DENB, velocidade);  // Define a velocidade do Motor B

  if (lado == "Esq") {  // Se o movimento é para a esquerda...
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, HIGH);  // Motor C gira para frente
    digitalWrite(EIN2, LOW);
    // Traseiro
    digitalWrite(EIN3, HIGH);  // Motor D gira para frente
    digitalWrite(EIN4, LOW);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, HIGH);  // Motor A gira para frente
    digitalWrite(DIN2, LOW);
    // Traseiro
    digitalWrite(DIN3, LOW);   // Motor B gira para trás
    digitalWrite(DIN4, HIGH);
  } else {  // Se o movimento é para a direita...
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, LOW);   // Motor C gira para trás
    digitalWrite(EIN2, HIGH);
    // Traseiro
    digitalWrite(EIN3, LOW);   // Motor D gira para trás
    digitalWrite(EIN4, HIGH);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, LOW);   // Motor A gira para trás
    digitalWrite(DIN2, HIGH);
    // Traseiro
    digitalWrite(DIN3, HIGH);  // Motor B gira para frente
    digitalWrite(DIN4, LOW);
  }
}

void rotacionar(String lado, byte velocidade) {  // Define "rotacionar" exigindo 'lado' e 'velocidade'...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);  // Define a velocidade do Motor C
  analogWrite(EENB, velocidade);  // Define a velocidade do Motor D
  analogWrite(DENA, velocidade);  // Define a velocidade do Motor A
  analogWrite(DENB, velocidade);  // Define a velocidade do Motor B

  if (lado == "Esq") {  // Se a rotação é para a esquerda...
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, HIGH);  // Motor C gira para frente
    digitalWrite(EIN2, LOW);
    // Traseiro
    digitalWrite(EIN3, LOW);   // Motor D gira para trás
    digitalWrite(EIN4, HIGH);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, LOW);   // Motor A gira para trás
    digitalWrite(DIN2, HIGH);
    // Traseiro
    digitalWrite(DIN3, LOW);   // Motor B gira para trás
    digitalWrite(DIN4, HIGH);
  } else {  // Se a rotação é para a direita...
    // Motores Esquerda //
    // Frente
    digitalWrite(EIN1, LOW);   // Motor C gira para trás
    digitalWrite(EIN2, HIGH);
    // Traseiro
    digitalWrite(EIN3, HIGH);  // Motor D gira para frente
    digitalWrite(EIN4, LOW);
    // Motores Direita //
    // Frente
    digitalWrite(DIN1, HIGH);  // Motor A gira para frente
    digitalWrite(DIN2, LOW);
    // Traseiro
    digitalWrite(DIN3, HIGH);  // Motor B gira para frente
    digitalWrite(DIN4, LOW);
  }
}
