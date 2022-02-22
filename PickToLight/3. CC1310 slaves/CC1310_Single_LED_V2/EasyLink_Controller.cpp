#include "EasyLink_Controller.h"

EasyLink_Controller::EasyLink_Controller(){
  EasyLink myLink;
  EasyLink_TxPacket txPacket;
  EasyLink_RxPacket rxPacket;
  _myLink = myLink;
  _txPacket = txPacket;
  _rxPacket = rxPacket;
}
void EasyLink_Controller::begin(){
  // begin defaults to EasyLink_Phy_50kbps2gfsk
  _myLink.begin();
  Serial.println(_myLink.version());

  // Set the destination address to 0xaa
  _txPacket.dstAddr[0] = 0xaa;

  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  _rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(150);
  // Turn the receiver on immediately
  _rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
}

bool EasyLink_Controller::receive(char (&data)[32]){
  //EasyLink check receive, Serial printout, update bReadDone and store to strValue
  EasyLink_Status status = _myLink.receive(&_rxPacket);
  
  if (status == EasyLink_Status_Success) {
    memcpy(&data, &_rxPacket.payload, sizeof(data));
    Serial.print("Packet received with lenght ");
    Serial.print(_rxPacket.len);
    Serial.print(" and value ");
    
    Serial.println(data); //value
    return true;//bReadDone = true;
    //strValue = data_;

  } else {
     Serial.println("Error receiving packet with status code: ");
//    Serial.print(status);
//      Serial.print(" (");
//      Serial.print(myLink.getStatusString(status));
//      Serial.println(")");
    return false;
  }
  return false;
//END of EasyLink check receive, Serial printout, update bReadDone and store to strValue
}

void EasyLink_Controller::sendStatusWithFeedback(String strValue, char status_){
  char data[32]; //128
  String txt = strValue + status_;
  txt.toCharArray(data, sizeof(data));
  memcpy(&_txPacket.payload, &data, sizeof(data)); // Copy the String value into the txPacket payload
 
  _txPacket.len = sizeof(data); // Set the length of the packet
  _txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  EasyLink_Status status = _myLink.transmit(&_txPacket); //check trasmit status

  if (status == EasyLink_Status_Success) {
    Serial.print("TX: ");
    Serial.println(data);
    //digitalWrite(buttonPin, LOW);
  }
  else {
    Serial.print("TX Error code: ");
  }
//  delay(1000);
}
void EasyLink_Controller::sendStatus(String strValue){
  
}
