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
#define RED 19 // pin 19 is always PWM capable according to LaunchPad standard
#define GREEN 11 // may need to change this for your LaunchPad
#define BLUE 12 // may need to change this for your LaunchPad
#define buttonPin 13 // button pin PUSH1
#define delayTime 10 // delay between color changes, 10ms by default
String BoardID = "0002"; // change this according to desired device identification

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
int PWM_RESOLUTION = 255; // this variable will hold our resolution.
//const byte buttonPin = 11;// PUSH2; Number of pushbutton pin
uint16_t value;

//For Button and debounce variables
volatile byte buttonState = LOW;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
volatile byte state = LOW;
bool state_Send = false;
char d[128];
/* This is our setup function. We want to set our LED pins as OUTPUT.
 * We can also set them to HIGH at the beginning.
 */
void setup() {
 // We don't have to use pinMode() when using analogWrite() but it doesn't
 // hurt to use it, especially if we want to call digitalWrite() for the
 // same pin in the same sketch.
 //INTIALISE as Red first //ALL TO HIGH, no colour

 pinMode(buttonPin, INPUT_PULLUP);  //Input as pullup
 //attachInterrupt(digitalPinToInterrupt(buttonPin), blink, CHANGE);
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE, OUTPUT);

  //Sub 1GHz setup..
  Serial.begin(9600);
  // begin defaults to EasyLink_Phy_50kbps2gfsk
  myLink.begin();
  Serial.println(myLink.version());
   
}

/*//interurpt state change 
void blink() {
  state = !state;
}*/
/* In the loop function we will...
 */

//String d = "";
void loop() {
  //buttonState = digitalRead(buttonPin); //read ack
  //if (state) { //interrupt state
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    state_Send = true;
    buttonState = LOW;
  }

  if(state_Send == true)
  {
     //delay(10);     
     //digitalWrite(40, HIGH);  
     reset_LED();
     sendStatus();
     state_Send = false;
    // state = !state;
  } 
    //digitalWrite(40,LOW);
     /* Start processing Sub 1GHz*/
  // Wait / block for 2 second to receive a packet.
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(2000);
  // Turn the receiver on immediately
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
  
  EasyLink_Status status = myLink.receive(RxDoneCb);
  

 /* Start processing LED */
  if (bReadDone){
    bReadDone = false;
    //split substring into RGB if relevant
    // assumes that command is : AAX00010R000G255B000BB
    IdCode = strValue.substring(3,7); //0001
    redCode = strValue.substring(9,12); 
    greenCode = strValue.substring(13,16);
    blueCode = strValue.substring(17,20);
    Serial.print("strValue: ");
    Serial.println(strValue);
//    Serial.print("IdCode: ");
//    Serial.println(IdCode);
    strValue = "";

    //int redInt;
    //redInt = 255 - constrain(redCode.toInt(), 0, 255); 
    
    //if ID matches this board ID, process LED\
    //change LED colour based on command sent
    if(IdCode == BoardID){
      //analogWrite( RED, redInt );
      analogWrite( RED, redCode.toInt() );
      analogWrite( GREEN, greenCode.toInt() );
      analogWrite( BLUE, blueCode.toInt() );

//      Serial.print("red: ");
//      Serial.println(redCode);
//      Serial.print("green: ");
//      Serial.println(greenCode);
//      Serial.print("blue: ");
//      Serial.println(blueCode);
    }
  }
 
// delay( delayTime ); // wait for how long delay time is
 
}

void reset_LED()
{
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

void sendStatus() {
  char data[128];
  String txt ="AAX00020R000G255B255BB";
  txt.toCharArray(data, sizeof(data));
  memcpy(&txPacket.payload, &data, sizeof(data)); // Copy the String value into the txPacket payload
 
  txPacket.len = sizeof(data); // Set the length of the packet
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status

  if (status == EasyLink_Status_Success) {
    Serial.print("TX: ");
    Serial.println(data);
    digitalWrite(buttonPin, LOW);
    
  }
  else {
    Serial.print("TX Error code: ");
  }
}
void RxDoneCb(EasyLink_RxPacket * rxPacket, EasyLink_Status status)
{
    //after packet received, this calback function should be called
    if (status == EasyLink_Status_Success) {
      /* Toggle LED2 to indicate RX, clear LED1 */
//        PIN_setOutputValue(pinHandle, Board_PIN_LED2,!PIN_getOutputValue(Board_PIN_LED2));
//        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 0);
//        /* Copy contents of RX packet to TX packet */
//        memcpy(&txPacket.payload, rxPacket->payload, rxPacket->len);
//        /* Permit echo transmission */
//        bBlockTransmit = false;

      //memcpy(&value, &rxPacket.payload, sizeof(uint16_t));
      memcpy(&d, &rxPacket->payload, sizeof(d));
      Serial.print("Packet received with lenght ");
      Serial.print(rxPacket->len);
      Serial.print(" and value ");
      
      Serial.println(d); //value
      bReadDone = true;
      strValue = d;
  
    }
    else
    {
        /* Set LED1 and clear LED2 to indicate error */
//        PIN_setOutputValue(pinHandle, Board_PIN_LED1, 1);
//        PIN_setOutputValue(pinHandle, Board_PIN_LED2, 0);
//        /* Block echo transmission */
//        bBlockTransmit = true;
    }

//    Semaphore_post(echoDoneSem);
}
