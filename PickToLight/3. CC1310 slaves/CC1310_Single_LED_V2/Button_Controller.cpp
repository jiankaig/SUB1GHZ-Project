#include "Button_Controller.h"

Button_Controller::Button_Controller(EasyLink myLink){
    _myLink = myLink;
    pinMode(buttonPin, INPUT_PULLUP);  //Input as pullup
    attachInterrupt(digitalPinToInterrupt(buttonPin), reinterpret_cast<void*>(blink), CHANGE);
}

void Button_Controller::sendStatus(String strValue, char status_) {
  char data[32]; //128
  String txt = strValue + status_;
  txt.toCharArray(data, sizeof(data));
  memcpy(&txPacket.payload, &data, sizeof(data)); // Copy the String value into the txPacket payload
 
  txPacket.len = sizeof(data); // Set the length of the packet
  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately

  EasyLink_Status status = _myLink.transmit(&txPacket); //check trasmit status

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

//interurpt state change 
void Button_Controller::blink() {
  state = !state;
}

void Button_Controller::UpdateButtonState(){
    //buttonState = digitalRead(buttonPin);  //read ack
    if(state == LOW)
    {
        //rxPacket.absTime = EasyLink_ms_To_RadioTime(1);
        reset_LED();
        sendStatus(strValue, '2');
        buttonState = HIGH;
    }
}
