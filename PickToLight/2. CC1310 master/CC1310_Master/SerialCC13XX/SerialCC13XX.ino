#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"
#include "EasyLink.h"

EasyLink_TxPacket txPacket;
EasyLink_RxPacket rxPacket;
EasyLink myLink;

SerialCC SerialCC1;
String txt = "";
String txt2 = "";
bool bReadDone = false;
String strValue = "";
String strValue2 = "";
char r[128];

void setup() {
  SerialCC1.Begin(9600);
  //Serial.begin(9600);
  myLink.begin();

  SerialCC1.Println(myLink.version());
  txPacket.dstAddr[0] = 0xaa;
}


void loop() {
  /*
  char ch = SerialCC1.Read();
  if (ch != 0) {
    
    txt += ch;
    if (ch == '\n')
      bReadDone = true;

    if (bReadDone) {
      bReadDone = false;
      sendStatus();
      txt = "";
    }*/
//    SerialCC1.Print("Loop");

  //}
  //SerialCC1.Print("Before receive");
  
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(2000);
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
  EasyLink_Status status = myLink.receive(&rxPacket); //check trasmit status

    if (status == EasyLink_Status_Success) {
    //txt2.toCharArray(r, sizeof(r));
    memcpy(&r, &rxPacket.payload, sizeof(r));
    SerialCC1.Println(r);
    }
//}

/*
void sendStatus() {
  SerialCC1.Println("sendStatus..");
  char d[128];
  txt.toCharArray(d, sizeof(d));
  memcpy(&txPacket.payload, &d, sizeof(d)); // Copy the String value into the txPacket payload
 
  txPacket.len = sizeof(d); // Set the length of the packet
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  if(myLink.transmit(&txPacket)) //added new logic
  {
    EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status
    if (status == EasyLink_Status_Success) {
    SerialCC1.Print("TX: ");
    SerialCC1.Println(d);
    }
  else {
    //SerialCC1.Print("TX Error code: ");
    //SerialCC1.Print(String(status));
    //SerialCC1.Print(" (");
    }
  }*/
}
