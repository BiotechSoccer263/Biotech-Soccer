// Parar toda movimentação
void parar() { // Define função 'parar'...
  EsqF.run(RELEASE); // Motor Esquerdo Frente soltar
  EsqT.run(RELEASE); // Motor Esquerdo Traseiro soltar
  DirF.run(RELEASE); // Motor Direito Frente soltar
  DirT.run(RELEASE); // Motor Direito Traseiro soltar
}

// Mover a frente
void frente(byte velocidade) { // Define função 'frente' exigindo 'velocidade'...
  // Motores Esquerdos
  EsqF.setSpeed(velocidade); // Define velocidade Motor Esquerdo Frente
  EsqT.setSpeed(velocidade); // Define velocidade Motor Esquerdo Traseiro
  EsqF.run(BACKWARD); // Girar sentido Ant-Horário Motor Esquerdo Frente
  EsqT.run(BACKWARD); // Girar sentido Horário Motor Esquerdo Traseiro
  // Motores Direitos
  DirF.setSpeed(velocidade); // Define velocidade Motor Direita Frente
  DirT.setSpeed(velocidade); // Define velocidade Motor Direito Traseiro
  DirF.run(FORWARD); // Girar sentido Ant-Horário Motor Direita Frente
  DirT.run(FORWARD); // Girar sentido Horário Motor Direito Traseiro
}

// Mover a trás
void tras(byte velocidade) { // Define função 'tras' exigindo 'velocidade'...
  // Motores Esquerdos
  EsqF.setSpeed(velocidade); // Define velocidade Motor Esquerda Frente
  EsqT.setSpeed(velocidade); // Define velocidade Motor Esquerdo Traseiro
  EsqF.run(FORWARD); // Girar sentido Horário Motor Esquerda Frente
  EsqT.run(FORWARD); // Girar sentido Ant-Horário Motor Esquerdo Traseiro
  // Motores Direitos
  DirF.setSpeed(velocidade); // Define velocidade Motor Direita Frente
  DirT.setSpeed(velocidade); // Define velocidade Motor Direito Traseiro
  DirF.run(BACKWARD); // Girar sentido Horário Motor Direita Frente
  DirT.run(BACKWARD); // Girar sentido Ant-Horário Motor Direito Traseiro
}
