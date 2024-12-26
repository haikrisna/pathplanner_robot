#include <Servo.h>
#include <DynamixelSerial3.h>

int toleransi = 10;
int state = 0;

Servo servo2;
Servo servo3;
int katup = 27;
int vakum = 23;

unsigned long startT, currentT, stopT;

int dir1, dir2, dir3;
float pwmValue1, pwmValue2, pwmValue3;

int IN1A = 6;
int IN1B = 5;
int PWM1 = 7;

int IN2A = 9;
int IN2B = 8;
int PWM2 = 10;

int IN3A = 11;
int IN3B = 12;
int PWM3 = 13;

float M1, M2, M3;

int Vx = 0;  // kecepatan sumbu x (cm/s)
int Vy = 0;  // kecepatan sumbu y (cm/s)
int W = 0;   // kecepatan rotasi (deg/s)

int plan = 0;
int pos1 = 0, pos2 = 0, pos3 = 0;

#define ENCA 2// 
#define ENCB 16 // Interupt
#define ENCC 19 // INterupt2
#define ENCD 3 // Digital 2
#define ENCE 18 // INterupt 3
#define ENCF 4 // Digital 3

const float L = 13.5;  // Jarak dari pusat ke roda (cm)
const float R = 5.0;   // Jari-jari roda (cm)

float theTa;
float dataGyro;
float offsetGyro = 0;
String inString;

float X, Y, T, x, y, t, rX, rY;
float theta = 0, thetaA = 0;
float phi = 22/7;
float d = 10;
float PPR = 200;
float kel = phi * d;
const float JPP = kel / PPR;

float kp = 2; //2
float ki = 0.1; //0.1
float kd = 0.025; //0.025

float Px, Py, Pt, Ix, Iy, It, Dx, Dy, Dt, PIDx, PIDy, PIDt, PIDX, PIDY, PIDT, maxpwm;
int errorX, errorY, errorT;
float errorpX, errorpY, errorpT;

int setX = 0, setY = 0, setT = 0;
int lastC = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Dynamixel.begin(1000000, 22);  // Inisialisasi servo Dynamixel pada 1Mbps dengan pin kontrol 22
  servo2.attach(41); // Menghubungkan servo 2 ke pin 37
  servo3.attach(43); // Menghubungkan servo 3 ke pin 39
  delay(1000);
  nol();
  
  pinMode(katup, OUTPUT);
  pinMode(vakum, OUTPUT);

  pinMode(IN1A, OUTPUT);
  pinMode(IN1B, OUTPUT);
  pinMode(PWM1, OUTPUT);

  pinMode(IN2A, OUTPUT);
  pinMode(IN2B, OUTPUT);
  pinMode(PWM2, OUTPUT);

  pinMode(IN3A, OUTPUT);
  pinMode(IN3B, OUTPUT);
  pinMode(PWM3, OUTPUT);

  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(ENCC, INPUT);
  pinMode(ENCD, INPUT);
  pinMode(ENCE, INPUT);
  pinMode(ENCF, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder_1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCC), readEncoder_2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCE), readEncoder_3, RISING);

  parseGyro();
  startT = millis();
}

void loop() {
  // currentT = millis();
  // stopT = currentT-startT;
  // int kondisi = 0;
  // if(stopT >= 3000 && kondisi == 0){setX = 0, setY = 1000, setT = 0; Serial.println("1"); pid_XYT(0, 100, 0, 100);
  //   if(Y >= setY-toleransi){
  //     kondisi = 1;
  //     currentT = 0;
  //   }
  // }
  // if(kondisi == 1){X = 0, Y = 0, T = 90; setX = 0, setY = 0, setT = 0; Serial.println("2"); pid_XYT(0, 0, 90, 100);
  //   if(T >= setT-5){
  //     pid_XYT(0, 0, 0, 0);
  //   }
  // }
  // if(kondisi == 2){X = 0, Y = 0, T = 0; setX = 0, setY = 1000, setT = 0; Serial.println("3"); X = 0, Y = 0, T = 0; pid_XYT(0, 0, 0, 100);
  //   if(Y >= setY-toleransi){
  //     pid_XYT(0, 0, 0, 0);
  //   }
  // }
  // delay(2000);
  // print_XY();
  // inverseKinematics(0,80,0,190);
  // Serial.print(dataGyro); Serial.print(" | ");
  // Serial.print(pos1); Serial.print(" | ");
  // Serial.print(pos2); Serial.print(" | ");
  // pid_XYT(0, 100, 0, 250); //maju
  // Serial.println(errorY);
  // Serial.print(PIDX); Serial.print(" | ");
  // Serial.print(PIDY); Serial.print(" | ");
  // Serial.print(PIDT); Serial.print(" | ");
  // Serial.println(maxpwm);
  switch (state){
    startT = millis();
    default:
      pid_XYT(0, 0, 0, 0); 
      // Serial.print("Oke "); Serial.println(state);
      if(state == 1){state = 2;}
      if(state == 2){state = 3;}
      if(state == 3){state = 4;}
      if(state == 4){state = 5;}
      if(state == 5){state = 6;}
      if(state == 6){state = 7;}
      if(state == 7){state = 8;}
      if(state == 8){state = 9;}
      break;
      
      case 0: // maju ke posisi tengah
        pid_XYT(-40, 80, 0, 130); //maju
        print_XY();
        setX = 0; setY = 80; setT = 0;
        currentT = millis();
        stopT = currentT-startT;
        if(Y >= setY - toleransi){
          Serial.print("Oke "); Serial.println(state);
          X = 0, Y= 0, pos2 = 0, pos3 = 0;
          state += 1;
          }
        break;

      case 1: //geser Henti sejenak
        Serial.print("Diam"); Serial.println(state);        
        pid_XYT(0, 0, 0, 0); //diam
        delay(1500);
        state += 1;
      break;

      case 2: //putar ambil plastik Case 2 change per 5 50 dan 50 
        Serial.print("Plan 2 ");
        pid_XYT(0, 0, 45, 80); //rotasi
        print_XY();
        setX = 0; setY = 0; setT = 45;
        currentT = millis();
        stopT = currentT-startT;
        if(T >= setT-toleransi){
          // offsetGyro = dataGyro;
          pid_XYT(0, 0, 0, 0); //diam
          // theta = -(dataGyro-offsetGyro);
          Serial.print("Oke "); Serial.println(state);
          X = 0, Y= 0, T = 0, pos2 = 0, pos3 = 0;
          state += 1;
          }
        break;

      case 3: //Diam sebentar
      //   // inverseKinematics(0, -100, 0, 130);
        Serial.print("Diam"); Serial.println(state);        
        pid_XYT(0, 0, 0, 0); //diam
        X = 0, Y= 0, T = 0;
        delay(1500);
        offsetGyro = dataGyro-30;
        state += 1;
      break;

      case 4: // mundur untuk kiri 
        Serial.print("Plan 4 ");
        pid_XYT(0, 60, 0, 130); //maju ke bungkus kertas
        // print_XY();
        setX = 0; setY = 60; setT = 0;
        stopT = currentT-startT;
        Serial.print("Timer "); Serial.println(stopT);
        delay(250);
        // if(stopT >= 13500){
          pid_XYT(0, 0, 0, 0); //diam
          Serial.print("Oke "); Serial.println(state);
          X = 0, Y= 0, pos2 = 0, pos3 = 0;
          state += 1;
          // }
        break;
      case 5: //geser kiri ambil kertas bungkus dan buang ke kuning
      //   // inverseKinematics(0, -100, 0, 130);
        Serial.print("Diam"); Serial.println(state);        
        pid_XYT(0, 0, 0, 0); //diam
        delay(1500);
        state += 1;
      break;

      case 6: //putar dan buang sampah plastik
        jauh();
        delay(300);
        nol();
        delay(300);
        tempatSampah();
        delay(100);
        lepas();
        delay(300);
        state +=1;
      break;
  
      case 7: //geser kiri ambil kertas bungkus dan buang ke kuning
      //   // inverseKinematics(0, -100, 0, 130);
        Serial.print("Diam"); Serial.println(state);        
        pid_XYT(0, 0, 0, 0); //diam
        delay(1500);
        // state += 1;
      break;

      case 8: // mundur untuk kiri
        Serial.print("Plan 2 ");
        pid_XYT(0, 0, 60, 80); //rotasi
        print_XY();
        setX = 0; setY = 0; setT = 55;
        currentT = millis();
        stopT = currentT-startT;
        if(T >= setT-toleransi){
          // offsetGyro = dataGyro;
          pid_XYT(0, 0, 0, 0); //diam
          // theta = -(dataGyro-offsetGyro);
          Serial.print("Oke "); Serial.println(state);
          X = 0, Y= 0, T = 0, pos2 = 0, pos3 = 0;
          state += 1;
          }


      case 9: //geser kiri ambil kertas bungkus dan buang ke kuning
      //   // inverseKinematics(0, -100, 0, 130);
        Serial.print("Diam"); Serial.println(state);        
        pid_XYT(0, 0, 0, 0); //diam
        delay(1000);
      break;

  }
}