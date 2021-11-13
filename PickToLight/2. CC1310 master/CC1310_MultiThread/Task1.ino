EasyLink_TxPacket txPacket;

void setupTask1() {
  // put your setup code here, to run once:
  SerialCC1.Begin(9600);
  myLink.begin();
}

void loopTask1() {
  // put your main code here, to run repeatedly: 
  com_CC3200toCC1310();
  if (bReadDone) {
        bReadDone = false;
        txStatus(txt); // send Status via Easylink/Sub1Ghz
        txt = "";
        bRecDone = false;
  }
}


void com_CC3200toCC1310()
{
  char ch = SerialCC1.Read();
  //read only when there is something
    if(ch != 0) {
      txt += ch;
      if (ch == '\n')
        bReadDone = true;
    }
}
