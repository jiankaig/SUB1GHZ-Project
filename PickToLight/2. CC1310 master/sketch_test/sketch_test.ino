#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"
//#include "EasyLink.h"

//EasyLink_TxPacket txPacket;
//EasyLink_RxPacket rxPacket;
//EasyLink myLink;

SerialCC SerialCC1;

void setup() {
  // put your setup code here, to run once:
  SerialCC1.Begin(9600);
  //myLink.begin();

  //SerialCC1.Println(myLink.version());
  //txPacket.dstAddr[0] = 0xaa;
//  Serial.begin(9600);
}
bool once = true;
void loop() {
  // put your main code here, to run repeatedly: 
  if(once){
    once = false;
  SerialCC1.Println("YOOOO");
//  Serial.println("YOOOOOO10");
    }
}
