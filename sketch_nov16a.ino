#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

int pinTrig[2] = {2, 6};
int pinEcho[2] = {3, 7};
char c;
int L[2] = {0,0};
int T;
int n[4] = {0, 0 ,0, 0};

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  for(int i = 0;i<2;i++)
    pinMode(pinTrig[i], OUTPUT);
  for(int i = 0;i<2;i++)
    pinMode(pinEcho[i], INPUT);
}


void loop() {
  if (mySerial.available()){  //mySerial
    c = mySerial.read();  //mySerial
    if (c=='g'){
    for (int i = 0; i<2;i++){
      digitalWrite(pinTrig[i], LOW); delayMicroseconds(2);
      digitalWrite(pinTrig[i], HIGH); delayMicroseconds(10);
      digitalWrite(pinTrig[i], LOW);
    
      T = pulseIn(pinEcho[i], HIGH);
    
      L[i] = T/58.82;
    
      if (L[i] < 20) {
          n[i] = i;
          mySerial.write(n[i]);  //mySerial
      }
      else if (L[i] >= 20){
          n[i+2] = i + 2;
          mySerial.write(n[i + 2]);  //mySerial
      }
     }

  }
  }
}
