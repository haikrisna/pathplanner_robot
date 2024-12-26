void maju() {
  inverseKinematics(0, 255, 0, 120);
  Serial.print(M1, " | ");
  Serial.print(M2, "|  ");
  Serial.println(M3);
}

void mundur() {
  inverseKinematics(0, -255, 0, 120);
  Serial.print(M1, " | ");
  Serial.print(M2, "|  ");
  Serial.println(M3);
}

void kanan() {
  inverseKinematics(255, 0, 0, 120);
  Serial.print(M1, " | ");
  Serial.print(M2, "|  ");
  Serial.println(M3);
}

void kiri() {
  inverseKinematics(-255, 0, 0, 120);
  Serial.print(M1, " | ");
  Serial.print(M2, "|  ");
  Serial.println(M3);
}

void putar(){
  inverseKinematics(0,0,100,130);
}

void henti() {
  inverseKinematics(0, 0, 0, 0);

}

void zeroangle() {
   parseGyro();
   offsetGyro = dataGyro;
}

void gerakan(int a, int b, int c) {
  float Vx = 0;  // kecepatan sumbu x (cm/s)
  float Vy = 0;  // kecepatan sumbu y (cm/s)
  float W = 0;   // kecepatan rotasi (deg/s)
  Vx = a;
  Vy = b;
  W = c;
  // pos1 = d;
  // pos2 = e;
  // pos3 = f;
}
