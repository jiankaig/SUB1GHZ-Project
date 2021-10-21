int redPin= 19;//13;
int greenPin =13;//14;
int bluePin = 12;//15;
const int buttonPin = 5;// PUSH2;     // the number of the pushbutton pin

void setup() {
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);     //INPUT_PULLUP
  
  // initialize led pins as output
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.print("setup..");
}

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int State = 0;

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //update state when button pressed
  if( buttonState == HIGH){
    Serial.print("ok ");
    State++;
    if(State >3)
    {
      State=0;
    }
  }
  
    //state machine
  switch (State){
    case 0: //off all coloursled
      Serial.print("ok 1");
      setColor(1, 1, 1);
      break;
    case 1: //on red
      setColor(0, 1, 1);
      Serial.print("ok 2");
      break;
    case 2: //on green
      setColor(1, 0, 1);
      Serial.print("ok 3");
      break;
    case 3: //on blue
      setColor(1, 1, 0);
      Serial.print("ok 4");
      break;
    default: State = 0;
    }
  
}

void setColor(int redValue, int greenValue, int blueValue) {
  //reset all to high
  digitalWrite(redPin, 1);
  digitalWrite(greenPin, 1);
  digitalWrite(bluePin, 1);

  //write respective pins
  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);

}
