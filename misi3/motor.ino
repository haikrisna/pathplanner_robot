void inverseKinematics(int Vx, int Vy, int W,int limit) {
    // Convert rotational speed from degrees to radians
    // W = W * PI / 180.0;

    // *M1 = (1/R) * (Vx - Vy - (L * W));
    // *M2 = (1/R) * (Vx + Vy + (L * W));
    // *M3 = (1/R) * (-Vx + Vy + (L * W));

    M1 = (cos(radians(30 + 90)) * Vx + sin(radians(30 + 90)) * -Vy + W) * 1;
    M2 = (cos(radians(150 + 90)) * Vx + sin(radians(150 + 90)) * -Vy + W) * 1;
    M3 = ((cos(radians(270 + 90)) * Vx + sin(radians(270 + 90)) * -Vy + W) * 1);

    int speed = limit;

    if (M1 > speed) { M1 = speed; }
    if (M1 < -speed) { M1 = -speed; }
    if (M2 > speed) { M2 = speed; }
    if (M2 < -speed) { M2 = -speed; }
    if (M3 > speed) { M3 = speed; }
    if (M3 < -speed) { M3 = -speed; }

    motor(M1, M2, M3);
}

void motor(int M1, int M2, int M3) {

  if (M1 > 0) {
    digitalWrite(IN1A, LOW);
    digitalWrite(IN1B, HIGH);
    analogWrite(PWM1, M1);
  } else if (M1 < 0) {
    digitalWrite(IN1A, HIGH);
    digitalWrite(IN1B, LOW);
    analogWrite(PWM1, -M1);
  } else {
    digitalWrite(IN1A, LOW);
    digitalWrite(IN1B, LOW);
    analogWrite(PWM1, LOW);
  }

  if (M2 > 0) {
    digitalWrite(IN2A, LOW);
    digitalWrite(IN2B, HIGH);
    analogWrite(PWM2, M2);
  } else if (M2 < 0) {
    digitalWrite(IN2A, HIGH);
    analogWrite(IN2B, LOW);
    analogWrite(PWM2, -M2);
  } else {
    digitalWrite(IN2A, LOW);
    digitalWrite(IN2B, LOW);
    analogWrite(PWM2, LOW);
  }

  if (M3 > 0) {
    digitalWrite(IN3A, HIGH);
    digitalWrite(IN3B, LOW);
    analogWrite(PWM3, M3);
  } else if (M3 < 0) {
    digitalWrite(IN3A, LOW);
    digitalWrite(IN3B, HIGH);
    analogWrite(PWM3, -M3);
  } else {
    digitalWrite(IN3A, 0);
    digitalWrite(IN3B, 0);
    analogWrite(PWM3, 0);
  }
}