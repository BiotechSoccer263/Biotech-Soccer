void DriblerAtivar(int velocidade) {  // Função para ativar o dribler no sentido padrão...
  digitalWrite(DRIN1, HIGH);  // Define direção do dribler para frente
  digitalWrite(DRIN2, LOW);
  analogWrite(DRENB, velocidade);  // Define a velocidade do dribler
}

void DriblerAtivar2(int velocidade) {  // Função para ativar o dribler no sentido reverso...
  digitalWrite(DRIN1, LOW);   // Define direção do dribler para trás
  digitalWrite(DRIN2, HIGH);
  analogWrite(DRENB, velocidade);  // Define a velocidade do dribler
}

void chutar() {  // Função para realizar o chute com o robô...
  int tempo = 0;  // Variável de controle de tempo para o chute
  while (tempo < 350) {  // Enquanto o tempo for menor que 350ms...
    refletancia = analogRead(RefleEsq);  // Leitura do sensor de refletância à esquerda
    if (refletancia > BrancoMin && refletancia < BrancoMax) {  // Verifica se há linha branca detectada
      tempo = 400;  // Ajusta o tempo para sair do loop
      tras(200);    // Move o robô para trás rapidamente
      delay(450);
      break;  // Sai do loop
    } else {
      frente(250);  // Caso contrário, move para frente em alta velocidade
      tempo += 100; // Incrementa o tempo
      delay(100);
    }
  }

  parar();                 // Para o movimento do robô
  DriblerAtivar2(255);     // Ativa o dribler para trás na força máxima
  delay(150);
  DriblerAtivar(255);      // Ativa o dribler para frente na força máxima
  tras(200);               // Move o robô para trás para finalizar o chute
  delay(250);
}
