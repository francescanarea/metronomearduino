#include <Servo.h>
Servo myservo1, myservo2;

int servo1pin = 8,
    servo2pin = 10;

int beat = 120;
int wait = 700;
int upDown = 100;
int half = upDown/2;

void setup() {
  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
  Serial.begin(9600);
}

void loop() {
  myservo1.write(90);
  myservo2.write(90);
  Serial.println("90, 90");
  delay(wait);

  myservo1.write(120);
  myservo2.write(120);
  delay(half);
  myservo2.write(90);
  Serial.println("150, 90");
  delay(wait-half);
  
  myservo1.write(60);
  myservo2.write(120);
  delay(upDown);
  myservo2.write(90);
  Serial.println("30, 90");
  delay(wait-upDown);
  
  myservo1.write(90);
  myservo2.write(120);
  delay(upDown);
  Serial.println("90, 150");
  delay(wait-upDown);
}
