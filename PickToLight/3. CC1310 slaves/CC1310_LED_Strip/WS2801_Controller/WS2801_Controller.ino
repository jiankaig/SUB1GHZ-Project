// -*- mode:c++; -*-
/// @file WS2801_Controller.ino
/// 
/// @brief Example for driving several WS2801 RGB LED modules over SPI on an CC1310 Launchpad.
///
/// @author Garth Zeglin, Jian Kai
/// @date 2021-10-27
///
/// @remarks The WS2801 LED driver has three current controlled LED outputs with
/// 8-bit precision (256 levels).  It is controlled over SPI by sending 24 bits
/// of pixel data at up to 25MHz rate.  Additional data is then relayed to the output
/// SPI pins to feed daisy-chained drivers.  Once the bus is quiescent for 500
/// microseconds, the data is applied to the outputs and the chip is ready to
/// receive more values.
///
/// So a large number of of drivers can be fed on each channel, limited only by
/// the overall refresh rate.  But the data must be fed without interruption to
/// avoid prematurely ending the cycle.
///
/// The actual color data sequence depends upon the wiring of the module; on one
/// particular strip light tested the actual sequence was blue-red-green.
///
/// Note that the relay scheme means that first three bytes output feed the
/// first module, the second three the second module, etc.  In other words, the
/// strand is not a shift register.  Extra data has no effect.

/// This sketch assumes the following electrical connections from the CC1310 to
/// the first module in a chain:

/// PIN9 (MOSI)  ->  DAT
/// PIN10 (SCK)   ->  CLK
/// GND           ->  GND

#include "WS2801_Controller.h"
#include "EasyLink.h"
EasyLink_RxPacket rxPacket;
EasyLink myLink;

#define BOARDID "04"
#define PIXELS 3 // number of pixels along led strip
typedef WS2801_Controller::Color Color; // alias for Color struct
WS2801_Controller strip = WS2801_Controller(PIXELS);

char d[128];
String BoardID = BOARDID; // change this according to desired device identification


//RGD LED Command syntax as follows: XXXXRXXXGXXXB AAX00010R000G255B000BBX
String IdCode;
String redCode;
String greenCode;
String blueCode;
String strValue = "";
String ledCode;
bool bReadDone = false;


void setup() 
{
  strip.begin(); // LEDs should be all off at start
  delay(2000); //wait 2secs 
  
  // begin defaults to EasyLink_Phy_50kbps2gfsk
  // Begin simple link sub 1ghz
  myLink.begin();
}

void loop() 
{
//    strip.rainbow(10); // simple animation to test led strip functionality
//    strip.simple(Color{0,126,0}, 1000); // another simple animation to test led strip functionality

// Color{} may be set with values 0-255 or 0x0-0xBB
//  strip.setPixelColor(Color{0,0,255}, 0); // set 1st led with RGB value
//  strip.setPixelColor(Color{0,255,0}, 1); // set 2nd led with RGB value
//  strip.setPixelColor(Color{255,0,0}, 2); // set 3nd led with RGB value
    // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(1000);
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
    writeLEDfromStr(strValue);
    //strip.setPixelColor(Color{255,0,0}, 2);
  }
//    strip.clear();
    strip.show(); // send all data in one go thru SPI
}

int writeLEDfromStr(String strValue)
{
    String IdCode, redCode, greenCode, blueCode, LedCode;
    //split substring into RGB if relevant
    // assumes that command is : AAX LL01 0R 000 G 255 B 000 BB 1
    ledCode = strValue.substring(3,5); //LL
    IdCode = strValue.substring(5,7); //01
    redCode = strValue.substring(9,12); 
    greenCode = strValue.substring(13,16);
    blueCode = strValue.substring(17,20);
    strValue = "";
    
    //if ID matches this board ID, process LED\
    //change LED colour based on command sent
    if(IdCode == BoardID){
      //analogWrite( RED, redInt );
      //analogWrite( RED, 255-redCode.toInt() );
      //analogWrite( GREEN, 255-greenCode.toInt() );
      //analogWrite( BLUE, 255-blueCode.toInt() );
      strip.setPixelColor(Color{redCode.toInt(),greenCode.toInt(), blueCode.toInt()}, ledCode.toInt());
      return 1;//success
    }
    return -1;//error BoardID mismatch
}
