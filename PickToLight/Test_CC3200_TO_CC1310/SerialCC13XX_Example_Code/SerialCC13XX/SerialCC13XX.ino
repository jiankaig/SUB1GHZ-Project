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

//Serial.begin(9600);
SerialCC1.Begin(9600);

myLink.begin();

SerialCC1.Println(myLink.version());
//txPacket.dstAddr[0] = 0xaa;

//SerialCC1.Println("Hello");
//SerialCC1.Print("Starting.");

//TESTing setup
bReadDone = true;
txt = "testing...";
}


void loop() {

  char ch = SerialCC1.Read();
  if(ch!=0){ 
    SerialCC1.Print("Ch:");
    SerialCC1.Println(String(ch));
    txt += ch;
    if(ch == '\n')
      bReadDone = true;
    }
    
  if(bReadDone){
    bReadDone = false;
    SerialCC1.Print("Txt:");
    SerialCC1.Println(txt);
    sendStatus();
    txt = "";
    }

}


void sendStatus() {
  //SerialCC1.Print(txt);
  
  char d[128]; 
  txt.toCharArray(d, sizeof(d));
  memcpy(&txPacket.payload, &d, sizeof(d)); // Copy the String value into the txPacket payload
  txPacket.len = sizeof(d); // Set the length of the packet
  
  //memcpy(&txPacket.payload, &txt, txt.length()); // Copy the String value into the txPacket payload
  //txPacket.len = txt.length(); // Set the length of the packet
  
  
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately
  EasyLink_Status status = myLink.transmit(&txPacket); //check trasmit status

  switch(status){
    case EasyLink_Status_Success:
      SerialCC1.Print("TX: ");
      SerialCC1.Println(d);
      break;
    case EasyLink_Status_Tx_Error:
      SerialCC1.Print("TX Error code: ");
      SerialCC1.Print(String(status));
      SerialCC1.Print(" (");
      //SerialCC1.Print(myLink.getStatusString(status));
      // SerialCC1.println(")");
      break;
    case EasyLink_Status_Config_Error:
      break;
    case EasyLink_Status_Param_Error:
      break;
    case EasyLink_Status_Mem_Error:
      break;
    case EasyLink_Status_Cmd_Error: 
      break;
    case EasyLink_Status_Rx_Error:
      break;
    case EasyLink_Status_Rx_Timeout:
      break;
    case EasyLink_Status_Rx_Buffer_Error:
      break;
    case EasyLink_Status_Busy_Error:
      break;
    case EasyLink_Status_Aborted:
      break;    
    
    }

}
