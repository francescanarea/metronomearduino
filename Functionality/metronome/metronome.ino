#include <Servo.h>
Servo myservo;

unsigned long time; //for timing the time in between the beats 

const int buzzerToneForMetronome = 600;
const int NUM_BEATS = 3; //the nubmer of beats the metronome requires to be measured in order to start 
const int NUM_TAPS = 4;

int beat = 0, //variable to store beat once calculated
    beatNum = 0,
    numTaps = 0, //counts the number of beats it has recieved
    numBeats = 0, //4 taps = 3 beats
    curBeat=0, 
    curBeatTime=0, 
    lastBeat=0;

double userBeatTiming[NUM_BEATS]; //stores the NUM_BEATS beats based on user taps 


/******* SONG STUFF ************/
int frequencies[] = {330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 660};
int notes[] = {11, 11, 12, 7, 4};
String names[] = {"d#", "d#", "e", "b", "g#"};
int duration[] = {7,2,4,2,1};
/*******************************/
 
//pin setup here
int servo1pin = 8,
    servo2pin = 10,
    tapper = 2,
    led1pin = 3, 
    led2pin = 4,
    buzzer = 11,
    button1 = 6,
    button2 = 7;

int button1state = 0,
    button2state = 0;

bool button1on = false,
     button2on = false;

bool tap = false, prevTap = false;

//setting up the pins, photoresistor, buzzer, buttons, LEDs
void setup(){
//  pinMode(button1, INPUT);
//  pinMode(button2, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(tapper, INPUT);
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
      Serial.print("Num Taps, ");
      Serial.println(numTaps);
      Serial.print("curBeatTime, ");
      Serial.println(curBeatTime);
    }
  
  prevTap = tap;
  
  }

  if(numTaps == 4){
    beat = calculateBeat(userBeatTiming);
//    Serial.print("Avg Beat: ");
//    Serial.println(beat);

    //LEDS ON 
    if(beatNum == 1){ 
      digitalWrite(led1pin, HIGH); 
      tone(buzzer, 2*(buzzerToneForMetronome));
    } 
    else{ 
      digitalWrite(led2pin, HIGH); 
      tone(buzzer, buzzerToneForMetronome);
    }
     
    delay(20);

    //LEDS OFF
    if(beatNum == 1){ digitalWrite(led1pin, LOW); } 
    else{ digitalWrite(led2pin, LOW); }
     
    noTone(buzzer);
    delay(beat);
 
    if(beatNum++ == 4){
      beatNum = 1;
    }
    Serial.println(beatNum);
  }
  
  int pressed1 = digitalRead(button1);
  if(pressed1 == 1){
    Serial.println(button1on);  
    playShootingStar();
  }
  
}

int calculateBeat(double userBeatTiming[]){
  double num = 0.0;
  for(int i = 0; i<NUM_BEATS; i++){
    num += userBeatTiming[i];
  }
  return int(num/NUM_BEATS); //averages the beat timings to give you average beat for metronome in MILLISECONDS
}
//
//bool checkButtonStatus(int buttonPinValue){ 
//  int buttonValue = digitalRead(buttonPinValue);
//  if(buttonValue == 1){
//     if(button1on){ 
//      button1on = false; 
//     } //button1on is global
//     else { button1on = true; }
//    }
//  return button1on;
//}



void playShootingStar(){
  int bruh = sizeof(notes)/sizeof(int);
  if(beat==0)
    beat = 480;
 
  for(int j = 0; j<2; j++){
    for(int i = 0; i<5;i++){
        tone(buzzer, frequencies[notes[i]]);
        Serial.println(frequencies[notes[i]]);
        delay((beat/4)*duration[i]);
        noTone(buzzer);
        delay(10);
      }
    }
  }


void playSong2(bool button2on){
  if(button2on){
    //plays another song
  }
}
