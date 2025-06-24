void DriblerAtivar(byte velocidade) {  // Define 'DriblerAtivar' com valor requirido 'velocidade'...
  // Definir velocidade
  analogWrite(INN, velocidade);  // Escreve Analogicamente porta 'INN' para [velocidade]
  analogWrite(INP, velocidade);  // Escreve Analogicamente porta 'INP' para [velocidade]
  // Ativar Motores
  digitalWrite(IN3, LOW);  // Escrever porta Digital 'IN1' para [Energizado]
  digitalWrite(IN4, HIGH);   // Escrever porta Digital 'IN2' para [Desenergizado]
}

void DriblerAtivar2(byte velocidade) {  // Define 'DriblerAtivar' com valor requirido 'velocidade'...
  // Definir velocidade
  analogWrite(INN, velocidade);  // Escreve Analogicamente porta 'INN' para [velocidade]
  analogWrite(INP, velocidade);  // Escreve Analogicamente porta 'INP' para [velocidade]
  // Ativar Motores
  digitalWrite(IN3, HIGH);   // Escrever porta Digital 'IN1' para [Energizado]
  digitalWrite(IN4, LOW);  // Escrever porta Digital 'IN2' para [Desenergizado]
}

void DriblerDesligar() {   // Define 'DriblerDesliga' para...
  digitalWrite(IN3, LOW);  // Escrever porta Digital 'IN1' para [Desenergizado]
  digitalWrite(IN4, LOW);  // Escrever porta Digital 'IN2' para [Desenergizado]
}

void chutar() {         // Define 'chutar' para...
  frente(130);          // Movimentar a frente na velocidade [255]
  delay(300);
  DriblerAtivar2(255);  // Virar sentido do dribler
  delay(200);           // Esperar
  parar();              // Parar qualquer movimentação
  delay(600);           // Esperar
  DriblerAtivar(255);   // Voltar movimento de puxar bola no dribler
  tras(120);            // Movimentar para trás na velocidade [120]
  delay(150);           // Esperar
}