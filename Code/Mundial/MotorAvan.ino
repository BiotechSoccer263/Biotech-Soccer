void conduzirBola(int velocidadeBase) {
  const float Kp = 7.0;  // Ajuste conforme necessário
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();        // Lê a posição atual antes de começar
  int headingAlvo = Bussola;  // Salva a posição atual como objetivo fixo

  while (UFrt.read() >= PFrente) {  // Loop infinito até ser interrompido externamente
    ReadCompassSensor();            // Atualiza leitura da bússola

    float erro = calcularErroAngular(Bussola, headingAlvo);  // Calcula erro para manter direção inicial
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain(velocidadeBase - ajuste, 0, 255);
    int velDir = constrain(velocidadeBase + ajuste, 0, 255);

    if (UEsq.read() <= 15) {
      lateral("d", 100);
    } else if (UDir.read() <= 15) {
      lateral("e", 100);
    }

    setMotoresFrente(velEsq, velDir);

    delay(30);
  }

  if (UEsq.read() <= PLado && UDir.read() >= PLado) {
    lateralAlinhadaPID("d", 100);
  } else if (UDir.read() <= PLado && UEsq.read() >= PLado) {
    lateralAlinhadaPID("e", 100);
  }

  while (1) {
    if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
      parar();
      delay(250);
      break;
    } else {
      alinhar();
    }
  }

  chutar();

  delay(100000);
}

void lateralAlinhadaPID(String lado, int velocidadeBase) {
  const float Kp = 1.5;
  const float Ki = 0.0;
  const float Kd = 0.003;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();
  int headingAlvo = gol;

  while (true) {
    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain(velocidadeBase - ajuste, 0, 255);
    int velDir = constrain(velocidadeBase + ajuste, 0, 255);

    if (lado == "e") {
      // Move obrigatoriamente para a esquerda enquanto a distância do lado esquerdo for maior que PLado
      if (UDir.read() <= ParedeLados && UEsq.read() >= 100) {
        lateral("e", (velEsq + velDir) / 2);
      } else {
        while (1) {
          if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
            parar();
            delay(250);
            break;
          } else {
            alinhar();
          }
        }
        break;  // Parar quando atingir ou ficar abaixo do limite
      }
    } else if (lado == "d") {
      // Move obrigatoriamente para a direita enquanto a distância do lado direito for maior que PLado
      if (UEsq.read() <= ParedeLados && UDir.read() >= 100) {
        lateral("d", (velEsq + velDir) / 2);
      } else {
        while (1) {
          if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
            parar();
            delay(250);
            break;
          } else {
            alinhar();
          }
        }
        break;  // Parar quando atingir ou ficar abaixo do limite
      }
    }

    delay(30);
  }

  parar();
}

float calcularErroAngular(int atual, int objetivo) {
  int erro = atual - objetivo;
  return erro;
}

void setMotoresFrente(int velEsq, int velDir) {
  // Motores esquerdos
  digitalWrite(IN1_ESQ, LOW);
  digitalWrite(IN2_ESQ, HIGH);
  digitalWrite(IN3_ESQ, HIGH);
  digitalWrite(IN4_ESQ, LOW);
  analogWrite(ENA_ESQ, velEsq);
  analogWrite(ENB_ESQ, velEsq);

  // Motores direitos
  digitalWrite(IN1_DIR, LOW);
  digitalWrite(IN2_DIR, HIGH);
  digitalWrite(IN3_DIR, HIGH);
  digitalWrite(IN4_DIR, LOW);
  analogWrite(ENA_DIR, velDir);
  analogWrite(ENB_DIR, velDir);
}

void lateral(String lado, int velEsq, int velDir) {
  if (lado == "e") {  // Lateral para ESQUERDA
    // Motores esquerdos: para frente
    digitalWrite(IN1_ESQ, LOW);
    digitalWrite(IN2_ESQ, HIGH);
    digitalWrite(IN3_ESQ, LOW);
    digitalWrite(IN4_ESQ, HIGH);
    analogWrite(ENA_ESQ, velEsq);
    analogWrite(ENB_ESQ, velEsq);

    // Motores direitos: para trás
    digitalWrite(IN1_DIR, LOW);
    digitalWrite(IN2_DIR, HIGH);
    digitalWrite(IN3_DIR, LOW);
    digitalWrite(IN4_DIR, HIGH);
    analogWrite(ENA_DIR, velDir);
    analogWrite(ENB_DIR, velDir);

  } else if (lado == "d") {  // Lateral para DIREITA
    // Motores esquerdos: para trás
    digitalWrite(IN1_ESQ, HIGH);
    digitalWrite(IN2_ESQ, LOW);
    digitalWrite(IN3_ESQ, HIGH);
    digitalWrite(IN4_ESQ, LOW);
    analogWrite(ENA_ESQ, velEsq);
    analogWrite(ENB_ESQ, velEsq);

    // Motores direitos: para frente
    digitalWrite(IN1_DIR, HIGH);
    digitalWrite(IN2_DIR, LOW);
    digitalWrite(IN3_DIR, HIGH);
    digitalWrite(IN4_DIR, LOW);
    analogWrite(ENA_DIR, velDir);
    analogWrite(ENB_DIR, velDir);
  }
}