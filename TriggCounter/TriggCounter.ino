// Connected equipment definitions
const int laserPin = 9; // Defining pin that communicates with laser
const int triggPin = 7; // Pin that receives trigger pulse
// Variables
int triggPulseCounter = 0; // Pulse counter
int triggState = 0; // Time dependant trigger state
int currTriggState = 0; // Last trigger TTL state
unsigned long previousMillis = 0;
const long interval = 50;
int laserState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(laserPin, OUTPUT);
  pinMode(triggPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Read the triggerPin current state
  triggState = digitalRead(triggPin);

  if (triggState != currTriggState){
    if (triggState == HIGH){
      triggPulseCounter++;
      
      Serial.print(triggPulseCounter);
      Serial.println(" - number of TRIGGER EVENTS");
    }
  }
  currTriggState = triggState;

// LASER blinking pattern
  
  if (triggPulseCounter%2 != 0){
    
    unsigned long currentMillis = millis();
    
    while (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    (laserState == LOW)?(laserState = HIGH):(laserState = LOW);
    }
    
    digitalWrite(laserPin, laserState);
  
  } else {  
        laserState = LOW;
  }
  
   digitalWrite(laserPin, laserState);
   
}
