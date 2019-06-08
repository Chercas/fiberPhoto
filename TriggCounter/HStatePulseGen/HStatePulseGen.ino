//-----PINs DEFs------
const int laserPin3 = 3;
const int triggPin = 7;

//------FREQUENCY------
const int frequency = 20; //Hz
/*
 * interval parameter should not exceed 
 * LASER RISE/FALL time in milliseconds
 */
const long interval = 1000/(2*frequency); //ms

//------HIGH intencity- 
const int intensity_L = 10;

//------LOW  intencity-
const int intensity_H = 50;

//-----INIT Conditions-
int triggState = LOW;
int laserState = intensity_L;
unsigned long previousMillis = 0; //ms

void setup() {
  // put your setup code here, to run once:
  pinMode(laserPin3, OUTPUT);
  pinMode(triggPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  triggState = digitalRead(triggPin);

  if (triggState == HIGH){

    unsigned long currentMillis = millis();
//-------------PULSE GENERATOR--------------
/*
 * Real-time PULSE GENERATOR 
 */
    while (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;
      laserState == intensity_L ? laserState = intensity_H : laserState = intensity_L;
    }
    analogWrite(laserPin3, laserState);
//-----------------END----------------------
  }else{
    analogWrite(laserPin3, intensity_L);
  }
}
