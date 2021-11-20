//#include "SerialCC.h"
//#include "uart.h"
//#include "ioc.h"
//#include "prcm.h"


//SerialCC SerialCC1;

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

// constants won't change. Used here to Toggle LED
// set pin numbers:
const int greenledPin =  GREEN_LED;      // the number of the LED pin
const int redledPin =  RED_LED;      // the number of the LED pin
const int buttonPin = PUSH2;     // the number of the pushbutton pin

// Variables will change:
int greenledState = LOW;             // ledState used to set the LED
int redledState = LOW;             // ledState used to set the LED
int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  
  //SerialCC1.Begin(115200);
  Serial.begin(9600);
  
//  SerialCC1.Println("SENDER");
//  SerialCC1.Print("Starting.");

  // reserve 200 bytes for the inputString:
  //inputString.reserve(200);

  // set the digital pin as output: for Led toogle
  //pinMode(greenledPin, OUTPUT);  
  pinMode(redledPin, OUTPUT);
  //pinMode(buttonPin, INPUT_PULLUP); 
   
}

int i = 0;
char msg = 'c';
bool ReadStringDone = false;
void loop() {
//  if(buttonState)
//    checkButtonAndSendMsg(msg)//if bbutton is pressed, send uart and toggle red led 1sec
  
//  if(ReadStringDone == false){
//    // receiving UART
//    char ch= SerialCC1.Read();
//
//    if(isAlphaNumeric(ch) && !isSpace(ch)) //or use isAlphaNumeric(ch) && !isSpace(ch) // ch!=0
//    {
//      toggleGreenLed();
//      ReadStringDone = processInputString(ch, inputString);
//      delay(500);
//    }
//  }
//
//  if(ReadStringDone == true){
//    toggleRedLed();
//    // sending UART
//    SerialCC1.Print("message");
//    delay(5000);
////    toggleRedLed();
//  }
  Serial.print("msg");
  delay(500);  
}

void toggleGreenLed(){
  // if the LED is off turn it on and vice-versa:
    if (greenledState == LOW)
      greenledState = HIGH;
    else
      greenledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(greenledPin, greenledState);
}

void toggleRedLed(){
  // if the LED is off turn it on and vice-versa:
    if (redledState == LOW)
      redledState = HIGH;
    else
      redledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(redledPin, redledState);
}
  /*
bool processInputString(char ch, String& inputString){
  // add it to the inputString:
  inputString += ch;
  // if the incoming character is a newline, set a flag
  // so the main loop can do something about it:
  if (isAlphaNumeric(ch)) 
    stringComplete = true;
  else
    return false; // return stringComplete state

  if (stringComplete) {
    SerialCC1.Print("stringComplete");
    SerialCC1.Print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
    return true; // return stringComplete state
  }
}*/

/*
void checkButtonAndSendMsg(char msg){
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    buttonState = reading;
  }
  if(!buttonState){
    SerialCC1.Print(msg);
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}*/
