int redPin= 19;//13;
int greenPin =13;//14;
int bluePin = 12;//15;

void setup() {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

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
