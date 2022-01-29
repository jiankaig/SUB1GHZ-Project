/*
 Test_RGBPWM_v2 : CC10 Slave device application for single 5050 LED

 This program receives command from master CC10 device via EasyLink API. 
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
#define RED 13 // pin 19 is always PWM capable according to LaunchPad standard
#define GREEN 19 // may need to change this for your LaunchPad
#define BLUE 12 // may need to change this for your LaunchPad
#define buttonPin 11//PUSH1 // button pin PUSH1 //13
#define delayTime 10 // delay between color changes, 10ms by default
#define BOARDID "0002" //Change this number for the board ID

String BoardID = BOARDID; // change this according to desired device identification

// Here we can introduce some global variables. These variables have a type
// (int) and a name. We can use the variables in any function that comes after
// Global variables are useful because we can save the state of a variable to
// use in later operations and functions.
int redVal;
int greenVal;
int blueVal;

//RGD LED Command syntax as follows: XXXXRXXXGXXXB AAX00010R000G255B000BB
String IdCode;
String redCode;
String greenCode;
String blueCode;
String strValue = "";
bool bReadDone = false;

//const byte buttonPin = 11;// PUSH2; Number of pushbutton pin
uint16_t value;

//For Button and debounce variables
volatile byte buttonState = LOW;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
volatile byte state = HIGH;
bool state_Send = false;
char d[32]; //128
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

//interurpt state change 
void blink() {
  state = !state;
}
/* In the loop function we will...
 */

//String d = "";
void loop() {
  //buttonState = digitalRead(buttonPin);  //read ack
  if(state == LOW)
  {
    //rxPacket.absTime = EasyLink_ms_To_RadioTime(1);
    reset_LED();
    sendStatus(strValue, '2');
    buttonState = HIGH;
  }
  
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(150);
  // Turn the receiver on immediately
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
  
  EasyLink_Status status = myLink.receive(&rxPacket);
  
  if (status == EasyLink_Status_Success) {
    //memcpy(&value, &rxPacket.payload, sizeof(uint16_t));
    memcpy(&d, &rxPacket.payload, sizeof(d));
    Serial.print("Packet received with lenght ");
    Serial.print(rxPacket.len);
    Serial.print(" and value ");
    
    Serial.println(d); //value
    bReadDone = true;
    strValue = d;

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

void sendStatus(String strValue, char status_) {
  char data[32]; //128
  String txt = strValue + status_;
  txt.toCharArray(data, sizeof(data));
  memcpy(&txPacket.payload, &data, sizeof(data)); // Copy the String value into the txPacket payload
 
  txPacket.len = sizeof(data); // Set the length of the packet
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status

  if (status == EasyLink_Status_Success) {
    Serial.print("TX: ");
    Serial.println(data);
    //digitalWrite(buttonPin, LOW);
  }
  else {
    Serial.print("TX Error code: ");
  }
//  delay(1000);
}
