#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

int led[2] = {12, 13};
char c;
char r;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  for(int i = 0;i<2;i++)
      pinMode(led[i], OUTPUT);
}

void susin(char r) {
  switch (r){
    case 'n':
    digitalWrite(led[0], LOW);
    break;
    case 'y':
    digitalWrite(led[0], HIGH);
    break;
    case 'N':
    digitalWrite(led[1], LOW);
    break;
    case 'Y':
    digitalWrite(led[1], HIGH);
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
