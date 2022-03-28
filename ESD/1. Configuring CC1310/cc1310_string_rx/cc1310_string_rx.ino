#include "EasyLink.h"

EasyLink_RxPacket rxPacket;
EasyLink myLink;

void setup() {
  Serial.begin(9600);
  // begin defaults to EasyLink_Phy_50kbps2gfsk
  myLink.begin();
  Serial.println(myLink.version());
}

char d[128];

void loop() {
  // Wait / block for 2 second to receive a packet.
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(2000);
  rxPacket.absTime = EasyLink_ms_To_RadioTime(0); // Turn the receiver on immediately

  EasyLink_Status status = myLink.receive(&rxPacket); // check receive status
  
  if (status == EasyLink_Status_Success) {
    
    memcpy(&d, &rxPacket.payload, sizeof(d));
    memset(&rxPacket.payload, 0, sizeof(rxPacket.payload));
    //Serial.print("len: ");
    //Serial.print(rxPacket.len);
    //Serial.print(", RX: ");
    Serial.print(d); //cc3200 will read from this serial..
  }
}
