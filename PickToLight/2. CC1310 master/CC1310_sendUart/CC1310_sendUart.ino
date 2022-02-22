#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"


SerialCC SerialCC1;

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

// constants won't change. Used here to Toggle LED
// set pin numbers:
const int greenledPin =  GREEN_LED;      // the number of the LED pin
const int redledPin =  RED_LED;      // the number of the LED pin

// Variables will change:
int greenledState = LOW;             // ledState used to set the LED
int redledState = LOW;             // ledState used to set the LED


void setup() {
  SerialCC1.Begin(115200);
//  Serial.begin(9600);
  
  SerialCC1.Println("SENDER");
//  SerialCC1.Print("Starting.");

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  // set the digital pin as output: for Led toogle
  pinMode(greenledPin, OUTPUT);  
  pinMode(redledPin, OUTPUT);
   
}

int i = 0;
void loop() {
  // sending UART
  SerialCC1.Print('c');
//  Serial.write('a');
  delay(1000);
  toggleRedLed();
    
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
}
