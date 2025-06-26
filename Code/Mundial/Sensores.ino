void ReadCompassSensor() {
  Wire.begin();

  // Inicializa a bússola
  Wire.beginTransmission(compassAddress);
  Wire.write(0x00);  // Modo de operação
  Wire.endTransmission();

  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);  // Comando para leitura
  Wire.endTransmission();

  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2)
    ;

  byte lowbyte = Wire.read();
  byte highbyte = Wire.read();
  Bussola = word(highbyte, lowbyte);

  if (PrimeiraLeitura == true) {
    gol = Bussola;
    limite = gol > 180 ? gol - 180 : gol + 180;
    quebra = gol > 180 ? 'D' : 'E';
    BMax = gol + 3;
    BMin = gol - 3;
    PrimeiraLeitura = false;
  }
}

void alinhar() {
  ReadCompassSensor();  // Atualiza a leitura da bússola

  if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
    Alinhado = true;
    if (UEsq.read() <= 60 && UDir.read() > 60) {
      delay(50);
      lateral("d", 150);
      delay(600);
      return;
    } else if (UDir.read() <= 60 && UEsq.read() > 60) {
      delay(50);
      lateral("e", 150);
      delay(600);
      return;
    }

    if (UFrt.read() <= 80) {
      chutar();
    } else {
      frente(VeloFrente);
      delay(500);
    }

  } else if (quebra == 'E') {
    if (BMin < Bussola && Bussola < limite) {
      Alinhado = false;
      rotacionar("e", VeloCurva);  // "e" para esquerda
      delay(50);
    } else {
      Alinhado = false;
      rotacionar("d", VeloCurva);  // "d" para direita
      delay(50);
    }
  } else {
    if (BMax > Bussola && Bussola > limite) {
      Alinhado = false;
      rotacionar("d", VeloCurva);  // "d" para direita
      delay(50);
    } else {
      Alinhado = false;
      rotacionar("e", VeloCurva);  // "e" para esquerda
      delay(50);
    }
  }
}