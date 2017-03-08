int pin = 4;

/* SHOOTING STAR */
int frequencies[] = {330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 660};
int notes[] = {11, 11, 12, 7, 4};
String names[] = {"d#", "d#", "e", "b", "g#"};
int duration[] = {7,2,4,2,1};
int beat = 120;

void setup() {
  Serial.begin(9600);
  pinMode(pin,OUTPUT);
//  tone(pin, 622, 1500);
}

void loop() {
  int bruh = sizeof(notes)/sizeof(int);
  for(int i = 0; i<5;i++){
    tone(pin, 2*frequencies[notes[i]]);
    Serial.println(frequencies[notes[i]]);
    delay(beat*duration[i]);
    noTone(pin);
    delay(10);
  }
}
