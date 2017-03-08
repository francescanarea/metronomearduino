int beat = 0; //variable to store beat once calculated
int count = 0; //counts the number of beats it has recieved
//the metronome will initially not be playing and once it recieves 4 input taps
bool metronomeExecute = false; 
bool metronomeExecuteBuzzer = false;

const buzzerToneForMetronome = 300;

const PHOTORESISTOR_RANGE = 300;//upper bound value when resistor is covered (when it is below this, registers beat)
const NUM_BEATS = 4; //the nubmer of beats the metronome requires to be measured in order to start 
double userBeatTiming[NUM_BEATS]; //stores the NUM_BEATS beats based on user taps 
 
//pin setup here
//int servopin = 
//int photoresistorPin = 
//int led1pin
//int led2pin
//int led3pin
//int led4pin

int ledNum = 1;
int button1state = 0;
int button2state = 0;
int button3state = 0;
int button4state = 0;

int buzzerPin = 4; //setup for buzzer pin on arduino board

//setting up the pins, photoresistor, buzzer, buttons, LEDs
void setup(){
	pinMode(button1, INPUT);
	pinMode(button2, INPUT);
	pinMode(button3, INPUT);

	pinMode(buzzer, OUTPUT);

	pinMode(led1pin, OUTPUT);
	pinMode(led2pin, OUTPUT);
	pinMode(led3pin, OUTPUT);
	pinMode(led4pin, OUTPUT);
	
	myservo.attach(servopin); // attaches the servo on pin 12 to a servo object

	Serial.begin(9600);
}

//main part that will loop the metronome code
void loop(){
	//gets all the button states to see if song should be played, turning off the buzzer
	button1state = digitalRead(button1Pin);
	button2state = digitalRead(button2Pin);
	button3state = digitalRead(button3Pin);
	button4state = digitalRead(button4Pin);

	if(count == NUM_BEATS){
		metronomeExecute = true;
		metronomeExecuteBuzzer = true;
		beat = calculateBeat(userBeatTiming);
	}
	
	//if any of the buttons are pressed, 
	if(button1state == 1 || button2state == 1 || button3state == 1 || button4state == 1){
		metronomeExecuteBuzzer = false; //will not let the metronome code with buzzer 
	}
	
	photoresistorValue = analogRead(photoresistorPin); //reads the photoresistor value 
	//gets value of buttons, if any of them are pressed then it will stop the metronome
	
	if(metronomeExecute){
		executeMetronome(metronomeExecuteBuzzer, beat, ledNum);
	}
	
	//photoresistor code
  	//Serial.println(photoresistorValue); //displays values of photoresistor for debugging
  
  	//digitalWrite(ledPin, LOW); //LED off by default

	//when photoresistor is covered, 
  	if(photoresistorValue < PHOTORESISTOR_RANGE){ //once the value goes below 300, registers a beat 
      		count++; //increases the count when the photoresistor is covered
		
		//GET TIME
		curBeatTime = //somevalue
		userBeatTiming[count-1] = curBeatTime
		
		//digitalWrite(ledPin, HIGH); //turn LED on 
	}

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
    	curLedPinValue = led3pin;
    }
    if(ledNum == 4){
    	curLedPinValue = led4pin;
    }
	
    digitalWrite(curLedPinValue, HIGH);
    delay(beat);
    digitalWrite(curLedPinValue, LOW);
}





