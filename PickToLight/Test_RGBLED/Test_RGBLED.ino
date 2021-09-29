int redPin= 13;
int greenPin =14;
int bluePin = 15;

void setup() {

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void loop() {

  setColor(1, 0, 0); // Red Color
  delay(1000);
  setColor(0, 1, 0); // Green Color
  delay(1000);
  setColor(0, 0, 1); // Blue Color
  delay(1000);

}

void setColor(int redValue, int greenValue, int blueValue) {

  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);

}