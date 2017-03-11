#include <Servo.h>
Servo myservo;

unsigned long time; //for timing the time in between the beats 

int beat = 0; //variable to store beat once calculated
int numTaps = 0; //counts the number of beats it has recieved
int numBeats = 0; //4 taps = 3 beats

//the metronome will initially not be playing and once it recieves 4 input taps
bool metronomeExecute = false; 
bool metronomeExecuteBuzzer = false;

const int buzzerToneForMetronome = 300;

const int PHOTORESISTOR_RANGE = 300;//upper bound value when resistor is covered (when it is below this, registers beat)
const int NUM_BEATS = 3; //the nubmer of beats the metronome requires to be measured in order to start 
const int NUM_TAPS = 4;
double userBeatTiming[NUM_BEATS]; //stores the NUM_BEATS beats based on user taps 
 
//pin setup here
int servo1pin = 8,
    servo2pin = 10,
    photoresistorPin = A0,
    led1pin = 2, 
    led2pin = 4,
    buzzer = 11;

int ledNum = 1;
int button1state = 0;
int button2state = 0;

bool button1on = false;
bool button2on = false;

bool tap = false, prevTap = false;

int buzzerPin = 4; //setup for buzzer pin on arduino board


//setting up the pins, photoresistor, buzzer, buttons, LEDs
void setup(){
//  pinMode(button1, INPUT);
//  pinMode(button2, INPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);

  digitalWrite(led1pin, LOW);
  digitalWrite(led1pin, LOW);
  
  myservo.attach(servo1pin); 

  Serial.begin(9600);
}


void loop(){
  //gets milliseconds since program was started or reset
  time = millis();

  
        
  //gets all the button states to see if song should be played, turning off the buzzer
//  button1state = digitalRead(button1Pin);
//  button2state = digitalRead(button2Pin);
//  button3state = digitalRead(button3Pin);
//  button4state = digitalRead(button4Pin);

//  if(numTaps == NUM_TAPS){
//    metronomeExecute = true;
//    metronomeExecuteBuzzer = true;
//    beat = calculateBeat(userBeatTiming);
//  }
//  
//  //if any of the buttons are pressed, if any of them are pressed then it will stop the buzzer because a song will be played instead
//  if(button1state == 1 || button2state == 1){
//    metronomeExecuteBuzzer = false; //will not let the metronome code with buzzer 
//  }
//  //checking button states to see if you should play any songs
//  if(button1state == 1 && button1on == false){
//    button1on = true;
//    playSong1(button1on);
//  }
//  if(button2state == 1 && button2on == false){
//    button2on = true;
//    playSong2(button2on);
//  }
//  if(button1on == false && button1state == 1){ 
//    button1on = false; //turns off the song
//  }
//  if(button2on == false && button2state == 1){
//    button2on = false; //turns off the song 
//  }
//
//  if(metronomeExecute){
//    executeMetronome(metronomeExecuteBuzzer, beat, ledNum);
//  }

  int photoresistorValue = analogRead(photoresistorPin); //reads the photoresistor value 
  int curBeat, curBeatTime, lastBeat;

  //numTaps = 10;
  
  if(numTaps<5){
    if(photoresistorValue < 1){ //once the value goes below 300, registers a beat 
      digitalWrite(led1pin, HIGH);
//      curBeat = time; //gets current milliseconds
//      if(numTaps != 1){
//        curBeatTime = curBeat - lastBeat;
//        userBeatTiming[numBeats] = curBeatTime;
//        numBeats++; //adds one to number of beats stored in array 
//      }
//      //saves the current time to use as last time to compare with next time its tapped
//      int lastBeat = time; 
      tap = true;
    }else{
      digitalWrite(led1pin, LOW);
      tap = false;
    }
    Serial.println(tap);
  }

  
  if(tap == false && prevTap == true)
    Serial.println("boi");
    numTaps++;
  prevTap = tap;
  
  //for tracking which led it plays based on teh beat
  ledNum++;
  if(ledNum == 5){
    ledNum = 1;
  }

}

void executeMetronome(bool metronomeExecuteBuzzer, int beat, int ledNum){
  //executeServo(beat);
  
  executeLeds(beat, ledNum);
  
  if(metronomeExecuteBuzzer){
    executeBuzzer(beat);
  }
}

int calculateBeat(double userBeatTiming[]){
  double num = 0.0;
  for(int i = 0; i<NUM_BEATS; i++){
    num += userBeatTiming[i];
  }
  return int(num/NUM_BEATS); //averages the beat timings to give you average beat for metronome in MILLISECONDS
}


//void executeServo(int beat){ 
//}

void executeBuzzer(int beat){
     tone(buzzerPin, buzzerToneForMetronome);
     delay(beat);
     noTone(buzzerPin);
}

void executeLeds(int beat, int ledNum){
    int curLedPinValue = 0; //just assumes 0 but will be changed based on ledNum
  
 //4 leds go one at a time ie, led1 for beat1, led2 for beat2, led3 for beat3, led4 for beat4 then loops again
    if(ledNum == 1){
      curLedPinValue = led1pin;
    }
   if(ledNum == 2){
      curLedPinValue = led2pin;
    }
    if(ledNum == 3){
      curLedPinValue = led2pin;
    }
    if(ledNum == 4){
      curLedPinValue = led2pin;
    }
  
    digitalWrite(curLedPinValue, HIGH);
    delay(beat);
    digitalWrite(curLedPinValue, LOW);
}

void playSong1(bool button1on){
  if(button1on){
    playShootingStar();
  }
}

void playSong2(bool button2on){
  if(button2on){
    //plays another song
  }
}

void playShootingStar(){

}

