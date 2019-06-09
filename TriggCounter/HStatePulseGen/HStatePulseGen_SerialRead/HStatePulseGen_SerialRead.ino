const int numOfVals = 3; // how many comma separated fields we expect
int fieldIndex = 0;            // the current field being received
int values[numOfVals];   // array holding values for all the fields
char *message[] = {"LOW lvl -> ","HIGH lvl -> ","FREQUENCY -> "};

//-----PINs DEFs------
const int laserPin3 = 3;
const int triggPin = 7;

//------FREQUENCY------
int frequency = 20; //Hz

//------HIGH intensity- 
int intensity_L = 10;

//------LOW  intensity-
int intensity_H = 50;

//-----INIT Conditions-
int triggState = LOW;
int laserState = intensity_L;
unsigned long previousMillis = 0; //ms

void setup() {
  // put your setup code here, to run once:
  pinMode(laserPin3, OUTPUT);
  pinMode(triggPin, INPUT);
  Serial.begin(9600);
}

void loop() {

//-------------READING VALUES FROM SERIAL PORT------
  if( Serial.available())
  {
    char ch = Serial.read();
    if(ch >= '0' && ch <= '9') // ASCI [0 9]
    {
      // yes, accumulate the value
      values[fieldIndex] = (values[fieldIndex] * 10) + (ch - '0'); 
    }
    else if (ch == ',')  // comma is our separator, so move on to the next field
    {
      if(fieldIndex < numOfVals-1)
        fieldIndex++;   // increment field index
    }
    else
    {
      // any character not a digit or comma ends the acquisition of fields
      // in this example it's the newline character sent by the Serial Monitor
      //-------Assigning received values---------
      intensity_L = values[0];
      intensity_H = values[1]; 
      frequency = values[2];
      
      Serial.print( fieldIndex +1);Serial.println(" fields received:");
      
      for(int i=0; i <= fieldIndex; i++)
      {
        Serial.print(message[i]);Serial.println(values[i]);
        values[i] = 0; // set the values to zero, ready for the next message
      }
      fieldIndex = 0;  // ready to start over
    }
  }
  
// put your main code here, to run repeatedly:
  
  const long interval = 1000/(2*frequency); //in (ms) >> LASER RISE/FALL time!!!

  triggState = digitalRead(triggPin);

  if (triggState == HIGH){

//----------Real-time PULSE GENERATOR--------

    unsigned long currentMillis = millis();

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
