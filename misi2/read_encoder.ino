void readEncoder_1(){
int b = digitalRead(ENCB);
  if(b > 0){
    pos1++;
  }
  else{
    pos1--;
  }
}

void readEncoder_2(){
  int b = digitalRead(ENCD);
  if(b > 0){
    pos2++;
  }
  else{
    pos2--;
  }
}

void readEncoder_3(){
  int b = digitalRead(ENCF);
  if(b > 0){
    pos3++;
  }
  else{
    pos3--;
  }
}
