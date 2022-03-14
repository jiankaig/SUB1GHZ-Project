/*
 CC1310_Single_LED : CC1310 Slave device application for single 5050 LED

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
//#define DEBUG

/******************Configurations***********************************************/
#define RED 13 // pin 19 is always PWM capable according to LaunchPad standard
#define GREEN 19 // may need to change this for your LaunchPad
#define BLUE 12 // may need to change this for your LaunchPad
#define buttonPin 11//PUSH1 // button pin PUSH1 //13
#define delayTime 10 // delay between color changes, 10ms by default
#define BOARDID "0003" //Change this number for the board ID

/******************Global Variables*********************************************/
String BoardID = BOARDID; // desired device identification
String txt = "";
int redVal;
int greenVal;
int blueVal;
String IdCode;
String redCode;
String greenCode;
String blueCode;
String strValue = "";
bool bReadDone = false;
int bLED_Command_Success=0;
#define LED_COMMAND_LENGTH 22
uint16_t value;
char buf[32]; //128

//For Button and debounce variables
volatile byte buttonState = LOW;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 50;
volatile byte state = HIGH;
bool state_Send = false;

/****************** Setup ***********************************************/
void setup() {
 //INTIALISE as Red first..
 //if ALL SET TO HIGH, no colour
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

/****************** Loop ***********************************************/
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
#ifdef DEBUG    
    Serial.print("strValue: ");
    Serial.print(strValue);
    Serial.print("\t");
    Serial.print("d1 check clear: ");
    Serial.println(buf);
#else
    delay(100); //slight delay, otherwise cc3200 cant seem to receive..
#endif
    memset(buf, 0, sizeof(buf)); // to clear buffer
#ifdef DEBUG    
    Serial.print("d2 check clear: ");
    Serial.println(buf);
#endif
    memcpy(&buf, &rxPacket.payload, sizeof(buf));
    memset(&rxPacket.payload, 0, sizeof(rxPacket.payload));
    Serial.print("Packet received with lenght ");
    Serial.print(rxPacket.len);
    Serial.print(" and value ");
    Serial.println((char*)rxPacket.payload); //value
    bReadDone = true;
#ifdef DEBUG
    Serial.print("strValue = buf: ");
    Serial.print(strValue);
    Serial.print(" = ");
    Serial.println(buf);
#endif
    strValue = buf;
    
  }

 /* Start processing LED */
  if (bReadDone){
    bReadDone = false;
    bLED_Command_Success = writeLEDfromStr(strValue);
    delay(100); //slight delay, otherwise cc3200 cant seem to receive..
    if(bLED_Command_Success ==1){
      bLED_Command_Success=0;
      sendStatus(strValue, '1');
    }
      
//#ifdef DEBUG
    else
      Serial.println("error led command failure");
//#endif
    strValue = "";  
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
    
    //if ID matches this board ID, process LED\
    //change LED colour based on command sent
    if(IdCode == BoardID && strValue.length() == LED_COMMAND_LENGTH){
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
    Serial.print("strValue:");
    Serial.println(strValue);
    Serial.print("TX: ");
    Serial.println((char*)txPacket.payload); // same as data
  }
  else {
    Serial.print("TX Error code: ");
  }
}

//interurpt state change 
void blink() {
  state = !state;
}
