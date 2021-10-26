#include <SPI.h>
#include <math.h>
//#include "ColorClass.h"

// basic example for LED Strip WS2801
// CLK <-> PIN 13
// SI  <-> PIN 11

/*****************
   CONFIGURATION
 *****************/

//SPISettings spiSettings(1000000 /* 1Mhz */, MSBFIRST, SPI_MODE0);
//#define _SERIAL_ Serial // Serial1 for Nucleo Board
#define LEDS_COUNT 32
#define SPEED 25 // 1 ... 60

/**************
   LED DRIVER
 **************/

typedef struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

//function prototypes
Color RGB(uint8_t r, uint8_t g, uint8_t b);
void leds_setAll(Color color);

Color RGB(uint8_t r, uint8_t g, uint8_t b) {
  Color result;
  result.r = r;
  result.g = g;
  result.b = b;
  return result;
}

/**
   internal state of led driver
*/
Color _leds_colors[LEDS_COUNT];

/**
   set the color for all LEDs used on next leds_commit()

   @param Color color to show
*/
void leds_setAll(Color color) {
  for (int i = 0; i < LEDS_COUNT; i++)  {
    leds_set(i, color);
  }
}

/**
   set the color for a LED used on next leds_commit()

   @param index zero-based index of the LED
   @param Color color to show
*/
void leds_set(int index, Color color) {
  if (index >= 0 && index < LEDS_COUNT) {
    Serial.print("setting LED ");
    Serial.print(index);
    Serial.print(" to (");
    Serial.print(color.r);
    Serial.print(", ");
    Serial.print(color.g);
    Serial.print(", ");
    Serial.print(color.b);
    Serial.println(")");
    _leds_colors[index] = color;
  } else {
    Serial.print("ignoring out-of-bounds index ");
    Serial.println(index);
  }
}

/**
   sends the current colors to the LEDs
*/
void leds_commit() {
  Serial.println("sending colors to LEDs");
  SPI.beginTransaction(SPISettings(1000000 /* 1Mhz */, MSBFIRST, SPI_MODE0));
  for (int i = 0; i < LEDS_COUNT; i++)  {
    Color current = _leds_colors[i];
    SPI.transfer(current.r);
    SPI.transfer(current.g);
    SPI.transfer(current.b);
  }
  SPI.endTransaction();
}

/**********
   MAIN
 **********/

void setup() {
  Serial.begin(115200);
  Serial.println("setting up...");

  leds_setAll(RGB(0, 0, 0));
  Serial.println("setup complete");
}

int mode = 0;
int mode0_currentLED = 0;
int mode1_currentStep = 0;
#define MODE1_STEP_COUNT 200
double mode1_stepSize = 2 * 3.14159265 / MODE1_STEP_COUNT;
#define MODE1_BRIGHTNESS 1.0 // 0.0 ... 1.0

void loop() {
  switch (mode) {
    case 0:
      loop_mode0();
      break;
    case 1:
      loop_mode1();
      break;
  }
}

/**
   one light dot moves over LED wire
*/
void loop_mode0() {
  leds_setAll(RGB(0, 0, 0));
  leds_set(mode0_currentLED++, RGB(0xFF, 0xFF, 0xFF));
  leds_commit();

  if (mode0_currentLED >= LEDS_COUNT) {
    mode0_currentLED = 0;
    mode = 1;
  }

  delay(3000 / SPEED);
}

/**
   all LEDS color shift
*/
void loop_mode1() {
  // see plotted RGB graphs here
  // http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiItMTI3KmNvcyg2KngqMiozLjE0LzIwMCkrMTI4IiwiY29sb3IiOiIjRjcwNTA1In0seyJ0eXBlIjowLCJlcSI6Ii0xMjcqY29zKDQqeCoyKjMuMTQvMjAwKSsxMjgiLCJjb2xvciI6IiMwMEZDMDAifSx7InR5cGUiOjAsImVxIjoiLTEyNypjb3MoeCoyKjMuMTQvMjAwKSsxMjgiLCJjb2xvciI6IiMwNTA1RkMifSx7InR5cGUiOjEwMDAsIndpbmRvdyI6WyIwIiwiMjAwIiwiMCIsIjI2MCJdfV0-
  Color color = RGB(
                  mode1_getColor(6 * mode1_currentStep),
                  mode1_getColor(4 * mode1_currentStep),
                  mode1_getColor(1 * mode1_currentStep)
                );
  leds_setAll(color);
  leds_commit();
  mode1_currentStep += 1;
  if (mode1_currentStep >= MODE1_STEP_COUNT) {
    mode1_currentStep = 0;
    mode = 0;
  }
  delay(300 / SPEED);
}

uint8_t mode1_getColor(int currentStep) {
  return (uint8_t) (MODE1_BRIGHTNESS * (-127 * cos(currentStep * mode1_stepSize) + 128));
}
