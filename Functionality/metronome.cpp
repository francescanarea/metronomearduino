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

	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
	
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
		executeMetronome(metronomeExecuteBuzzer, beat);
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

	

	
	
}

void executeMetronome(bool metronomeExecuteBuzzer, int beat){
	//executeServo(beat);
	
	executeLeds(beat);
	
	if(metronomeExecuteBuzzer){
		executeBuzzer(int beat);
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

void executeLeds(int beat ){
    digitalWrite(ledPin, HIGH);
    delay(beat);
    digitalWrite(ledPin, LOW);
}





