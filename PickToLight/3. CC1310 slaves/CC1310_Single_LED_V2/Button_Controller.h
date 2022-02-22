#include <String>
#include <String.h>
#include <WString.h>
#include <Arduino.h>
#define byte uint8_t
#define buttonPin 11//PUSH1 // button pin PUSH1 //13

class Button_Controller{

public:
    Button_Controller();
    void begin();
    void blink();
    bool UpdateButtonState();
    
private:
    String txt = "";
    volatile byte state = HIGH;
    //const byte buttonPin = 11;// PUSH2; Number of pushbutton pin

    //For Button and debounce variables
    volatile byte buttonState = LOW;
    int lastButtonState = LOW;
    long lastDebounceTime = 0;
    long debounceDelay = 50;
    bool state_Send = false;
    char d[32]; //128
    
};
