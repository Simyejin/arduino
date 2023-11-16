#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

int led[2] = {12, 13};
char c;
int r;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  for(int i = 0;i<2;i++)
      pinMode(led[i], OUTPUT);
}

void susin(int r) {
  switch (r){
    case 0:
    digitalWrite(led[0], LOW);
    break;
    case 1:
    digitalWrite(led[1], LOW);
    break;
    case 2:
    digitalWrite(led[0], HIGH);
    break;
    case 3:
    digitalWrite(led[1], HIGH);
    break;
    default:
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    break;
  }
}

void loop() {
  if(Serial.available()){
    c = Serial.read();
    mySerial.write(c);
  }
  if(mySerial.available()){
    r = mySerial.read();
    susin(r);
  }
} 
