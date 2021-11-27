
//
//EasyLink_RxPacket rxPacket;
//String strValue = "";
//
//void setupTask2() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  myLink2.begin();
//}
//
//void loopTask2() {
//  // put your main code here, to run repeatedly: 
//  // 1. keep receving from easyline,
//  // 2. if message received, then send uart message once and,
//  // 3. back to step 1
//
//
//  char f[128];
//  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
//  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(200);
//  // Turn the receiver on immediately
//  rxPacket.absTime = EasyLink_ms_To_RadioTime(0);
//  
//  EasyLink_Status status = myLink2.receive(&rxPacket);
//  
//  if (status == EasyLink_Status_Success) {
//    //memcpy(&value, &rxPacket.payload, sizeof(uint16_t));
//    memcpy(&f, &rxPacket.payload, sizeof(f));
//    //SerialCC1.print("Packet received with lenght ");
//    //SerialCC1.print(rxPacket.len);
//    //SerialCC1.print(" and value ");
//    Serial.print(f);
//    //bRecDone = true;
//    //SerialCC1.Println(f); //value
//    //bReadDone = true;
//    strValue = f;
//
//  } else {
//
//     //SerialCC1.Println("Error receiving packet with status code: ");
////    Serial.print(status);
////      Serial.print(" (");
////      Serial.print(myLink.getStatusString(status));
////      Serial.println(")");
//  }
//  
//}


EasyLink_RxPacket rxPacket;

String strValue = "";
void EasyLink_ReceiveCb_function(EasyLink_RxPacket * rxPacket, EasyLink_Status status);

void setupTask2() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myLink.begin();
}

void loopTask2() {
  // put your main code here, to run repeatedly: 
  // 1. keep receving from easyline,
  // 2. if message received, then send uart message once and,
  // 3. back to step 1


  char f[128];
//  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
//  rxPacket.rxTimeout = EasyLink_ms_To_RadioTime(200);
//  // Turn the receiver on immediately
//  rxPacket.absTime = EasyLink_ms_To_RadioTime(0); 
//  EasyLink_Status status = myLink.receive(&rxPacket);
 
  EasyLink_Status status = myLink.receive(EasyLink_ReceiveCb_function);
  
  if (status == EasyLink_Status_Success) {
    //memcpy(&value, &rxPacket.payload, sizeof(uint16_t));
    memcpy(&f, &rxPacket.payload, sizeof(f));
    //SerialCC1.print("Packet received with lenght ");
    //SerialCC1.print(rxPacket.len);
    //SerialCC1.print(" and value ");
    Serial.print(f);
    //bRecDone = true;
    //SerialCC1.Println(f); //value
    //bReadDone = true;
    strValue = f;

  } else {

     //SerialCC1.Println("Error receiving packet with status code: ");
//    Serial.print(status);
//      Serial.print(" (");
//      Serial.print(myLink.getStatusString(status));
//      Serial.println(")");
  }
  
}
void EasyLink_ReceiveCb_function(EasyLink_RxPacket * rxPacket, EasyLink_Status status){
//  char f[128];
  // rxTimeout is in Radio time and needs to be converted from miliseconds to Radio Time
  rxPacket->rxTimeout = EasyLink_ms_To_RadioTime(200);
  // Turn the receiver on immediately
  rxPacket->absTime = EasyLink_ms_To_RadioTime(0);
  
  status = myLink.receive(rxPacket);
}

  
