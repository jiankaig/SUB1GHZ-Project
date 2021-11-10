#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"


SerialCC SerialCC1;

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

void setup() {
  SerialCC1.Begin(9600);
  
  SerialCC1.Println("Hello");
  SerialCC1.Print("Starting.");

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
   
}

int i = 0;
void loop() {
  // receiving UART from CC3200
  char ch= SerialCC1.Read();

  if(ch!=0) //or use isAlphaNumeric(ch) && !isSpace(ch)
  {
    SerialCC1.Print(String(i)+":");
    SerialCC1.Print(ch);
    i += 1;
    SerialCC1.Print("\n");
  }
    
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