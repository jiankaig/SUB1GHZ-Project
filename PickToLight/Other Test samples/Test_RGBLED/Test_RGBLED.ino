int redPin= 19;//13;
int greenPin =13;//14;
int bluePin = 12;//15;
const int buttonPin = 11;// PUSH2;     // the number of the pushbutton pin

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     //INPUT_PULLUP

  // initialize led pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int redState = 1;
int greenState = 1;
int blueState = 1;
int State = 0;

void loop() {
  setColor(0, 1, 1); // Red Color
  delay(1000);
  setColor(1, 0, 1); // Green Color
  delay(1000);
  setColor(1, 1, 0); // Blue Color
  delay(1000);

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
