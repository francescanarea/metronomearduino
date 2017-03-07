int photoresistorPin = A4; //value of resistor 
int ledPin = 3; //value of led pin 
int photoresistorValue = 0; //where current read of photoresistor
int range = 300;//value when light is on 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  photoresistorValue = analogRead(photoresistorPin); //reads the photoresistor value 
  Serial.println(photoresistorValue); //displays values of photoresistor 
  
  digitalWrite(ledPin, LOW); //LED off by default

  if(photoresistorValue < range) //once the value goes below 300, turns on the light 
      digitalWrite(ledPin, HIGH); //turn LED on 
}
