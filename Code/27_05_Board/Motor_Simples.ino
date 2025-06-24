// Parar toda movimentação
void parar() {  // Define função 'parar' para interromper todos os motores...
  digitalWrite(EIN1, HIGH);  // Para motor C frente
  digitalWrite(EIN2, HIGH);  // Para motor C traseiro
  digitalWrite(EIN3, HIGH);  // Para motor D frente
  digitalWrite(EIN4, HIGH);  // Para motor D traseiro
  digitalWrite(DIN1, HIGH);  // Para motor A frente
  digitalWrite(DIN2, HIGH);  // Para motor A traseiro
  digitalWrite(DIN3, HIGH);  // Para motor B frente
  digitalWrite(DIN4, HIGH);  // Para motor B traseiro
}

// Mover à frente
void frente(int velocidade) {  // Define função 'frente' com velocidade ajustável...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);  // Ajusta a velocidade do motor C
  analogWrite(EENB, velocidade);  // Ajusta a velocidade do motor D
  analogWrite(DENA, velocidade);  // Ajusta a velocidade do motor A
  analogWrite(DENB, velocidade);  // Ajusta a velocidade do motor B
  
  // Motores Esquerda //
  // Frente
  digitalWrite(EIN1, LOW);   // Motor C gira para frente
  digitalWrite(EIN2, HIGH);
  // Traseiro
  digitalWrite(EIN3, HIGH);  // Motor D gira para frente
  digitalWrite(EIN4, LOW);
  
  // Motores Direita //
  // Frente
  digitalWrite(DIN1, LOW);   // Motor A gira para frente
  digitalWrite(DIN2, HIGH);
  // Traseiro
  digitalWrite(DIN3, LOW);   // Motor B gira para frente
  digitalWrite(DIN4, HIGH);
}

// Mover para trás
void tras(int velocidade) {  // Define função 'tras' com velocidade ajustável...
  // Definir Velocidade //
  analogWrite(EENA, velocidade);  // Ajusta a velocidade do motor C
  analogWrite(EENB, velocidade);  // Ajusta a velocidade do motor D
  analogWrite(DENA, velocidade);  // Ajusta a velocidade do motor A
  analogWrite(DENB, velocidade);  // Ajusta a velocidade do motor B
  
  // Motores Esquerda //
  // Frente
  digitalWrite(EIN1, HIGH);  // Motor C gira para trás
  digitalWrite(EIN2, LOW);
  // Traseiro
  digitalWrite(EIN3, LOW);   // Motor D gira para trás
  digitalWrite(EIN4, HIGH);
  
  // Motores Direita //
  // Frente
  digitalWrite(DIN1, HIGH);  // Motor A gira para trás
  digitalWrite(DIN2, LOW);
  // Traseiro
  digitalWrite(DIN3, HIGH);  // Motor B gira para trás
  digitalWrite(DIN4, LOW);
}
