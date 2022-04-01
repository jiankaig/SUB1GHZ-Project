#include "WS2801_Controller.h"
#include <Arduino.h> // for delay() and delayMicroseconds();

WS2801_Controller::WS2801_Controller(int pixels, int fPixel){
  pixels_ = pixels;
  firstPixel = fPixel;
}

WS2801_Controller::~WS2801_Controller(){
    
}

void WS2801_Controller::begin(){
  //init SPI
  SPI.begin();  // initialize SPI hardware with default values

  //init colours
  Red = Color{0xBB,0x00,0x00};
  Green = Color{0x00,0xBB,0x00};
  Blue = Color{0x00,0x00,0xBB};
  Yellow = Color{0xBB,0xBB,0x00};
  Rainbow = Color{0xBB,0x00,0x00}; // start from red
  White = Color{0x0B,0x0B,0x0B}; 

  show();// set all leds to 0 intially
}

void WS2801_Controller::sendRGB (byte r, byte g, byte b){
    SPI.transfer(r); 
    SPI.transfer(g); 
    SPI.transfer(b); 
}

void WS2801_Controller::show(){
    delayMicroseconds(1000); //Wait for 500us to go into reset 
    byte r_value, g_value, b_value;
    for(int i = 0; i<pixels_; i++){
        r_value = pixelColor[i].r;
        g_value = pixelColor[i].g;
        b_value = pixelColor[i].b;
        sendRGB(r_value,g_value,b_value);
    }
}

void WS2801_Controller::setPixelColor(Color c, int index){
    int offset = firstPixel+1;
    Serial.print("offset: ");
    Serial.println(offset);
    pixelColor[index - offset] = c;
}

void WS2801_Controller::clear(){
  for(int i = 0; i<pixels_; i++){
    setPixelColor(Color{0,0,0}, i);
  }
} 

void WS2801_Controller::rainbow(int wait){
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
  for(int i = firstPixel; i<pixels_+firstPixel; i++){
    setPixelColor(Rainbow, i);
  }
  
}

void WS2801_Controller::simple(Color c, int wait){
  for(int i = 0; i<pixels_; i++){
    setPixelColor(c, i);
    show();
    delay(wait);
  }
  clear();
  show();
  delay(wait);
}
