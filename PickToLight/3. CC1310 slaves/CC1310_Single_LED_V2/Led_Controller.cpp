#include "Led_Controller.h"

void Led_Controller::reset_LED()
{
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
}

int Led_Controller::writeLEDfromStr(String strValue)
{
    String IdCode, redCode, greenCode, blueCode;
    //split substring into RGB if relevant
    // assumes that command is : AAX00010R000G255B000BB
    IdCode = strValue.substring(3,7); //0001
    redCode = strValue.substring(9,12); 
    greenCode = strValue.substring(13,16);
    blueCode = strValue.substring(17,20);
//    strValue = "";
    
    //if ID matches this board ID, process LED\
    //change LED colour based on command sent
    if(IdCode == BoardID){
      //analogWrite( RED, redInt );
      analogWrite( RED, 255-redCode.toInt() );
      analogWrite( GREEN, 255-greenCode.toInt() );
      analogWrite( BLUE, 255-blueCode.toInt() );
      return 1;//success
    }
    return -1;//error BoardID mismatch
}
void Led_Controller::setBoardId(String boardid){
  BoardID = boardid;
}
