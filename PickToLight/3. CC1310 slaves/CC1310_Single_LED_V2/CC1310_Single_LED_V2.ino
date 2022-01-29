/*
 Test_RGBPWM_v2 : CC10 Slave device application for single 5050 LED

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

 pinMode(buttonPin, INPUT_PULLUP);  //Input as pullup
 attachInterrupt(digitalPinToInterrupt(buttonPin), blink, CHANGE);
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
}


/* In the loop function we will...
 */
void loop() {
  
  ButtonHandler.UpdateButtonState();
  
  
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(150);
  // Turn the receiver on immediately
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
  
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

 /* Start processing LED */
  if (bReadDone){
    bReadDone = false;
    int bLED_Command_Success;
    bLED_Command_Success = writeLEDfromStr(strValue);
    if(bLED_Command_Success == 1)
      sendStatus(strValue, '1'); // sendStatus(strValue, '0'); 0 if timeout???
  }
}

void reset_LED()
{
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

int writeLEDfromStr(String strValue)
{
    String IdCode, redCode, greenCode, blueCode;
    //split substring into RGB if relevant
    // assumes that command is : AAX00010R000G255B000BB
    IdCode = strValue.substring(3,7); //0001
    redCode = strValue.substring(9,12); 
    greenCode = strValue.substring(13,16);
    blueCode = strValue.substring(17,20);
//    strValue = "";
    
    //if ID matches this board ID, process LED\
    //change LED colour based on command sent
    if(IdCode == BoardID){
      //analogWrite( RED, redInt );
      analogWrite( RED, 255-redCode.toInt() );
      analogWrite( GREEN, 255-greenCode.toInt() );
      analogWrite( BLUE, 255-blueCode.toInt() );
      return 1;//success
    }
    return -1;//error BoardID mismatch
}


