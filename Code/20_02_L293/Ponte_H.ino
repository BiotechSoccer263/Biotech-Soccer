void DriblerAtivar(int velocidade) {
  digitalWrite(DRIN1, HIGH);
  digitalWrite(DRIN2, LOW);
  analogWrite(DRENB, velocidade);
}

void DriblerAtivar2(int velocidade) {
  digitalWrite(DRIN1, LOW);
  digitalWrite(DRIN2, HIGH);
  analogWrite(DRENB, velocidade);
}

void chutar() {
  int tempo = 0;
  while (tempo < 350) {
    refletancia = analogRead(RefleEsq);
    if (refletancia > BrancoMin && refletancia < BrancoMax) {
      tempo = 400;
      tras(200);
      delay(450);
      break;
    }else {
      frente(250);
      tempo += 100;
      delay(100);
    }
  }

  parar();
  DriblerAtivar2(255);
  delay(150);
  DriblerAtivar(255);
  tras(200);
  delay(250);
}