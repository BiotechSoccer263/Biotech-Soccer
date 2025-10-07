// Variável global auxiliar para alternar o giro rápido
unsigned long ultimoTroca = 0;
bool giraEsq = true;

void goleiro_infra() {                                     
  // --- Leitura do Infravermelho ---
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;
  ballIntensi = InfraredBall.Strength;

  linhagoleiro();

  BMax = gol + 10;
  BMin = gol - 10;

  // --- Ultrassônicos ---
  int distE = UltraE.read();  
  int distD = UltraD.read();  
  int distT = UltraT.read();  
  int distF = UltraF.read();  

  // --- Bússola ---
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);
  Wire.endTransmission();
  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2);
  byte lowbyte = Wire.read();
  byte highbyte = Wire.read();
  Bussola = word(highbyte, lowbyte);

  parar();

  // --- Alinhamento ---
  if (Bussola <= BMax && Bussola >= BMin) Alinhado = true;
  else Alinhado = false;

  if (!Alinhado) {
    int velRot = 60;
    if (quebra == 'E') {
      if (BMin < Bussola && Bussola < limite) rotacionar("Esq", velRot);
      else rotacionar("Dir", velRot);
    } else {
      if (BMax > Bussola && Bussola > limite) rotacionar("Dir", velRot);
      else rotacionar("Esq", velRot);
    }
    return;
  }

  // --- Defesa contra robô frontal ---
    if (distF < 35 ) {
    frente(250);       
    delay(300);        
    tras(200);         
    delay(250);
    parar();
    return;
  }

  // --- Posição base próxima ao gol ---
  if (distT > 45) {     
    tras(160);
    return;
  }
  if (distT < 20) {     
    frente(120);
    delay(200);
    return;
  }

  // --- Limite lateral ---
  if (distD < 20) {      
    lateralg("Esq", 250);
    return;
  }
  if (distE < 20) {      
    lateralg("Dir", 250);
    return;
  }

  // --- Movimento lateral baseado na bola ---
  int velBase = map(ballIntensi, 255, 255, 255, 255);
  velBase = constrain(velBase, 150, 255);

  if (ballDirecao > 6) {       
    if (distD > 35) lateralg("Dir", velBase);
  } 
  else if (ballDirecao < 4) {  
    if (distE > 35) lateralg("Esq", velBase);
  } 
  else {   
    // --- NOVO: caso esteja "parado" (bola central) -> gira rápido esq/dir ---
    unsigned long agora = millis();
    if (agora - ultimoTroca > 70) { // troca a cada 200ms (rápido)
      giraEsq = !giraEsq;
      ultimoTroca = agora;
    }

    if (giraEsq) rotacionar("Esq", 250);
    else         rotacionar("Dir", 250);
  }
}
