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
#include "WS2801_Controller.h"
//#define DEBUG

/******************Configurations***********************************************/
#define RED 13 // pin 19 is always PWM capable according to LaunchPad standard
#define GREEN 19 // may need to change this for your LaunchPad
#define BLUE 12 // may need to change this for your LaunchPad
#define buttonPin 11//PUSH1 // button pin PUSH1 //13
#define delayTime 10 // delay between color changes, 10ms by default
#define BOARDID "0004" //Change this number for the board ID
#define PIXELS 3 // number of pixels along led strip
/******************Global Variables*********************************************/
String BoardID = BOARDID; // desired device identification
String strValue = "";
String strValue_copy = ""; // so not overwrited for button feedback
bool bReadDone = false;
int bLED_Command_Success=0;
#define LED_COMMAND_LENGTH 22
uint16_t value;
char buf[32]; //128
#define FIRST_STRIP_PIXEL BOARDID[3]-'0' //board id in int format

//For Button and debounce variables
volatile byte state = HIGH;
bool bFeedbackEnable = false;

#define BURST_COUNT 5
#define BURST_DELAY 50

EasyLink_RxPacket rxPacket;
EasyLink_TxPacket txPacket;
typedef WS2801_Controller::Color Color; // alias for Color struct
WS2801_Controller strip = WS2801_Controller(PIXELS, FIRST_STRIP_PIXEL);
EasyLink myLink;

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

  //init led strip controller
  strip.begin(); // LEDs should be all off at start
}

/****************** Loop ***********************************************/
void loop() {
  if(state == LOW)
  {
    Serial.println("button..");
    reset_LED();
    if(bFeedbackEnable){
      bFeedbackEnable = false;
      for(int i=0;i<BURST_COUNT;i++){
        sendStatus(strValue_copy, '2');
        delay(BURST_DELAY);
      }
      
      strValue = "";
    }
    state = !state;
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
    strip.show(); // For LED strip, send all data in one go thru SPI
    if(bLED_Command_Success ==1){
      bLED_Command_Success=0;
      sendStatus(strValue, '1');
      strValue_copy = strValue; //store strValue such that it wont be overwritten
      bFeedbackEnable = true;
    }
    else
      Serial.println("error: invalid led command");
//    strValue = "";  //if clear then button feedback wont know
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
    int intIdCode = IdCode.toInt();
    int intBoardID = BoardID.toInt();
    
    //if ID matches this board ID, process LED\
    //change LED colour based on command sent
    if(IdCode == BoardID && strValue.length() == LED_COMMAND_LENGTH){
      //analogWrite( RED, redInt );
      analogWrite( RED, 255-redCode.toInt() );
      analogWrite( GREEN, 255-greenCode.toInt() );
      analogWrite( BLUE, 255-blueCode.toInt() );
      Serial.println("set single led!");
      return 1;//success
    }
    else if(intIdCode > intBoardID && intIdCode <= intBoardID+PIXELS){
      //set led strip
      Serial.println("set led strip!");
      Serial.print("intIdCode: ");
      Serial.println(intIdCode);
      strip.setPixelColor(Color{redCode.toInt(),greenCode.toInt(), blueCode.toInt()}, intIdCode);
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
  Serial.println("blink!");
  state = !state;
}
