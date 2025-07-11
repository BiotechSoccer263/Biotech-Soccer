void conduzirBola(int velocidadeBase) {
  const float Kp = 2.0;  // Ajuste conforme necessário
  const float Ki = 0.05;
  const float Kd = 8.0;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();    // Lê a posição atual antes de começar
  int headingAlvo = gol;  // Salva a posição atual como objetivo fixo

  while (1) {
    if (Bussola == gol || (Bussola >= BMin && Bussola <= BMax)) {
      parar();
      delay(250);
      break;
    } else {
      alinhar();
    }
  }

  Serial.println("Andar");

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

    int refletanciaEsq = analogRead(EsqR);
    int refletanciaDir = analogRead(DirR);

    bool linhaDetectadaEsq = (refletanciaEsq >= BrancoMin && refletanciaEsq <= BrancoMax);
    bool linhaDetectadaDir = (refletanciaDir >= BrancoMin && refletanciaDir <= BrancoMax);

    if (linhaDetectadaEsq && !linhaDetectadaDir) {
      lateral("d", 110);
    } else if (linhaDetectadaDir && !linhaDetectadaEsq) {
      lateral("e", 110);
    }

    setMotoresFrente(velEsq, velDir);

    delay(30);
  }

  if (digitalRead(chavecurso) == 0) { return; }

  int LFrt = UFrt.read();

  Serial.println("Alinhar");

  for (int i = 0; i < 3; i++) {
    int LEsq = UEsq.read();
    int LDrt = UDir.read();
    if (LDrt > 255) {
      LDrt = UDir.read();
    }

    if (LDrt <= PLado && LEsq >= PLado) {
      lateralAlinhadaPID("e", 110);
    }
    if (LEsq <= PLado && LDrt >= PLado) {
      lateralAlinhadaPID("d", 110);
    }
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

  Serial.println("Chutar");

  if (digitalRead(chavecurso) == 0) {
    return;
  } else {
    chutar();
  }
}

void lateralAlinhadaPID(String lado, int velocidadeBase) {
  const float Kp = 1.5;
  const float Ki = 0.0;
  const float Kd = 0.003;
  float erroAnterior = 0.0;
  float somaErro = 0.0;

  ReadCompassSensor();
  int headingAlvo = gol;

  while (true && (digitalRead(chavecurso) == 1)) {
    ReadCompassSensor();

    float erro = calcularErroAngular(Bussola, headingAlvo);
    somaErro += erro;
    float derivada = erro - erroAnterior;
    erroAnterior = erro;

    float ajuste = Kp * erro + Ki * somaErro + Kd * derivada;
    ajuste = constrain(ajuste, -100, 100);

    int velEsq = constrain(velocidadeBase - ajuste, 0, 255);
    int velDir = constrain(velocidadeBase + ajuste, 0, 255);

    alinhar();

    if (lado == "e") {
      // Move obrigatoriamente para a esquerda enquanto a distância do lado esquerdo for maior que PLado
      if (UDir.read() <= (ParedeLados + 10)) {
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
      if (UEsq.read() <= ParedeLados) {
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

float calcularErroAngular(int atual, int alvo) {
  int erro = atual - alvo;

  // Garante que erro fique em [-180, +180]
  erro = (erro + 540) % 360 - 180;
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

void setMotoresTras(int velEsq, int velDir) {
  // Motores esquerdos
  digitalWrite(IN1_ESQ, HIGH);
  digitalWrite(IN2_ESQ, LOW);
  digitalWrite(IN3_ESQ, LOW);
  digitalWrite(IN4_ESQ, HIGH);
  analogWrite(ENA_ESQ, velEsq);
  analogWrite(ENB_ESQ, velEsq);

  // Motores direitos
  digitalWrite(IN1_DIR, HIGH);
  digitalWrite(IN2_DIR, LOW);
  digitalWrite(IN3_DIR, LOW);
  digitalWrite(IN4_DIR, HIGH);
  analogWrite(ENA_DIR, velDir);
  analogWrite(ENB_DIR, velDir);
}