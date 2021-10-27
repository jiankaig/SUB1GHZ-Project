# Hello WS2801 LED Strip

This example shows how to use a `LED Strip with WS2801` controllers on a `STM Nucleo F103RB`.
It should work with almost no adjustment on any `Arduino`–like controller.

## Preliminaries

* LED Strip WS2801 (e.g. one meter)
* [STM Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) or similar controller
* [Arduino IDE](https://www.arduino.cc/) or similar IDE

## Setup

### STM Nucleo F103RB

* connect the *5V* and *GND* PINs
* connect *GPIO PIN 13* to *CK*
* connect *GPIO PIN 11* to *SI*
* change `#define SERIAL Serial` to `#define SERIAL Serial1`
* install program

### STM32F103C8

* connect the *5V* and *GND* PINs
* connect *PA5* to *CK*
* connect *PA7* to *SI*
* install program
* (sometimes) manually reset

## Watch on YouTube

It should look like [this](https://www.youtube.com/watch?v=vOKymU7Ov0c).