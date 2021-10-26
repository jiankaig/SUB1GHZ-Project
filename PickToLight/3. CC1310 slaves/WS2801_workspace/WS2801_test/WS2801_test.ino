// -*- mode:c++; -*-
/// @file WS2801_test.ino
/// 
/// @brief Example for driving several WS2801 RGB LED modules over SPI on an Arduino UNO.
///
/// @author Garth Zeglin
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

/// This sketch assumes the following electrical connections from the Arduino to
/// the first module in a chain:

/// PIN11 (MOSI)  ->  DAT
/// PIN13 (SCK)   ->  CLK
/// GND           ->  GND

// Include the SPI library.
#include <SPI.h>
#define PIXELS 1 // number of pixels along led strip
void setup() 
{
  SPI.begin();  // initialize SPI hardware
  Serial.begin(9600);
}

void loop() 
{
  static uint8_t cycle = 0;
//  delayMicroseconds(500); //Wait for 500us to go into reset  

    byte red   =  0x00;
    byte green =  0xBB;
    byte blue  =  0x00;
    
    byte red2   =  0x00;
    byte green2 =  0x00;
    byte blue2  =  0xBB;
    
    byte red3   =  0xBB;
    byte green3 =  0x00;
    byte blue3  =  0x00;
    
    SPI.transfer( red2   );
    SPI.transfer( green2 );
    SPI.transfer( blue2  );
    SPI.transfer( red3  );
    SPI.transfer( green3 );
    SPI.transfer( blue3  );
//    SPI.transfer( red   );
//    SPI.transfer( green );
//    SPI.transfer( blue  );
    SPI.transfer( 0x00 );
    SPI.transfer( 0x00 );
    SPI.transfer( 0x00 );
    delay(1000); //1 sec
  
//  delay(1);  // delay 1 millisecond to allow outputs to update
//  cycle++;   // update the overall animation

  // add a delay to control the overall frame rate
//  delay(20); 
}
