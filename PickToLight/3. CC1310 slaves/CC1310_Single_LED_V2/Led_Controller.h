#include "EasyLink.h"
EasyLink_RxPacket rxPacket;

// Let's use #define to rename our pins from numbers to readable variables
// This is good practice when writing code so it is less confusing to read
#define RED 13 // pin 19 is always PWM capable according to LaunchPad standard
#define GREEN 19 // may need to change this for your LaunchPad
#define BLUE 12 // may need to change this for your LaunchPad
#define buttonPin 11//PUSH1 // button pin PUSH1 //13
#define delayTime 10 // delay between color changes, 10ms by default
#define BOARDID "0002" //Change this number for the board ID

class Led_Controller{
public:
    Led_Controller(EasyLink myLink);
    ~Led_Controller();
    void begin();
private:    
    String BoardID = BOARDID; // change this according to desired device identification
    int redVal;
    int greenVal;
    int blueVal;

    //RGD LED Command syntax as follows: XXXXRXXXGXXXB AAX00010R000G255B000BB
    String IdCode;
    String redCode;
    String greenCode;
    String blueCode;
    String strValue = "";
    bool bReadDone = false;
};