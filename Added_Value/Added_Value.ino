#include <Servo.h>
Servo servo1;
Servo servo2;
String printToIBoardBot = "";
int lineFinder = 0;
int charCount = 0;
int verticalLineCounter = 0;
int horizontalLineCounter = 0;
int verticalHalfLineCounter = 0;
int horizontalHalfLineCounter = 0;
void setup() {
  pinMode(4, OUTPUT); // ENABLE MOTORS
  pinMode(7, OUTPUT); // STEP MOTOR 1 PORTE,6
  pinMode(8, OUTPUT); // DIR MOTOR 1  PORTB,4
  pinMode(12, OUTPUT); // STEP MOTOR 2 PORTD,6
  pinMode(5, OUTPUT); // DIR MOTOR 2  PORTC,6. Low = right; High = left
  pinMode(13, OUTPUT); // Servo pin
  pinMode(10, OUTPUT); // Servo1
  pinMode(6, OUTPUT); // Servo2
  pinMode(2, OUTPUT); // SERVOs aux (on I2C)

  servo1.attach(10);
  servo2.attach(6);
  
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.println("Type the string you want the iBoardBot to print:");
  while(printToIBoardBot.length() == 0){
    Serial.setTimeout(1);
    printToIBoardBot = Serial.readString();
    if(printToIBoardBot == "ERASE"){
      servoEraseMode();
      for(int i = 0; i<10;i++){
        for(int x = 0; x<27;x++){
          if((i%2) == 0){
            servoEraseMode();
            horizontalLine();
          }
          else{
            servoEraseMode();
            digitalWrite(4,LOW); // Enables motors
            digitalWrite(5,HIGH);
            for(int x = 0; x < 1000;x++){
              digitalWrite(12, HIGH);
              delayMicroseconds(300);
              digitalWrite(12, LOW);
              delayMicroseconds(300);
            }
            digitalWrite(4,HIGH);
            horizontalLineCounter--;
          }
        }
        verticalHalfLine("LOW");
      }
      printToIBoardBot = "";
      for(int i = 0; i <= horizontalLineCounter + (int)(horizontalHalfLineCounter/2); i++){
        horizontalMoveLeft();
        horizontalLineCounter++;
      }
      for(int i = 0; i <= verticalLineCounter + (int)(verticalHalfLineCounter/2); i++){
        servoMoveMode();
        verticalLine("HIGH");
        verticalLineCounter++;
      }
    }
  }
  lineFinder = (int)(printToIBoardBot.length()/18);
  digitalWrite(4, LOW);
  servoMoveMode();
  if(lineFinder == 1 || lineFinder == 0){
    verticalLine("LOW");
    verticalLine("LOW");
    verticalLine("LOW");
  }
  if(lineFinder == 2){
    verticalLine("LOW");
    verticalLine("LOW");
    verticalLine("LOW");
    verticalHalfLine("LOW");
  }
  if(lineFinder == 3){
    verticalLine("LOW");
    verticalLine("LOW");
    verticalLine("LOW");
    verticalLine("LOW");
    verticalHalfLine("LOW");
  }
  horizontalLine();
  while(printToIBoardBot.length() != 0){
    servoDrawMode();
    if(printToIBoardBot.charAt(0) == 'A' || printToIBoardBot.charAt(0) == 'a'){
      verticalLine("LOW");
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalMoveLeft();
      horizontalLine();
      verticalHalfLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'B' || printToIBoardBot.charAt(0) == 'b'){
      verticalLine("LOW");
      verticalHalfLine("HIGH");
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalMoveLeft();
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == 'C' || printToIBoardBot.charAt(0) == 'c'){
      verticalLine("LOW");
      horizontalLine();
      verticalMoveDown();
      horizontalMoveLeft();
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == 'D' || printToIBoardBot.charAt(0) == 'd'){
      verticalHalfLine("LOW");
      horizontalLine();
      verticalHalfLine("LOW");
      verticalLine("HIGH");
      horizontalMoveLeft();
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == 'E' || printToIBoardBot.charAt(0) == 'e'){
      verticalLine("LOW");
      horizontalLine();
      horizontalMoveLeft();
      verticalHalfLine("HIGH");
      horizontalLine();
      horizontalMoveLeft();
      verticalHalfLine("HIGH");
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == 'F' || printToIBoardBot.charAt(0) == 'f'){
      verticalLine("LOW");
      horizontalLine();
      horizontalMoveLeft();
      verticalHalfLine("HIGH");
      horizontalLine();
      servoMoveMode();
      verticalHalfLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'G' || printToIBoardBot.charAt(0) == 'g'){
      verticalLine("LOW");
      horizontalLine();
      horizontalMoveLeft();
      verticalLine("HIGH");
      horizontalLine();
      verticalHalfLine("LOW");
      horizontalHalfLine("HIGH");
      horizontalHalfLine("LOW");
      verticalHalfLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'H' || printToIBoardBot.charAt(0) == 'h'){
      verticalLine("LOW");
      verticalHalfLine("HIGH");
      horizontalLine();
      verticalHalfLine("LOW");
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'I' || printToIBoardBot.charAt(0) == 'i'){
      horizontalHalfLine("LOW");
      verticalLine("LOW");
      horizontalHalfLine("HIGH");
      horizontalLine();
      servoMoveMode();
      verticalLine("HIGH");
      servoDrawMode();
      horizontalHalfLine("HIGH");
      horizontalHalfLine("LOW");
    }
    if(printToIBoardBot.charAt(0) == 'J' || printToIBoardBot.charAt(0) == 'j'){
      horizontalHalfLine("LOW");
      verticalLine("LOW");
      horizontalHalfLine("HIGH");
      horizontalLine();
      servoMoveMode();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'K' || printToIBoardBot.charAt(0) == 'k'){
      verticalLine("LOW");
      verticalHalfLine("HIGH");
      servoMoveMode();
      digitalWrite(4,LOW); // Enables motors
      digitalWrite(5,LOW);
      for(int x = 0; x < 250;x++){
        digitalWrite(12, HIGH);
        delayMicroseconds(300);
        digitalWrite(12, LOW);
        delayMicroseconds(300);
      }
      digitalWrite(4,HIGH);
      servoDrawMode();
      delay(100);
      forwardHalfSlash();
      servoMoveMode();
      verticalHalfLine("HIGH");
      delay(100);
      digitalWrite(4,LOW); // Enables motors
      digitalWrite(5,HIGH);
      for(int x = 0; x < 450;x++){
        digitalWrite(12, HIGH);
        delayMicroseconds(300);
        digitalWrite(12, LOW);
        delayMicroseconds(300);
      }
      digitalWrite(4,HIGH);
      servoDrawMode();
      backHalfSlash();
    }
    if(printToIBoardBot.charAt(0) == 'L' || printToIBoardBot.charAt(0) == 'l'){
      verticalLine("LOW");
      verticalLine("HIGH");
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == 'M' || printToIBoardBot.charAt(0) == 'm'){
      verticalLine("LOW");
      horizontalHalfLine("LOW");
      verticalLine("HIGH");
      verticalLine("LOW");
      horizontalHalfLine("LOW");
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'N' || printToIBoardBot.charAt(0) == 'n'){
      verticalLine("LOW");
      backSlash();
      verticalLine("LOW");
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'O' || printToIBoardBot.charAt(0) == 'o'){
      verticalLine("LOW");
      horizontalLine();
      verticalLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == 'P' || printToIBoardBot.charAt(0) == 'p'){
      verticalLine("LOW");
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalLine();
      servoMoveMode();
      verticalHalfLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'Q' || printToIBoardBot.charAt(0) == 'q'){
      verticalHalfLine("LOW");
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalMoveLeft();
      horizontalLine();
      verticalHalfLine("HIGH");
      verticalHalfLine("LOW");
    }
    if(printToIBoardBot.charAt(0) == 'R' || printToIBoardBot.charAt(0) == 'r'){
      verticalLine("LOW");
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalHalfLine("LOW");
      backHalfSlash();
    }
    if(printToIBoardBot.charAt(0) == 'S' || printToIBoardBot.charAt(0) == 's'){
      horizontalLine();
      verticalHalfLine("LOW");
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      verticalHalfLine("LOW");
      horizontalLine();
      servoMoveMode();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'T' || printToIBoardBot.charAt(0) == 't'){
      servoMoveMode();
      horizontalHalfLine("LOW");
      servoDrawMode();
      verticalLine("LOW");
      horizontalHalfLine("HIGH");
      horizontalLine();
      servoMoveMode();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'U' || printToIBoardBot.charAt(0) == 'u'){
      verticalLine("LOW");
      verticalLine("HIGH");
      horizontalLine();
      verticalLine("LOW");
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'V' || printToIBoardBot.charAt(0) == 'v'){
      servoMoveMode();
      verticalLine("LOW");
      servoDrawMode();
      backSlash();
      forwardSlash();
      servoMoveMode();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'W' || printToIBoardBot.charAt(0) == 'w'){
      verticalLine("LOW");
      verticalLine("HIGH");
      horizontalHalfLine("LOW");
      verticalLine("LOW");
      verticalLine("HIGH");
      horizontalHalfLine("LOW");
      verticalLine("LOW");
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'X' || printToIBoardBot.charAt(0) == 'x'){
      forwardSlash();
      servoMoveMode();
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      servoDrawMode();
      backSlash();
    }
    if(printToIBoardBot.charAt(0) == 'Y' || printToIBoardBot.charAt(0) == 'y'){
      servoMoveMode();
      verticalLine("LOW");
      servoDrawMode();
      backHalfSlash();
      verticalHalfLine("HIGH");
      verticalHalfLine("LOW");
      forwardHalfSlash();
      servoMoveMode();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == 'Z' || printToIBoardBot.charAt(0) == 'z'){
      horizontalLine();
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      forwardSlash();
      horizontalHalfLine("HIGH");
      horizontalHalfLine("HIGH");
      horizontalLine();
      servoMoveMode();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == ' '){
      servoMoveMode();
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == '3'){
      horizontalLine();
      verticalHalfLine("LOW");
      horizontalMoveLeft();
      horizontalLine();
      verticalHalfLine("LOW");
      horizontalMoveLeft();
      horizontalLine();
      verticalLine("HIGH");
    }
    if(printToIBoardBot.charAt(0) == '8'){
      verticalLine("LOW");
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalMoveLeft();
      horizontalLine();
      verticalHalfLine("HIGH");
      horizontalMoveLeft();
      horizontalLine();
    }
    if(printToIBoardBot.charAt(0) == '7'){
      forwardSlash();
      horizontalMoveLeft();
      horizontalLine();
      servoMoveMode();
      verticalLine("HIGH");
    }
    servoMoveMode();
    digitalWrite(4,LOW); // Enables motors
    digitalWrite(5,LOW);
    for(int x = 0; x < 500;x++){
      digitalWrite(12, HIGH);
      delayMicroseconds(300);
      digitalWrite(12, LOW);
      delayMicroseconds(300);
    }
    digitalWrite(4,HIGH);
    horizontalHalfLineCounter++;
    if(printToIBoardBot.length() != 1){
      printToIBoardBot = printToIBoardBot.substring(1);
    }
    else{
      printToIBoardBot = "";
    }
    charCount++;
    if(charCount == 18){
      newLine();
      charCount = 0;
    }
  }
  for(int i = 0; i <= horizontalLineCounter + (int)(horizontalHalfLineCounter/2); i++){
    horizontalMoveLeft();
    horizontalLineCounter++;
  }
  for(int i = 0; i <= verticalLineCounter + (int)(verticalHalfLineCounter/2); i++){
    servoMoveMode();
    verticalLine("HIGH");
    verticalLineCounter++;
  }
}
// Draws a vertical line in the indicated direction when in draw mode
void verticalLine(String dir){
  delay(50);
  digitalWrite(4,LOW); // Enables motors
  if(dir == "LOW"){
    digitalWrite(8,LOW);
    verticalLineCounter++;
  }
  else{
    digitalWrite(8,HIGH);
    verticalLineCounter--;
  }
  for(int x = 0; x < 750;x++){
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
}
// Draws a horizontal line right when in draw mode
void horizontalLine(){
  digitalWrite(4,LOW); // Enables motors
  digitalWrite(5,LOW);
  for(int x = 0; x < 1000;x++){
    digitalWrite(12, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  horizontalLineCounter++;
}
void horizontalHalfLine(String dir){
  delay(100);
  digitalWrite(4,LOW); // Enables motors
  if(dir == "LOW"){
    digitalWrite(5,LOW);
    horizontalHalfLineCounter++;
  }
  else{
    digitalWrite(5,HIGH);
    horizontalHalfLineCounter--;
  }
  for(int x = 0; x < 500;x++){
    digitalWrite(12, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
}
void verticalMoveDown(){
  servoMoveMode();
  delay(100);
  digitalWrite(4,LOW); // Enables motors
  digitalWrite(8,HIGH);
  for(int x = 0; x < 750;x++){
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  servoDrawMode();
  verticalLineCounter--;
}
void verticalHalfLine(String dir){
  delay(50);
  digitalWrite(4,LOW); // Enables motors
  if(dir == "LOW"){
    digitalWrite(8,LOW);
    verticalHalfLineCounter++;
  }
  else{
    digitalWrite(8,HIGH);
    verticalHalfLineCounter--;
  }
  for(int x = 0; x < 375;x++){
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
}
void horizontalMoveLeft(){
  servoMoveMode();
  delay(100);
  digitalWrite(4,LOW); // Enables motors
  digitalWrite(5,HIGH);
  for(int x = 0; x < 1000;x++){
    digitalWrite(12, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  servoDrawMode();
  horizontalLineCounter--;
}
void backSlash(){
  delay(100);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
  for(int x = 0; x < 750; x++){
    digitalWrite(12, HIGH);
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  horizontalLineCounter++;
  verticalLineCounter--;
}
void backHalfSlash(){
  delay(100);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,HIGH);
  for(int x = 0; x < 375; x++){
    digitalWrite(12, HIGH);
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  horizontalHalfLineCounter++;
  verticalHalfLineCounter--;
}
void forwardSlash(){
  delay(100);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  for(int x = 0; x < 750; x++){
    digitalWrite(12, HIGH);
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  horizontalLineCounter++;
  verticalLineCounter++;
}
void forwardHalfSlash(){
  delay(100);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(8,LOW);
  for(int x = 0; x < 375; x++){
    digitalWrite(12, HIGH);
    digitalWrite(7, HIGH);
    delayMicroseconds(300);
    digitalWrite(12, LOW);
    digitalWrite(7, LOW);
    delayMicroseconds(300);
  }
  digitalWrite(4,HIGH);
  horizontalHalfLineCounter++;
  verticalHalfLineCounter++;
}
// Sets the servos to the proper angles so the pen will write 
void servoDrawMode(){
  servo2.write(100);
  servo1.write(110);
}
// Sets the servos to the proper angles so the eraser will erase
void servoEraseMode(){
  servo2.write(100);
  servo1.write(50);
}
// Sets the servos to the proper angles so the eraser won't erase and the pen won't write
void servoMoveMode(){
  servo2.write(50);
  servo1.write(110);
}
void newLine(){
  servoMoveMode();
  verticalLine("HIGH");
  verticalHalfLine("HIGH");
  for(int i = 0; i < 18; i++){
    servoMoveMode();
    digitalWrite(4,LOW); // Enables motors
    digitalWrite(5,HIGH);
    for(int x = 0; x < 500;x++){
      digitalWrite(12, HIGH);
      delayMicroseconds(300);
      digitalWrite(12, LOW);
      delayMicroseconds(300);
    }
    digitalWrite(4,HIGH);
    horizontalMoveLeft();
  }
}

