#include <Servo.h>
Servo myservo;

int pin = 12, b1 = 3, b2 = 4;
int pos = 0;

void setup(){
  myservo.attach(pin); // attaches the servo on pin 12 to a servo object
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  Serial.begin(9600);
}

void loop(){
  myservo.attach(pin);
  pos=0;
  if(digitalRead(b1) == HIGH){
    myservo.write(0);
    delay(50);
  }
  if(digitalRead(b2) == HIGH){
    myservo.write(180);
    delay(50);
  }
  myservo.detach();
}
