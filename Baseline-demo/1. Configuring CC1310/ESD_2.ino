#include "EasyLink.h"

EasyLink_TxPacket txPacket;
EasyLink myLink;

const int threshold = 250;
int P1 = 0;
int P2 = 0;

<<<<<<< Updated upstream:Baseline-demo/1. Configuring CC1310/ESD_2.ino
const int p_value = 51;
const int off_value = 3;
=======
const int p_value = 25;//47;
const int off_value = 5;
>>>>>>> Stashed changes:ESD/1. Configuring CC1310/ESD_2/ESD_2.ino

String stat;
String prevStat;
String tagName = "L9_SMT_ESD_1_Op1_Stat ";
String value;

void setup() {
  Serial.begin(9600);
  myLink.begin();
  Serial.println(myLink.version());

  // Set the destination address to 0xaa
  txPacket.dstAddr[0] = 0xaa;
}

void loop() {
  detectStatus();
  sendStatus();
  P1 = 0;
  P2 = 0;
}


void detectStatus() {
  for (byte i = 0; i < 50; i++) {
    P1 = P1 + analogRead(A0);
<<<<<<< Updated upstream:Baseline-demo/1. Configuring CC1310/ESD_2.ino
    P2 = P2 + analogRead(A1);
    delay(50);
=======
    P2 = P2 + analogRead(A1);                   
    delay(40); //50 ms delay
>>>>>>> Stashed changes:ESD/1. Configuring CC1310/ESD_2/ESD_2.ino
  }

  P1 = P1 / 1000;
  P2 = P2 / 1000;
  Serial.print("P1: ");
  Serial.println(P1);
  Serial.print("P2: ");
  Serial.println(P2);
  Serial.println();

<<<<<<< Updated upstream:Baseline-demo/1. Configuring CC1310/ESD_2.ino
  if (P1 == 1 && P2 == p_value) {
    stat = "1"; // PASS
  }
  if (P1 == p_value && P2 == 1) {
    stat = "2"; // NO CONNECT
  }
  if (P2 > 20 && P1 == p_value) {
    stat = "3"; // FAIL
=======
  if (P1 == 1 && P2 >= p_value) {
    stat = "1"; // PASS 1 ; You are safe
  }
//  if (P1 >= p_value && P2 == 1) {
//    stat = "2"; // NO CONNECT 2 Please connect the ESD cable
//  }
  if (P1==51 && P2==51){ //(P2 > 20 && P1 >= p_value) {
    stat = "3"; // FAIL 2 Please connect and wear the ESD band
>>>>>>> Stashed changes:ESD/1. Configuring CC1310/ESD_2/ESD_2.ino
  }
  if (P1 < off_value && P2 < off_value) {
    stat = "Power Off"; // POWER OFF 3
  }
}

void sendStatus() {
  if (prevStat != stat) {
    value = tagName + stat;
    char d[128];
    value.toCharArray(d, sizeof(d));
    memcpy(&txPacket.payload, &d, sizeof(d)); // Copy the String value into the txPacket payload

    txPacket.len = sizeof(d); // Set the length of the packet
    txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

    EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status

    if (status == EasyLink_Status_Success) {
      Serial.print("TX: ");
      Serial.println(d);
    } else {
      Serial.print("TX Error code: ");
      Serial.print(status);
      Serial.print(" (");
      Serial.print(myLink.getStatusString(status));
      Serial.println(")");
    }
  }
  prevStat = stat;
}
