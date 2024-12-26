void read_XY(){
  parseGyro();
  rX = JPP * pos3;
  rY = JPP * pos2;
  X = -(cos(radians(theta)) * rX - sin(radians(theta)) * rY);
  Y = -(sin(radians(theta)) * rX + cos(radians(theta)) * rY);
  theta = -(dataGyro-offsetGyro);
  T = theta;
}

void print_XY(){
  read_XY();
  Serial.print(X); Serial.print(" | ");
  Serial.print(Y); Serial.print(" | ");
  Serial.println(T);
  // Serial.println(dataGyro);
}

void pid_XYT(int x, int y, int t, int max){
  read_XY();
  //error saat ini
  errorX = x - X;
  errorY = y - Y;
  errorT = t - theta;

  //Hitung P, I D 
  Px = errorX * kp;
  Ix = (errorX + errorpX) * ki;
  Dx = (errorX - errorpY) * kd;

  Py = errorY * kp;
  Iy = (errorY + errorpY) * ki;
  Dy = (errorY - errorpY) * kd;

  Pt = errorT * kp;

  //It = (errorT + errorPt) * ki;

  // Menjulahkan PID

  PIDx = Px + Ix + Dx;
  PIDy = Py + Iy + Dy;
  PIDt = Pt + It + Dt;

  // NIlai PID yang dibatasi
  PIDX = constrain(PIDx, -max, max);
  PIDY = constrain(PIDy, -max, max);
  PIDT = constrain(PIDt, -180, 180);


  inverseKinematics(PIDX, PIDY, -PIDT, max);

  //Simpan error sebelumnya

  errorpX = errorX;
  errorpY = errorY;
  errorpT = errorT;
}