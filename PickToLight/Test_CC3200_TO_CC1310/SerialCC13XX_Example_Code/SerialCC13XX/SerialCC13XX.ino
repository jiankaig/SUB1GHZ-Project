#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"


SerialCC SerialCC1;

void setup() {
SerialCC1.Begin(115200);

SerialCC1.Println("Hello");
SerialCC1.Print("Starting.");
   
}


void loop() {

char ch = SerialCC1.Read();
if(ch!=0)SerialCC1.Print(String(ch));

}
