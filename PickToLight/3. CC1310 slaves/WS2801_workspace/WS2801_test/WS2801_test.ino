// -*- mode:c++; -*-
/// @file WS2801_test.ino
/// 
/// @brief Example for driving several WS2801 RGB LED modules over SPI on an CC1310 Launchpad.
///
/// @author Garth Zeglin, Jian Kai
/// @date 2014-09-13
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

// Include the SPI library.
#include <SPI.h>
#define PIXELS 4 // number of pixels along led strip
struct Color
{
  public:
    byte r;
    byte g;
    byte b;
}Red, Green, Blue, Yellow, Rainbow;
//typedef struct color Color;
int RainbowState = 0;
void setPixelColor(Color c, int index); // function prototype
Color pixelColor[PIXELS] = {0}; //store pixel color data

void setup() 
{
  //init SPI
  SPI.begin();  // initialize SPI hardware
//  SPI.setClockDivider(SPI_CLOCK_DIV2);  // defined for each clock speed
//  SPI.setBitOrder(MSBFIRST);
//  SPI.setDataMode(SPI_MODE1);   // MOSI normally low.

  Serial.begin(9600); // for debugging

  //init colours
  Red = Color{0xBB,0x00,0x00};
  Green = Color{0x00,0xBB,0x00};
  Blue = Color{0x00,0x00,0xBB};
  Yellow = Color{0xBB,0xBB,0x00};
  Rainbow = Color{0xBB,0x00,0x00}; // start from red
  show();// set all leds to 0 intially
}

void loop() 
{
  show();
  rainbow(10);
//  setPixelColor(Color{0x01,0x00,0x00}, 0);
//  setPixelColor(Color{0,1,0}, 1);
//  setPixelColor(Blue, 2);
}

// Sends three bytes to the LED strip by SPI.
void sendRGB (byte r, byte g, byte b) {
    SPI.transfer(r); 
    SPI.transfer(g); 
    SPI.transfer(b); 
} // end of sendRGB

// Wait long enough without sending any bits and update all pixels
void show(){
  delayMicroseconds(1000); //Wait for 500us to go into reset 
  byte r_value, g_value, b_value;
  for(int i = 0; i<PIXELS; i++){
    r_value = pixelColor[i].r;
    g_value = pixelColor[i].g;
    b_value = pixelColor[i].b;
    sendRGB(r_value,g_value,b_value);
    }
  
} // end of show

// set Pixel Color by index, assuming indexing starts from 0
void setPixelColor(Color c, int index){
  pixelColor[index] = c;
}
void rainbow(int wait){
  delay(wait);
  switch(RainbowState){
    case 0: Rainbow.r--;
            Rainbow.g++;
            if(Rainbow.r == 0)
              RainbowState++;
            break;
    case 1: Rainbow.g--;
            Rainbow.b++;
            if(Rainbow.g == 0)
              RainbowState++;
            break;
    case 2: Rainbow.b--;
            Rainbow.r++;
            if(Rainbow.b == 0)
              RainbowState = 0;
            break;
  }

  //set all pixels to same color
  for(int i = 0; i<PIXELS; i++){
    setPixelColor(Rainbow, i);
  }
  
}
