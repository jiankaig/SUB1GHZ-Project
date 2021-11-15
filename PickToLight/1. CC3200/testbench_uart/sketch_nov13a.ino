#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}

//String data;

void loop() {
  // put your main code here, to run repeatedly: 
  String data = "";
  if (Serial.available() > 0) {   //serial1 for sending uart
       data = Serial.readString();//serial1 for sending uart
       Serial1.println(data);  //serial1 for sending uart to leds // serial for receive
  }
   //Serial1.println(data);
}
