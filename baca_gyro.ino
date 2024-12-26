void parseGyro(){
  int dataG;
  while(Serial2.available()>0){
    int inChar = Serial2.read();

    if(inChar != '\n'){
      inString += (char)inChar;
    }
    else{
      dataGyro = inString.toInt();
      inString= "";
    }
  }
}
