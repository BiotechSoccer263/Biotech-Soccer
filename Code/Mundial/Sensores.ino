void ReadCompassSensor() {
  Wire.begin();  // Inicializa a comunicação I2C

  // Inicializa a bússola, configurando o modo de operação
  Wire.beginTransmission(compassAddress);
  Wire.write(0x00);  // Registro para configurar o modo
  Wire.endTransmission();

  // Comando para solicitar leitura da bússola
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);  // Comando de leitura
  Wire.endTransmission();

  // Solicita 2 bytes de dados (high byte e low byte)
  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2)
    ;  // Espera os dados estarem disponíveis

  byte lowbyte = Wire.read();         // Lê o primeiro byte (LSB)
  byte highbyte = Wire.read();        // Lê o segundo byte (MSB)
  Bussola = word(highbyte, lowbyte);  // Concatena os dois bytes em um valor de 16 bits

  // Configurações iniciais na primeira leitura
  if (PrimeiraLeitura == true) {
    gol = Bussola;                               // Define o objetivo (posição inicial do robô)
    limite = gol > 180 ? gol - 180 : gol + 180;  // Define o limite oposto (180° invertido)
    quebra = gol > 180 ? 'D' : 'E';              // Define em qual metade do círculo a orientação está
    BMax = gol + 3;                              // Tolerância máxima de alinhamento (3 graus acima)
    BMin = gol - 3;                              // Tolerância mínima de alinhamento (3 graus abaixo)
    PrimeiraLeitura = false;                     // Marca que já realizou a leitura inicial
  }
}

void alinhar() {
  ReadCompassSensor();  // Atualiza a leitura atual da bússola

  // Verifica se já está alinhado com o objetivo (dentro da margem BMin-BMax ou igual a gol)
  if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
    parar();
    return;
  } else if (quebra == 'E') {  // Para objetivos no lado leste do círculo
    if (BMin < Bussola && Bussola < limite) {
      Alinhado = false;
      rotacionar("e", VeloCurvaD);  // Rotaciona à esquerda para alinhar
    } else {
      Alinhado = false;
      rotacionar("d", VeloCurvaD);  // Rotaciona à direita para alinhar
    }
  } else {  // Para objetivos no lado oeste do círculo
    if (BMax > Bussola && Bussola > limite) {
      Alinhado = false;
      rotacionar("d", VeloCurvaD);  // Rotaciona à direita para alinhar
    } else {
      Alinhado = false;
      rotacionar("e", VeloCurvaD);  // Rotaciona à esquerda para alinhar
    }
  }
}