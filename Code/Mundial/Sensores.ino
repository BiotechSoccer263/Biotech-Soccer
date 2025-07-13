void ReadCompassSensor() {
  Wire.begin();  // Initialize I2C communication

  // Initialize the compass by setting the operation mode
  Wire.beginTransmission(compassAddress);
  Wire.write(0x00);  // Register to configure the mode
  Wire.endTransmission();

  // Command to request compass reading
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);  // Read command
  Wire.endTransmission();

  // Request 2 bytes of data (high byte and low byte)
  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2)
    ;  // Wait for data to be available

  byte lowbyte = Wire.read();         // Read first byte (LSB)
  byte highbyte = Wire.read();        // Read second byte (MSB)
  Bussola = word(highbyte, lowbyte);  // Combine two bytes into a 16-bit value

  // Initial settings on the first reading
  if (PrimeiraLeitura == true) {
    gol = Bussola;                               // Set the goal (initial robot position)
    limite = gol > 180 ? gol - 180 : gol + 180;  // Set the opposite limit (inverted 180°)
    quebra = gol > 180 ? 'D' : 'E';              // Define which half of the circle the orientation is in
    BMax = gol + 3;                              // Maximum alignment tolerance (3 degrees above)
    BMin = gol - 3;                              // Minimum alignment tolerance (3 degrees below)
    PrimeiraLeitura = false;                     // Mark that initial reading was done
  }
}

void alinhar() {
  ReadCompassSensor();  // Update current compass reading

  // Check if already aligned with the goal (within BMin-BMax margin or equal to gol)
  if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
    parar();
    return;
  } else if (quebra == 'E') {  // For goals on the east side of the circle
    if (BMin < Bussola && Bussola < limite) {
      Alinhado = false;
      rotacionar("e", VeloCurvaD);  // Rotate left to align
    } else {
      Alinhado = false;
      rotacionar("d", VeloCurvaD);  // Rotate right to align
    }
  } else {  // For goals on the west side of the circle
    if (BMax > Bussola && Bussola > limite) {
      Alinhado = false;
      rotacionar("d", VeloCurvaD);  // Rotate right to align
    } else {
      Alinhado = false;
      rotacionar("e", VeloCurvaD);  // Rotate left to align
    }
  }
}