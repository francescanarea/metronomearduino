#include <Servo.h>
Servo myservo1, myservo2;

unsigned long time; //for timing the time in between the beats 

const int buzzerToneForMetronome = 600;
const int NUM_BEATS = 3; //the nubmer of beats the metronome requires to be measured in order to start 
const int NUM_TAPS = 4;

int beat = 10000, //variable to store beat once calculated
    beatNum = 1,
    numTaps = 0, //counts the number of beats it has recieved
    numBeats = 0, //4 taps = 3 beats
    curBeat=0, 
    curBeatTime=0, 
    lastBeat=0,
    count = 1;

double userBeatTiming[NUM_BEATS]; //stores the NUM_BEATS beats based on user taps 
 
//pin setup here
int servo1pin = 8,
    servo2pin = 10,
    tapper = 2,
    led1pin = 6, 
    led2pin = 7,
    buzzer = 11,
    button1 = 3,
    button2 = 4;

int button1state = 0,
    button2state = 0;

bool button1on = false,
     button2on = false;

bool tap = false, 
     prevTap = false;

bool terminate = false;

int batonDelay = 80, 
    halfBatonDelay = 45, 
    ledDelay = 20;

long startConducting = 2147483647;

//setting up the pins, photoresistor, buzzer, buttons, LEDs
void setup(){
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(tapper, INPUT);
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  digitalWrite(led1pin, LOW);
  digitalWrite(led2pin, LOW);
  
  myservo1.attach(servo1pin);
  myservo2.attach(servo2pin);
  myservo1.write(90);
  myservo2.write(120);

  Serial.begin(9600);
}


void loop(){
  //gets milliseconds since program was started or reset
  time = millis();

  //FIRST 4 BEATS
  if(numTaps < NUM_TAPS){
    int pressed = digitalRead(tapper);
    
    if(pressed == 1){
      tap = true;
      digitalWrite(led1pin, HIGH);
    }else{
      tap = false;
      digitalWrite(led1pin, LOW);
    }

    //if a beat is registered
    if(tap == false && prevTap == true){
      numTaps++;
      curBeat = time; //gives you time of current beat execution
      if(numTaps != 1){
        curBeatTime = curBeat - lastBeat;
        userBeatTiming[numBeats] = curBeatTime;
        numBeats++; 
      }
      lastBeat = time;
    }
  
  prevTap = tap;
  }

  //MAKE SURE BEAT ISN'T TOO SHORT
  if(beat<360){
    Serial.println("FAIL, beat too fast.");
    tone(buzzer, buzzerToneForMetronome);
    delay(1000);
    noTone(buzzer);
    //reset everything
    reset();
  }

  //ALL OTHER BEATS
  if(numTaps >= 4){
    beat = calculateBeat(userBeatTiming);

    if(count==1)
      startConducting = time;

    //LEDS ON 
    if(beatNum == 1){
      myservo1.write(90);
      myservo2.write(90);
      digitalWrite(led1pin, HIGH); 
      tone(buzzer, 2*(buzzerToneForMetronome));
    } 
    else if (beatNum == 2){
      myservo1.write(120);
      myservo2.write(120);
      digitalWrite(led2pin, HIGH); 
      tone(buzzer, buzzerToneForMetronome);
    }
    else if (beatNum == 3){ 
      myservo1.write(60);
      myservo2.write(90);
//      myservo2.write(120);
      digitalWrite(led2pin, HIGH); 
      tone(buzzer, buzzerToneForMetronome);
    }
    else { 
      myservo1.write(90);
      myservo2.write(120);
      digitalWrite(led2pin, HIGH); 
      tone(buzzer, buzzerToneForMetronome);
    }
    
    delay(ledDelay);
    
    //LEDS OFF
    if(beatNum == 1){ 
      digitalWrite(led1pin, LOW); 
    } else { 
      digitalWrite(led2pin, LOW); 
    }
    noTone(buzzer);

    if(beatNum == 2){
      delay(halfBatonDelay-ledDelay);
      myservo2.write(90);
      delay(beat-halfBatonDelay-ledDelay);
    } 
//    else if(beatNum == 3) {
//      delay(batonDelay-ledDelay);
//      myservo2.write(90);
//      delay(beat-batonDelay-ledDelay);
//    } 
    else {
      delay(beat-ledDelay);
    }

    count++;

    if(beatNum++ == 4){
      beatNum = 1;
    }

    int pressed = digitalRead(tapper);
    if(pressed == 1){
      terminate = true;
    }
  }
  
  int pressed1 = digitalRead(button1);
  int pressed2 = digitalRead(button2);
  if(count%4==1 || count==1){
    if(pressed1 == 1){
      Serial.println(button1on);  
      playShootingStar();
      count = 1;
    }
    if(pressed2 == 1){
      Serial.println(button2on);  
      playBumblebee();
      count = 1;
    }
  }
  
  //TERMINATE COUNT
  long elapsed = time - startConducting;
  if(elapsed >= 30000 || terminate){
    Serial.println("STOP");
    reset();
  }
  
}

int calculateBeat(double userBeatTiming[]){
  double num = 0.0;
  for(int i = 0; i<NUM_BEATS; i++){
    num += userBeatTiming[i];
  }
  return int(num/NUM_BEATS); //averages the beat timings to give you average beat for metronome in MILLISECONDS
}

void playShootingStar(){
  Serial.println("Shooting Star!");
  int frequencies[] = {330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 660};
  int notes[] = {11, 11, 12, 7, 4};
  int duration[] = {7,2,4,2,1};
  int bruh = sizeof(notes)/sizeof(int);
  
  if(beat==10000 || beat==360)
    beat = 480;
 
  for(int j = 0; j<4; j++){
    for(int i = 0; i<5;i++){
        tone(buzzer, frequencies[notes[i]]);
        if(i == 0){
          delay(beat/4);
          myservo1.write(90);
          myservo2.write(90);
          digitalWrite(led1pin, HIGH);
          delay(ledDelay);
          digitalWrite(led1pin, LOW);
          delay(beat-ledDelay);
          
          myservo1.write(120);
          myservo2.write(120);
          digitalWrite(led2pin, HIGH);
          delay(ledDelay);
          digitalWrite(led2pin, LOW);
          delay(halfBatonDelay-ledDelay);
          myservo2.write(90);
          delay(beat/2-halfBatonDelay);
        } 
        if (i == 1){
          delay(beat/2);
        }
        if (i == 2){ 
          myservo1.write(60);
          myservo2.write(90);
          digitalWrite(led2pin, HIGH);
          delay(ledDelay);
          digitalWrite(led2pin, LOW);
          delay(beat-ledDelay);
        }
        if (i == 3){ 
          myservo1.write(90);
          myservo2.write(120);
          digitalWrite(led2pin, HIGH);
          delay(ledDelay);
          digitalWrite(led2pin, LOW);
          delay((beat/2)-ledDelay);
        }
        if (i == 4){
          delay(beat/4);
        }
        noTone(buzzer);
        delay(10);
      }
    }
    delay(50);
  }


void playBumblebee(){
  Serial.println("Bumblebee!");
  int frequencies[] = {185, 196, 207, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 660, 698, 740};
  int notes[] = {16, 15, 14, 13, 12, 17, 16, 15, 16, 15, 14, 13, 12, 13, 14, 15};
  int duration[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

  if(beat==10000 || beat==480)
    beat = 360;

  for(int j = 0; j<4; j++){
    for(int i = 0; i<16;i++){
      tone(buzzer, 2*frequencies[notes[i]]);
      if(i==0){
        myservo1.write(90);
        myservo2.write(90);
        digitalWrite(led1pin, HIGH); 
      }
      if(i==4){
        myservo1.write(120);
        myservo2.write(90);
        digitalWrite(led2pin, HIGH);
      }
      if(i==8){
        myservo1.write(60);
        myservo2.write(90);
        digitalWrite(led2pin, HIGH);
      }
      if(i==12){
        myservo1.write(90);
        myservo2.write(120);
        digitalWrite(led2pin, HIGH);
      }
      delay(ledDelay);
      digitalWrite(led1pin, LOW); 
      digitalWrite(led2pin, LOW); 
      delay((beat/4-10)*duration[i]-ledDelay);
      noTone(buzzer);
      delay(10);
    }
  }
  delay(50);
}

void reset(){
  Serial.println("RESET");
  numTaps = 0;
  numBeats = 0;
  beat = 10000;
  beatNum = 1;
  count = 1;
  startConducting = 2147483647;
  myservo1.write(90);
  myservo2.write(120);
  terminate = false;
  delay(1000);
}

