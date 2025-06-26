void dribler(String std, int velocidade) {
  if (std = "On") {
    analogWrite(ENA_DRIBLER, velocidade);
    digitalWrite(IN1_DRIBLER, HIGH);
    digitalWrite(IN2_DRIBLER, LOW);
  } else if (std = "Off") {
    digitalWrite(IN1_DRIBLER, LOW);
    digitalWrite(IN2_DRIBLER, LOW);
  } else if (std = "Reverse") {
    analogWrite(ENA_DRIBLER, velocidade);
    digitalWrite(IN1_DRIBLER, HIGH);
    digitalWrite(IN2_DRIBLER, LOW);
  }
}