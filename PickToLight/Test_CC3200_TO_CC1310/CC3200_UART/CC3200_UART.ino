//#include string.h
//#include uart.h
String incomingByte;

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
  //Serial1.print("AAX00010R000G255B000BB");
  //AAX00010R255G000B255BB
  if(Serial.available() > 0)
  {
    incomingByte = Serial.readString();
    Serial1.print(incomingByte); 
  }
}
