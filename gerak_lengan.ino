void moveServos(int posisiawal, int dynamixelPos, int servo2Pos, int servo3Pos, int delayTime) {
  if (posisiawal >= 512 && dynamixelPos >= posisiawal){
    Dynamixel.moveSpeed(1, dynamixelPos, 110);
    Dynamixel.moveSpeed(16, dynamixelPos, 110);
    delay(500);
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(delayTime);
  }else if (posisiawal > 512 && dynamixelPos <= posisiawal){
    Dynamixel.moveSpeed(1, dynamixelPos, 110);
    Dynamixel.moveSpeed(16, dynamixelPos, 110);
    delay(500);
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(delayTime);
  }
  else if (posisiawal <= 512 && dynamixelPos <= posisiawal){
    Dynamixel.moveSpeed(1, dynamixelPos, 110);
    Dynamixel.moveSpeed(16, dynamixelPos, 110);
    delay(500);
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(delayTime);
  }else if (posisiawal < 512 && dynamixelPos >= posisiawal){
    Dynamixel.moveSpeed(1, dynamixelPos, 150);
    Dynamixel.moveSpeed(16, dynamixelPos, 150);
    delay(500);
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(delayTime);
  }
  else {

  }
 
}

void moveServosfirst(int posisiawal, int dynamixelPos, int servo2Pos, int servo3Pos, int delayTime) {
  if (posisiawal >= 512 && dynamixelPos >= posisiawal){
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(500);
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    Dynamixel.moveSpeed(1, dynamixelPos, 100);
    Dynamixel.moveSpeed(16, dynamixelPos, 100);
    delay(delayTime);
  }else if (posisiawal > 512 && dynamixelPos <= posisiawal){
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(500);
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    Dynamixel.moveSpeed(1, dynamixelPos, 150);
    Dynamixel.moveSpeed(16, dynamixelPos, 150);
    delay(delayTime);
  }
  else if (posisiawal <= 512 && dynamixelPos <= posisiawal){
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(500);
    Dynamixel.moveSpeed(1, dynamixelPos, 100);
    Dynamixel.moveSpeed(16, dynamixelPos, 100);
    delay(delayTime);
  }else if (posisiawal < 512 && dynamixelPos >= posisiawal){
    moveServoSmooth(servo2, servo2Pos, 3);
    delay(500);
    moveServoSmooth(servo3, servo3Pos, 3);
    delay(500);
    Dynamixel.moveSpeed(1, dynamixelPos, 150);
    Dynamixel.moveSpeed(16, dynamixelPos, 150);
    delay(delayTime);
  }
  else {

  }
 
}

void moveServoSmooth(Servo &servo, int targetPos, int speed) {
  int currentPos = servo.read();
  if (currentPos < targetPos) {
    for (int pos = currentPos; pos <= targetPos; pos++) {
      servo.write(pos);
      delay(50/speed);
    }
  } else {
    for (int pos = currentPos; pos >= targetPos; pos--) {
      servo.write(pos);
      delay(50/speed);
    }
  }
}

void hisap() {
  Serial.println("Hisap aktif");
  digitalWrite(vakum, HIGH); // Aktifkan vakum
  digitalWrite(katup, LOW);  // Matikan katup
}

void lepas() {
  Serial.println("Lepas aktif");
  digitalWrite(vakum, LOW);  // Matikan vakum
  digitalWrite(katup, HIGH); // Aktifkan katup
}

void nol(){
  Dynamixel.moveSpeed(1, 400, 120);
  Dynamixel.moveSpeed(16, 400, 120);
  moveServoSmooth(servo2, 40, 3);
  moveServoSmooth(servo3, 50, 3);
  Serial.println("Tangan Standby");
}

void dekat() {
  Serial.println("Ambil sampah dekat");
  moveServos(400, 530, 40, 60, 2000);
  delay(1000);
  hisap();
  delay(2000);
  moveServosfirst(400, 530, 40, 50, 2000);
  moveServos(530, 400, 40, 60, 2000);
}

void jauh() {
  Serial.println("Ambil sampah jauh");
  moveServos(400, 550, 40, 52, 2000);
  delay(1000);
  hisap();
  delay(2000);
}

void tempatSampah() {
  Serial.println("Bawa ke tempat sampah");
  moveServos(400, 700, 0 , 10, 3000);
  delay(1000);
  moveServosfirst(400, 700, 0, 0, 1000);
  moveServosfirst(700, 400, 0, 0, 1000);
}