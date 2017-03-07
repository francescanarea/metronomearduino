int beat = 0; //variable to store beat once calculated
int count = 0; //counts the number of beats it has recieved
//the metronome will initially not be playing and once it recieves 4 input taps
bool metronomeExecute = false; 

//pin setup here





//setting up the pins, photoresistor, buzzer, buttons, LEDs
void setup(){
	pinMode(button1, INPUT);
	pinMode(button2, INPUT);
	pinMode(button3, INPUT);
	pinMode(button4, INPUT);

	pinMode(buzzer, OUTPUT);

	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
	
	pinMode(button, OUTPUT);

	Serial.begin(9600);
}

//main part that will loop the metronome code
void loop(){
	
	//photoresistor code
	
	//if 4 input taps are recieved, 
	metronomeExecute = true;
	

	
	if(metronomeExecute){
		executeMetronome();
	}
	
}

void executeMetronome(){
	executeServo();
	executeBuzzer();
	executeLeds();

}

void calculateBeat(){

}


void executeServo(){

}

void executeBuzzer(){

}

void executeLeds(){

}





