#include "Button_Controller.h"

Button_Controller::Button_Controller(EasyLink myLink, EasyLink_TxPacket txPacket){
    _myLink = myLink;
    _txPacket = txPacket;
    pinMode(buttonPin, INPUT_PULLUP);  //Input as pullup
    attachInterrupt(digitalPinToInterrupt(buttonPin), reinterpret_cast<void*>(blink), CHANGE);
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
