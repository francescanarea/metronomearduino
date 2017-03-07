int white = 2;  //White LED is in pin 2
int led = 4;    //Purple LED is in pin 4

void setup() {
  //Set each pin to output
  pinMode(white, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  //Turn both LEDs on
  digitalWrite(white, HIGH);
  digitalWrite(led, HIGH);
  delay(125);

  //Turn purple LED off
  digitalWrite(led, LOW);
  delay(125);

  //Turn white off and purple on
  digitalWrite(white, LOW);
  digitalWrite(led, HIGH);
  delay(125);

  //Turn purple off
  digitalWrite(led, LOW);
  delay(125);
}
