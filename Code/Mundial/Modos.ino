void atacante() {
  SeguirBola();  // Função que faz o robô seguir a bola detectada pelo sensor infravermelho

  if (digitalRead(chavecurso) == 1) {  // Se a chave física estiver pressionada
    conduzirBola(140);  // Executa a função de alinhamento com o gol
  }
}

void goleiro() {
  // Leitura do sensor infravermelho para obter direção e intensidade da bola
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;  // Atualiza direção da bola
  ballIntensi = InfraredBall.Strength;   // Atualiza intensidade do sinal

  Serial.println(ballDirecao);  // Exibe a direção da bola no monitor serial

  // Se a chave física estiver pressionada, executa a função de chute
  if (digitalRead(chavecurso) == 1) {
    chutar();
  }

  // Movimentação do robô de acordo com as leituras do sensor ultrassônico traseiro
  if (UTrs.read() >= 55) {  // Se obstáculo distante atrás
    tras(VeloFrente);              // Anda para trás com velocidade 150
    delay(200);             // Aguarda 200 ms
  } else if (UTrs.read() <= 20 && ballDirecao >= 4 && ballDirecao <= 6) {
    // Se obstáculo muito próximo atrás e bola na frente (direção central)
    frente(VeloFrente);  // Anda para frente com velocidade 150
    delay(200);   // Aguarda 200 ms
  }

  // Leitura da bússola para verificar alinhamento
  ReadCompassSensor();

  Alinhado = false;  // Reseta estado de alinhamento (será avaliado novamente)

  // Correção de alinhamento com base na direção de rotação desejada (quebra)
  if (quebra == 'E') {                          // Se precisa corrigir para a esquerda
    if (BMin <= Bussola && Bussola < limite) {  // Se bússola fora do intervalo correto
      Alinhado = false;
      rotacionar("e", VeloCurva);  // Rotaciona para esquerda
      delay(50);                   // Pequeno atraso para ajuste
    } else {
      Alinhado = false;
      rotacionar("d", VeloCurva);  // Rotaciona para direita para correção
      delay(50);
    }
  } else {                                      // Senão, precisa corrigir para a direita
    if (BMax >= Bussola && Bussola > limite) {  // Se bússola fora do intervalo correto
      Alinhado = false;
      rotacionar("d", VeloCurva);  // Rotaciona para direita
      delay(50);
    } else {
      Alinhado = false;
      rotacionar("e", VeloCurva);  // Rotaciona para esquerda para correção
      delay(50);
    }
  }

  // Movimentação lateral para interceptar bola se ela estiver em uma direção lateral
  if (ballDirecao < 5 && UEsq.read() >= 40) {         // Se bola está à esquerda e há espaço lateral
    lateral("e", VeloFrente);                                // Move lateralmente para esquerda
    delay(350);                                       // Aguarda 350 ms
  } else if (ballDirecao > 5 && UDir.read() >= 40) {  // Se bola está à direita e há espaço lateral
    lateral("d", VeloFrente);                                // Move lateralmente para direita
    delay(350);
  } else {
    parar();  // Se não precisa ajustar, para os motores
  }
}