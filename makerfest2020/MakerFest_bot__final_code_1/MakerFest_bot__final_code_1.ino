#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8);

#include <Servo.h>
Servo servoFL;
Servo servoFR;
Servo servoBL;
Servo servoBR;

#define motorL1 12
#define motorL2 13
#define motorR1 9
#define motorR2 10
#define enL 11
#define enR 6

char data;
char dataLimitation;
int carSpeed=0;
int gateWatcher=0;

void setup() {
  mySerial.begin(38400);
  //Serial.begin(9600);
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);
  servoFL.attach(2);
  servoFR.attach(3);
  servoBL.attach(4);
  servoBR.attach(5);
  servoFL.write(145);
  servoFR.write(45);
  servoBL.write(45);
  servoBR.write(140);
  delay(100);
  servoFL.detach();
  servoFR.detach();
  servoBL.detach();
  servoBR.detach();
}

void loop() {
  while (mySerial.available()>0) {
    data = mySerial.read();
  }
  if (dataLimitation != data) {   
    if (data == 'w' && gateWatcher == 1) {
      openFront(15);
    }
    else if (data == 'W' && gateWatcher == 0) {
      closeFront(10);
    }
    else if (data == 'u') {
      if (gateWatcher == 0) {
        closeFront(5);
        openBack(8);
        openFront(15);
      }
      else if (gateWatcher == 1) {
        gateWatcher = 2;
      }
    }
    else if (data == 'U') {
      if (gateWatcher==0) {
        closeFront(10);
        closeBack(8);
        openFront(8);
      }
      else if (gateWatcher==1) {
        closeBack(10);
      }
      else if (gateWatcher==2) {
        gateWatcher=1;
      }
    }
    else if (data>='0' && data<='9') {
      carSpeed = ((int)data-48)*25;
    }
    else if (data=='q') {
      carSpeed = 250;
    }
  }

  if (data == 'F' || data == 'G' || data == 'I') {
    if (data == 'F') {
      analogWrite(enL, carSpeed);
      analogWrite(enR, carSpeed);
    }
    else if (data == 'G') {
      analogWrite(enL, 0);
      analogWrite(enR, carSpeed);
    }
    else if (data == 'I') {
      analogWrite(enL, carSpeed);
      analogWrite(enR, 0);
    }
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, HIGH);
    digitalWrite(motorR1, LOW);
    digitalWrite(motorR2, HIGH);
  } 
  else if (data == 'B' || data == 'H' || data == 'J') {
    if (data == 'B') {
      analogWrite(enL, carSpeed);
      analogWrite(enR, carSpeed);
    }
    if (data == 'H') {
      analogWrite(enL, 0);
      analogWrite(enR, carSpeed);
    }
    else if (data == 'J') {
      analogWrite(enL, carSpeed);
      analogWrite(enR, 0);
    }
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2, LOW);
    digitalWrite(motorR1, HIGH);
    digitalWrite(motorR2, LOW);
  }
  else if (data == 'L') {
    analogWrite(enL, carSpeed);
    analogWrite(enR, carSpeed);
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2, LOW);
    digitalWrite(motorR1, LOW);
    digitalWrite(motorR2, HIGH);
  }
  else if (data == 'R') {
    analogWrite(enL, carSpeed);
    analogWrite(enR, carSpeed);
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, HIGH);
    digitalWrite(motorR1, HIGH);
    digitalWrite(motorR2, LOW);
  }
  else {
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, LOW);
    digitalWrite(motorR1, LOW);
    digitalWrite(motorR2, LOW);
  }
    
  dataLimitation = data;
}

void closeFront(int y){
  servoFL.attach(2);
  servoFR.attach(3);
  for(int x=135; x>=45; x--){
    servoFL.write(x);
    servoFR.write(190-x);
    delay(y);
  }
  servoFL.detach();
  servoFR.detach();
  gateWatcher=1;
}

void openFront(int y){
  servoFL.attach(2);
  servoFR.attach(3);
  for(int x=45; x<=135; x++){
    servoFL.write(x);
    servoFR.write(190-x);
    delay(y);
  }
  servoFL.detach();
  servoFR.detach();
  gateWatcher=0;
}

void closeBack(int y){
  servoBL.attach(4);
  servoBR.attach(5);
  for(int x=45; x<=135; x++){
    servoBL.write(x);
    servoBR.write(185-x);
    delay(y);
  }
  servoBL.detach();
  servoBR.detach();
}

void openBack(int y){
  servoBL.attach(4);
  servoBR.attach(5);
  for(int x=135; x>=45; x--){
    servoBL.write(x);
    servoBR.write(185-x);
    delay(y);
  }
  servoBL.detach();
  servoBR.detach();
}
