#include "EasyLink.h"

EasyLink_TxPacket txPacket;
EasyLink myLink;
#define GREEN_LED 40
#define RED_LED 39
bool led_toggle = 0;
const int threshold = 250;
int P1 = 0;
int P2 = 0;

//const int p_value = 47; //
int p_value=0;
//const int off_value = 3;

String stat;
String prevStat;
String tagName = "L9_SMT_ESD_1_Op1_Stat ";
String value;
#define calibrate_cycle 100 //take average of how many cycles..
#define p_val_offset 75 // choose value from 0 to 100

void setup() {
  Serial.begin(9600);
  myLink.begin();
  Serial.println(myLink.version());

  // Set the destination address to 0xaa
  txPacket.dstAddr[0] = 0xaa;

  //Calibration algo, Start/Reset device at "NO CONNECT" or "FAIL" state
  pinMode(GREEN_LED, OUTPUT);     
  Serial.print("calibrate p-value..");
  for(int i=0;i<calibrate_cycle;i++){
      p_value += analogRead(A0);
      p_value += analogRead(A1);
      Serial.print(i);
      Serial.print(": A0, A1: ");
      Serial.print(analogRead(A0));
      Serial.print(", ");
      Serial.println(analogRead(A1));
      led_toggle = !led_toggle;
      digitalWrite(RED_LED, led_toggle);
  }
  Serial.print("percent offset: ");
  Serial.println((100.0-p_val_offset)/100.0);
  p_value /= (40*calibrate_cycle); 
  p_value *= ((100.0-p_val_offset)/100.0);
  Serial.print("p_value calibrated to: ");
  Serial.println(p_value);
  digitalWrite(RED_LED, LOW);  
  //end of calibration p-value
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
    P2 = P2 + analogRead(A1);                   
    delay(50); //50 ms delay
  }

  P1 = P1 / 1000;
  P2 = P2 / 1000;
  Serial.print("P1: ");             //testing the analog signal from ESD
  Serial.print(P1);
  Serial.print("\tP2: ");
  Serial.println(P2);

  if (P1 == 1 && P2 >= p_value) {
    stat = "1"; // PASS
    Serial.println("PASS"); 
  }
  if (P1 >= p_value && P2 >= p_value) {
    stat = "2"; // NO CONNECT
    Serial.println("NO CONNECT"); 
  }
  if (P2 > p_value && P1 >= p_value) {
    stat = "3"; // FAIL
    Serial.println("FAIL"); 
  }
  if (P1 < p_value && P2 < p_value) {
    stat = "4"; // POWER OFF
    Serial.println("POWER OFF"); 
  }
}

void sendStatus() {
  if (prevStat != stat) {
    Serial.println("SEND STATUS!");
    value = tagName + stat;
    char d[128];                              // declare string 
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
