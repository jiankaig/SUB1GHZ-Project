//EasyLink_TxPacket txPacket;
//
//String txt = "";
//bool bReadDone = false;
//bool bRecDone = true;
//
//void setupTask1() {
//  // put your setup code here, to run once:
//  SerialCC1.Begin(9600);
////  myLink.begin();
//  txPacket.dstAddr[0] = 0xaa;
//}
//
//void loopTask1() {
//  // put your main code here, to run repeatedly: 
//  com_CC3200toCC1310();
//  if (bReadDone) {
//        bReadDone = false;
//        txStatus(txt); // send Status via Easylink/Sub1Ghz
//        txt = "";
//        bRecDone = false;
//  }
//}
//
//
//void com_CC3200toCC1310()
//{
//  char ch = SerialCC1.Read();
//  //read only when there is something
//    if(ch != 0) {
//      txt += ch;
//      if (ch == '\n')
//        bReadDone = true;
//    }
//}
//
//void txStatus(String text) {
//  char d[128];
//  text.toCharArray(d, sizeof(d));
//  memcpy(&txPacket.payload, &d, sizeof(d)); // Copy the String value into the txPacket payload
// 
//  txPacket.len = sizeof(d); // Set the length of the packet
//  txPacket.absTime = EasyLink_ms_To_RadioTime(0); // Transmit immediately
//
//  EasyLink_Status status = myLink.transmit(&txPacket); //check transmit status
//
//  if (status == EasyLink_Status_Success) {
//    //SerialCC1.Print("TX: ");
//    SerialCC1.Println(d);
//  }
//  else {
//    //SerialCC1.Print("TX Error code: ");
//    //SerialCC1.Print(String(status));
//    //SerialCC1.Print(" (");
//    //SerialCC1.Print(myLink.getStatusString(status));
//    // SerialCC1.println(")");
//  }
//}
