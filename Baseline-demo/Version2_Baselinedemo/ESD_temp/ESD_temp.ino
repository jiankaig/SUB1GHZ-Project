#include "EasyLink.h"

EasyLink_TxPacket txPacket;
EasyLink myLink;

const int threshold = 250;
int P1 = 0;
int P2 = 0;
int P3 = 0;
int P4 = 0;

const int p_value = 49;
const int off_value = 15;

String stat_1;
String stat_2;
String prevStat_1;
String prevStat_2;
String tagName_1 = "L9_SMT_ESD_1_Op1 ";
String tagName_2 = "L9_SMT_ESD_2_Op2 ";

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
  P3 = 0;
  P4 = 0;
}


void detectStatus() {
  for (byte i = 0; i < 50; i++) {
    P1 = P1 + analogRead(A0);
    P2 = P2 + analogRead(A1);
    P3 = P3 + analogRead(A2);
    P4 = P4 + analogRead(A3);
    delay(50);
  }

  P1 = P1 / 1000;
  P2 = P2 / 1000;
  P3 = P3 / 1000;
  P4 = P4 / 1000;
  
  Serial.print("P1: ");
  Serial.print(P1);
  Serial.print(" P2: ");
  Serial.println(P2);
  Serial.print("P3: ");
  Serial.print(P3);
  Serial.print(" P4: ");
  Serial.println(P4);
  Serial.println();

  if (P1 == 1 && P2 == p_value) {
    stat_1 = "1"; // PASS
  }
  if (P1 == p_value && P2 == 1) {
    stat_1 = "2"; // NO CONNECT
  }
  if (P2 > 20 && P1 == p_value) {
    stat_1 = "3"; // FAIL
  }
  if (P1 < off_value && P2 < off_value) {
    stat_1 = "4"; // POWER OFF
  }

  if (P3 == 1 && P4 == p_value) {
    stat_2 = "1"; // PASS
  }
  if (P3 == p_value && P4 == 1) {
    stat_2 = "2"; // NO CONNECT
  }
  if (P4 > 20 && P3 == p_value) {
    stat_2 = "3"; // FAIL
  }
  if (P3 < off_value && P4 < off_value) {
    stat_2 = "4"; // POWER OFF
  }
}

void sendStatus() {
  if (prevStat_1 != stat_1 || prevStat_2 != stat_2) {
    value = tagName_1 + stat_1 + tagName_2 + stat_2;
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
  prevStat_1 = stat_1;
  prevStat_2 = stat_2;
}
