/*
 CC1310_Single_LED : CC1310 Slave device application for single 5050 LED

 This program receives command from master CC10 device via EasyLink API. 
 Inteprets command into an input string for further processing of device ID
 and RGB values. 

 If device ID is correct, programm wil proceed to change the RGB LED state
 accordingly. The respective output pins for red, green, blue can be customiszed.
 BoardID can also be customiszed in order to match each slave device.
 
*/
#include "Led_Controller.h"
#include "Button_Controller.h"
#include "EasyLink.h"
//const byte buttonPin = 11;// PUSH2; Number of pushbutton pin
EasyLink myLink;
Led_Controller LedHandler = Led_Controller(myLink);
Button_Controller ButtonHandler = Button_Controller(myLink);

char data_[32]; //128
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
  // begin defaults to EasyLink_Phy_50kbps2gfsk
  myLink.begin();
  Serial.println(myLink.version());

  // Set the destination address to 0xaa
  txPacket.dstAddr[0] = 0xaa;

  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(150);
  // Turn the receiver on immediately
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
}


/* In the loop function we will...
 */
void loop() {
  
  ButtonHandler.UpdateButtonState();


  //EasyLink check receive, Serial printout, update bReadDone and store to strValue
  EasyLink_Status status = myLink.receive(&rxPacket);
  
  if (status == EasyLink_Status_Success) {
    memcpy(&data_, &rxPacket.payload, sizeof(data_));
    Serial.print("Packet received with lenght ");
    Serial.print(rxPacket.len);
    Serial.print(" and value ");
    
    Serial.println(data_); //value
    bReadDone = true;
    strValue = data_;

  } else {

     Serial.println("Error receiving packet with status code: ");
//    Serial.print(status);
//      Serial.print(" (");
//      Serial.print(myLink.getStatusString(status));
//      Serial.println(")");
  }
//END of EasyLink check receive, Serial printout, update bReadDone and store to strValue

 /* Start processing LED */
  if (bReadDone){
    bReadDone = false;
    int bLED_Command_Success;
    bLED_Command_Success = LedHandler.writeLEDfromStr(strValue);
    if(bLED_Command_Success == 1)
      sendStatus(strValue, '1'); // sendStatus(strValue, '0'); 0 if timeout???
  }
}
