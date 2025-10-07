// ===============================
// --- Função: goleiro_infra ---
// ===============================
void goleiro_infra() {
  // --- Leitura do Infravermelho (bola) ---
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
  ballDirecao = InfraredBall.Direction;   // Direção da bola
  ballIntensi = InfraredBall.Strength;    // Intensidade da bola

  // --- Leitura dos Ultrassônicos ---
  int Ultrae = UltraE.read();   // Sensor da esquerda
  int Ultrad = UltraD.read();   // Sensor da direita
  int Ultrat = UltraT.read();   // Sensor traseiro

  // --- Linha do goleiro ---
  linhagoleiro();

  // --- Leitura da Bússola ---
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);
  Wire.endTransmission();

  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2);

  byte lowbyte  = Wire.read();
  byte highbyte = Wire.read();
  Bussola = word(highbyte, lowbyte);

  // --- Parada inicial ---
  parar();

  // --- Controle de afastamento lateral com ultrassônicos ---
  if (Ultrad < 80) {
    lateralg("Esq", 150);
  }
  if (Ultrae < 80) {
    lateralg("Dir", 150);
  }

  // --- Verificação da Bússola ---
  if (Bussola <= BMax && Bussola >= BMin) {
    Alinhado = true;
  } else {
    Alinhado = false;
  }

  // --- Ajuste de alinhamento usando rotação ---
  if (Alinhado) {
    parar();
  } else if (quebra == 'E') {
    if (BMin < Bussola && Bussola < limite) {
      rotacionar("Esq", 65);
      delay(50);
      return;
    } else {
      rotacionar("Dir", 65);
      delay(20);
      return;
    }
  } else {
    if (BMax > Bussola && Bussola > limite) {
      rotacionar("Dir", 65);
      delay(20);
    } else {
      rotacionar("Esq", 65);
      delay(20);
    }
  }

  if (!Alinhado) return;

  // --- Controle frontal com ultrassônico traseiro ---
  if (Ultrat < ParedeT) {
    frente(100);
    delay(50);
  } else if (Ultrat >= 60 || Ultrat > 35) {
    tras(100);
    delay(50);
  }

  // --- Controle lateral baseado na bola + ultrassônicos ---
  if (ballDirecao > 6) {  
    // bola está para a direita
    if (Ultrad > 50) {
      lateralg("Drt", 220);
      delay(50);
    } else {
      parar();  // muito perto da parede direita
    }
    return;
  } 
  else if (ballDirecao < 4) {  
    // bola está para a esquerda
    if (Ultrae > 50) {
      lateralg("Esq", 220);
      delay(50);
    } else {
      parar();  // muito perto da parede esquerda
    }
    return;
  } 
  else {
    parar();  // bola centralizada
  }
}
