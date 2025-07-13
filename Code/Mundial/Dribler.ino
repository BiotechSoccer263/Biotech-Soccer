void dribler(String std, int velocidade) {
  // If the string is "On", turns on the dribbler in the normal direction
  if (std == "On") {
    analogWrite(ENA_DRIBLER, velocidade);
    digitalWrite(IN1_DRIBLER, HIGH);
    digitalWrite(IN2_DRIBLER, LOW);
  }
  // If the string is "Off", turns off the dribbler
  else if (std == "Off") {
    digitalWrite(IN1_DRIBLER, LOW);
    digitalWrite(IN2_DRIBLER, LOW);
  }
  // If the string is "Reverse", turns on the dribbler in reverse direction
  else if (std == "Reverse") {
    analogWrite(ENA_DRIBLER, velocidade);
    digitalWrite(IN1_DRIBLER, HIGH);
    digitalWrite(IN2_DRIBLER, LOW);
  }
}