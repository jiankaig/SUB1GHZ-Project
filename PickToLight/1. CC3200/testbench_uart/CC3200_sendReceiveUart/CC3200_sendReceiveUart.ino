#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif

const int greenledPin =  GREEN_LED;      // the number of the LED pin
const int redledPin =  RED_LED;      // the number of the LED pin
int greenledState = LOW;             // ledState used to set the LED
int redledState = LOW;             // ledState used to set the LED

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  // set the digital pin as output: for Led toogle
  pinMode(greenledPin, OUTPUT);  
  pinMode(redledPin, OUTPUT);

  Serial.println("TESTBENCH START");
}

//String data;

void loop() {
  // Serial is for user to key input from serial monitor/emulator
  // Serial1 is for UART TX/RX to be CC1310 board
//  String data = "";
//  if (Serial.available() > 0) {   
////       data = Serial.readString();
//       Serial1.println(Serial.readString());  
//       toggleRedLed();
//  }
  
//  String data_uart = "";
  if (Serial1.available() > 0) {   
//       data_uart = Serial1.readString();
       Serial.println(Serial1.readString());  
       toggleGreenLed();
  }

//  if (Serial.available()) {      // If anything comes in Serial (USB),
//    Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
//    toggleRedLed();
//  }
//
//  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
//    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
//    toggleGreenLed();
//  }
  
//  delay(500);
   //Serial1.println(data);
}

void toggleGreenLed(){
  // if the LED is off turn it on and vice-versa:
    if (greenledState == LOW)
      greenledState = HIGH;
    else
      greenledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(greenledPin, greenledState);
}

void toggleRedLed(){
  // if the LED is off turn it on and vice-versa:
    if (redledState == LOW)
      redledState = HIGH;
    else
      redledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(redledPin, redledState);
}
