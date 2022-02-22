/*
 CC1310_Single_LED : CC1310 Slave device application for single 5050 LED

 This program receives command from master CC1310 device via EasyLink API. 
 Inteprets command into an input string for further processing of device ID
 and RGB values. 

 If device ID is correct, programm wil proceed to change the RGB LED state
 accordingly. The respective output pins for red, green, blue can be customiszed.
 BoardID can also be customiszed in order to match each slave device.
 
*/
#include "Led_Controller.h"
#include "Button_Controller.h"
#include "EasyLink_Controller.h"

Led_Controller LedHandler = Led_Controller();
Button_Controller ButtonHandler = Button_Controller();
EasyLink_Controller easylinkHandler = EasyLink_Controller();

char data_[32]; //128
bool bReadDone;
String strValue = "";
bool bButtonState = false;
/* This is our setup function. We want to set our LED pins as OUTPUT.
 * We can also set them to HIGH at the beginning.
 */
void setup() {
 // We don't have to use pinMode() when using analogWrite() but it doesn't
 // hurt to use it, especially if we want to call digitalWrite() for the
 // same pin in the same sketch.
 //INTIALISE as Red first //ALL TO HIGH, no colour
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  
  //Sub 1GHz setup..
  Serial.begin(9600);
  easylinkHandler.begin();

}


/* In the loop function we will...
 */
void loop() {
  
  bButtonState = ButtonHandler.UpdateButtonState();
  if(bButtonState){
    LedHandler.reset_LED();
    easylinkHandler.sendStatusWithFeedback(strValue, '2');
  }

  bReadDone = easylinkHandler.receive(data_);
  strValue = data_;

 /* Start processing LED */
  if (bReadDone){
    bReadDone = false;
    int bLED_Command_Success;
    bLED_Command_Success = LedHandler.writeLEDfromStr(strValue);
    if(bLED_Command_Success == 1)
      easylinkHandler.sendStatusWithFeedback(strValue, '1'); // sendStatus(strValue, '0'); 0 if timeout???
  }
}
