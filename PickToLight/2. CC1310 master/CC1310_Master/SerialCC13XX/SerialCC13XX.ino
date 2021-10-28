#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"
#include "EasyLink.h"

EasyLink_TxPacket txPacket;
EasyLink myLink;

SerialCC SerialCC1;
String txt = "";
bool bReadDone = false;

void setup() {
  SerialCC1.Begin(9600);

  myLink.begin();

  SerialCC1.Println(myLink.version());
  txPacket.dstAddr[0] = 0xaa;
}


void loop() {
  
  //receive UART from CC3200 and send string to CC1310master wirelessly via sub1ghz
  com_CC3200toCC1310(txt, bReadDone);
  
}


void sendStatus(String text) {
  char d[128];
  text.toCharArray(d, sizeof(d));
  memcpy(&txPacket.payload, &d, sizeof(d)); // Copy the String value into the txPacket payload
 
  txPacket.len = sizeof(d); // Set the length of the packet
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status

  if (status == EasyLink_Status_Success) {
    SerialCC1.Print("TX: ");
    SerialCC1.Println(d);
  }
  else {
    SerialCC1.Print("TX Error code: ");
    SerialCC1.Print(String(status));
    SerialCC1.Print(" (");
    //SerialCC1.Print(myLink.getStatusString(status));
    // SerialCC1.println(")");
  }
}
void com_CC3200toCC1310(String txt, bool bReadDone){
  char ch = SerialCC1.Read();
    if (ch != 0) {
      txt += ch;
      if (ch == '\n')
        bReadDone = true;
  
      if (bReadDone) {
        bReadDone = false;
        sendStatus(txt); // sendStatus via Easylink/Sub1Ghz
        txt = "";
      }
    }
}
