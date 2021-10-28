/*
 Test_RGBPWM_v2 : CC1310 Slave device application for single 5050 LED

 This program receives command from master CC1310 device via EasyLink API. 
 Inteprets command into an input string for further processing of device ID
 and RGB values. 

 If device ID is correct, programm wil proceed to change the RGB LED state
 accordingly. The respective output pins for red, green, blue can be customiszed.
 BoardID can also be customiszed in order to match each slave device.
 
*/

//Sub 1GHz setup..
#include "EasyLink.h"
EasyLink_RxPacket rxPacket;
EasyLink_TxPacket txPacket;
EasyLink myLink;
String txt = "";


// Let's use #define to rename our pins from numbers to readable variables
// This is good practice when writing code so it is less confusing to read
#define RED 19 // pin 19 is always PWM capable according to LaunchPad standard
#define GREEN 13 // may need to change this for your LaunchPad
#define BLUE 12 // may need to change this for your LaunchPad
#define delayTime 10 // delay between color changes, 10ms by default
#define BOARDID "0001"

// Here we can introduce some global variables. These variables have a type
// (int) and a name. We can use the variables in any function that comes after
// Global variables are useful because we can save the state of a variable to
// use in later operations and functions.

//RGD LED Command syntax as follows: XXXXRXXXGXXXB AAX00010R000G255B000BB
String strValue = "";
bool bReadDone = false;
String BoardID = BOARDID; // change this according to desired device identification
/* This is our setup function. We want to set our LED pins as OUTPUT.
 * We can also set them to HIGH at the beginning.
 */
void setup() {
 // We don't have to use pinMode() when using analogWrite() but it doesn't
 // hurt to use it, especially if we want to call digitalWrite() for the
 // same pin in the same sketch.
 
 //INTIALISE LEDs 
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE, OUTPUT);

  //Sub 1GHz setup..
  Serial.begin(9600);
  // begin defaults to EasyLink_Phy_50kbps2gfsk
  myLink.begin();
  Serial.println(myLink.version());
   
}

/* In the loop function we will...
 */
char d[128];
//String d = "";
void loop() {
  /* Start processing Sub 1GHz*/
  // Wait / block for 2 second to receive a packet.
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(2000);
  // Turn the receiver on immediately
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
  
  EasyLink_Status status = myLink.receive(&rxPacket);
  
  if (status == EasyLink_Status_Success) {
    memcpy(&d, &rxPacket.payload, sizeof(d));
    Serial.print("Packet received with lenght ");
    Serial.print(rxPacket.len);
    Serial.print(" and value ");
    
    Serial.println(d); //value
    bReadDone = true;
    strValue = d;

  } else {
//    Serial.print("Error receiving packet with status code: ");
//    Serial.print(status);
//    Serial.print(" (");
//    Serial.print(myLink.getStatusString(status));
//    Serial.println(")");
  }
  
 /* Start processing LED */
  if (bReadDone){
    bReadDone = false;
    writeLEDfromStr(strValue);
  }
// delay( delayTime ); // wait for how long delay time is
 
}


void sendStatus() {
  char data[128];
  String txt ="AAX00010R255G255B255BB";
  txt.toCharArray(data, sizeof(data));
  memcpy(&txPacket.payload, &data, sizeof(data)); // Copy the String value into the txPacket payload
 
  txPacket.len = sizeof(data); // Set the length of the packet
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status

  if (status == EasyLink_Status_Success) {
    Serial.print("TX: ");
    //Serial.Println(data);
  }
  else {
    Serial.print("TX Error code: ");
    //SerialCC1.Print(String(status));
    //SerialCC1.Print(" (");
    //SerialCC1.Print(myLink.getStatusString(status));
    // SerialCC1.println(")");
  }
}

int writeLEDfromStr(String strValue);
{
    String IdCode, redCode, greenCode, blueCode;
    //split substring into RGB if relevant
    // assumes that command is : AAX00010R000G255B000BB
    IdCode = strValue.substring(3,7); //0001
    redCode = strValue.substring(9,12); 
    greenCode = strValue.substring(13,16);
    blueCode = strValue.substring(17,20);
    strValue = "";
    
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
