#include "Button_Controller.h"
//#include "pcint.h"

Button_Controller::Button_Controller(){
    pinMode(buttonPin, INPUT_PULLUP);  //Input as pullup

    //this line is migrated to main file..
//    attachInterrupt(digitalPinToInterrupt(buttonPin), reinterpret_cast<void*>(Button_Controller::blink), CHANGE);
}

void Button_Controller::begin(){

}

//interurpt state change 
void Button_Controller::blink() {
  state = !state;
}

bool Button_Controller::UpdateButtonState(){
    //buttonState = digitalRead(buttonPin);  //read ack
    if(state == LOW)
    {
        //rxPacket.absTime = EasyLink_ms_To_RadioTime(1);
        
        return true;//buttonState = HIGH;
    }
    return false;
}
