#include "WS2801_Controller.h"

void WS2801_Controller::begin(){
  //init SPI
  SPI.begin();  // initialize SPI hardware with default values

  //init colours
  Red = Color{0xBB,0x00,0x00};
  Green = Color{0x00,0xBB,0x00};
  Blue = Color{0x00,0x00,0xBB};
  Yellow = Color{0xBB,0xBB,0x00};
  Rainbow = Color{0xBB,0x00,0x00}; // start from red

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
    for(int i = 0; i<PIXELS; i++){
        r_value = pixelColor[i].r;
        g_value = pixelColor[i].g;
        b_value = pixelColor[i].b;
        sendRGB(r_value,g_value,b_value);
    }
}

void WS2801_Controller::setPixelColor(Color c, int index){
    pixelColor[index] = c;
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
  for(int i = 0; i<PIXELS; i++){
    setPixelColor(Rainbow, i);
  }
  
}