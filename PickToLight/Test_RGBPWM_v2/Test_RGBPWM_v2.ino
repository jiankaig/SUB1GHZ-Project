/*
 Example 01: Fade RGB LED (PWM)
 Sidekick Basic Kit for TI LaunchPad

 Now we are going to use the special tricolor LED. RGB stands for
 Red, Green, and Blue which are primary colors that can make any
 color we want. This LED can help us make different colors that
 can mean different things.

 We are going to use Pulse Width Modulation to let the LED fade.
 Certain pins on the LaunchPad are PWM capable. In Energia, we call
 this analogWrite() capable. We will want to use those to connect
 to our LED. If you are not sure, check the Energia pin maps on
 the website for your LaunchPad.
 
 This example code is in the public domain.
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
String BoardID = "0001";  //Change this variable to control another cc1310 board (slave)
int PWM_RESOLUTION = 255; // this variable will hold our resolution.
const int buttonPin = 11;// PUSH2;    
int buttonState = LOW;  
uint16_t value;

/* This is our setup function. We want to set our LED pins as OUTPUT.
 * We can also set them to HIGH at the beginning.
 */
void setup() {
 // We don't have to use pinMode() when using analogWrite() but it doesn't
 // hurt to use it, especially if we want to call digitalWrite() for the
 // same pin in the same sketch.
 //INTIALISE as Red first //ALL TO HIGH, no colour

 pinMode(buttonPin, INPUT);  //Input as pullup
 
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
//    memcpy(&value, &rxPacket.payload, sizeof(uint16_t));
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
  buttonState = digitalRead(buttonPin); //read ack
  if(buttonState == HIGH) //if button is pressed (ack)
  {
    digitalWrite(RED,  HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    Serial.println("User Acknowledge");
    // Send AAX00010R255G255B255BB
    //sendStatus();
    buttonState = LOW;          
  }
  
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
