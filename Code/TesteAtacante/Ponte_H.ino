void DriblerAtivar(int velocidade) {
  digitalWrite(DRIN3, HIGH);
  digitalWrite(DRIN4, LOW);
  analogWrite(DRENB, velocidade);
}

void DriblerAtivar2(int velocidade) {
  digitalWrite(DRIN3, LOW);
  digitalWrite(DRIN4, HIGH);
  analogWrite(DRENB, velocidade);
}

void chutar() {
frente(250);
delay(200);
DriblerAtivar2(255);
delay(500);
tras(200);
delay(800);
parar();
}