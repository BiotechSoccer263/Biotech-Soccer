// Rotacionar sobre seu eixo
void rotacionar(String lado, byte velocidade) { // Define "rotacionar" exigindo 'lado' e 'velocidade'...
  EsqF.setSpeed(velocidade); // Define velocidade Motor Esquerda Frente
  EsqT.setSpeed(velocidade); // Define velocidade Motor Esquerdo Traseiro
  DirF.setSpeed(velocidade); // Define velocidade Motor Direita Frente
  DirT.setSpeed(velocidade); // Define velocidade Motor Direito Traseiro

  // Motores Esquerdos
  EsqF.run((lado == "Esq") ? FORWARD : BACKWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Horário, se não, Ant-Horário
  EsqT.run((lado == "Esq") ? FORWARD : BACKWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Ant-Horário, se não, Horário
  // Motores Direitos
  DirF.run((lado == "Esq") ? FORWARD : BACKWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Ant-Horário, se não, Horário
  DirT.run((lado == "Esq") ? FORWARD : BACKWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Horário, se não, Ant-Horário
}

// Mover sentido lateral
void lateral(String lado, byte velocidade) { // Define "lateral" exigindo 'lado' e 'velocidade'...
  EsqF.setSpeed(velocidade); // Define velocida Esquerda Frente 
  EsqT.setSpeed(velocidade); // Define velocida Esquerdo Traseiro
  DirF.setSpeed(velocidade); // Define velocida Direita Frente 
  DirT.setSpeed(velocidade); // Define velocida Direito Traseiro

  // Motores Esquerdos
  EsqF.run((lado == "Esq") ? FORWARD : BACKWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Horário, se não, Ant-Horário
  EsqT.run((lado == "Esq") ? BACKWARD : FORWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Horário, se não, Ant-Horário
  // Motores Direitos
  DirF.run((lado == "Esq") ? FORWARD : BACKWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Ant-Horário, se não, Horário
  DirT.run((lado == "Esq") ? BACKWARD : FORWARD); // Caso 'lado' = [Esquerda] ele irá virar sentido Ant-Horário, se não, Horário
}

// Mover ao sentido vertical
void diagonal(String lado, String sentido, byte velocidade) { // Define "diagonal" exigindo 'lado' e 'sentido' e 'velocidade'...
  EsqF.setSpeed(velocidade); // Define velocida Esquerda Frente
  EsqT.setSpeed(velocidade); // Define velocida Esquerdo Traseiro
  DirF.setSpeed(velocidade); // Define velocida Direita Frente
  DirT.setSpeed(velocidade); // Define velocida Direito Traseiro

  parar(); // Parar qualquer tipo de movimentação

  if (lado == "Esq" && sentido == "frente") EsqT.run(FORWARD); // Caso 'lado' = [Esquerda] e 'sentido' = [Frente] ele irá movimentar sentido Horário
  if (lado == "Esq" && sentido == "frente") DirF.run(BACKWARD); // Caso 'lado' = [Esquerda] e 'sentido' = [Frente] ele irá movimentar sentido Ant-Horário
  if (lado == "Esq" && sentido == "tras") EsqF.run(FORWARD); // Caso 'lado' = [Esquerda] e 'sentido' = [tras] ele irá movimentar sentido Horário
  if (lado == "Esq" && sentido == "tras") DirT.run(BACKWARD); // Caso 'lado' = [Esquerda] e 'sentido' = [tras] ele irá movimentar sentido Ant-Horário

  if (lado == "Dir" && sentido == "frente") EsqT.run(FORWARD); // Caso 'lado' = [Direita] e 'sentido' = [Frente] ele irá movimentar sentido Horário
  if (lado == "Dir" && sentido == "frente") DirF.run(BACKWARD); // Caso 'lado' = [Direita] e 'sentido' = [Frente] ele irá movimentar sentido Ant-Horário
  if (lado == "Dir" && sentido == "tras") EsqF.run(FORWARD); // Caso 'lado' = [Direita] e 'sentido' = [tras] ele irá movimentar sentido Horário 
  if (lado == "Dir" && sentido == "tras") DirT.run(BACKWARD); // Caso 'lado' = [Direita] e 'sentido' = [tras] ele irá movimentar sentido Ant-Horário
}
