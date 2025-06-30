void dribler(String std, int velocidade) {
  // Se a string for "On", liga o dribler no sentido normal
  if (std == "On") {
    analogWrite(ENA_DRIBLER, velocidade);
    digitalWrite(IN1_DRIBLER, HIGH);
    digitalWrite(IN2_DRIBLER, LOW);
  }
  // Se a string for "Off", desliga o dribler
  else if (std == "Off") {
    digitalWrite(IN1_DRIBLER, LOW);
    digitalWrite(IN2_DRIBLER, LOW);
  }
  // Se a string for "Reverse", liga o dribler no sentido reverso
  else if (std == "Reverse") {
    analogWrite(ENA_DRIBLER, velocidade);
    digitalWrite(IN1_DRIBLER, HIGH);
    digitalWrite(IN2_DRIBLER, LOW);
  }
}