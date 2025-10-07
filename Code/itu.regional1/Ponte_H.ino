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
  falha = false;
int distF = UltraF.read();
int distE = UltraE.read();  
int distD = UltraD.read();
chutou = false;
while (!chutou){
  if(distF < 80 && distD < 50){
    Serial.println("alili") ;
    rotacionar("Esq", 55);
    delay(500);
    parar();
     falha = true;
  }
    if(distF < 80 && distE < 50){
    rotacionar("Dir", 45);
    delay(300);
    parar();
    falha = true;
  }
  if (distF < 70){
    falha = true;
    rotacionar("Esq", 50);
    delay(80);
    parar();
  }

  // esquerda, tudo
  
if (!falha){
  rotacionar("Esq", 50);
  delay(200);
  parar();
}


frente(250);
delay(200);
DriblerAtivar2(255);
delay(500);
tras(200);
delay(800);
parar();
DriblerAtivar(255);
chutou = true;
  
}
}