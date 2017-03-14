#include <Servo.h>
Servo myservo1, myservo2;

int servo1pin = 8,
    servo2pin = 10;

int beat = 120;

void setup() {
  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
}

void loop() {
  myservo1.write(50);
  myservo2.write(50);
  delay(200);
  myservo1.write(130);
  myservo2.write(130);
  delay(200);

}
