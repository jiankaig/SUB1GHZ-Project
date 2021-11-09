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

#define PIXELS 4 // number of pixels along led strip
typedef WS2801_Controller::Color Color; // alias for Color struct
WS2801_Controller strip = WS2801_Controller(PIXELS);

void setup() 
{
  strip.begin(); // LEDs should be all off at start
  delay(2000); //wait 2secs 
}

void loop() 
{
    strip.rainbow(10); // simple animation to test led strip functionality

// Color{} may be set with values 0-255 or 0x0-0xBB
//  strip.setPixelColor(Color{0x01,0x00,0x00}, 0); // set 1st led with RGB value in hex
//  strip.setPixelColor(WS2801_Controller::Color{1,1,0}, 1); // set 2nd led with RGB value in dec
  
    strip.show(); // send all data in one go thru SPI
}
