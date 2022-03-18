
/*
  WiFi UDP Send and Receive String

 This sketch wait an UDP packet on localPort using the CC3200 launchpad
 When a packet is received an Acknowledge packet is sent to the client on port remotePort
 Followed by sending AT command to a Easylink API(rfEasyLinkNp) via UART
 Waits to Respond from Easylink API via UART
 Then back to checking for UDP packets

 created 25 Feburary 2022
 
 modified from WifiUdpSendReceiveString Example
 by Giam Jian Kai

 Version:
  2.0:  NIL
  2.1:  added simpleGuiPort parameter for sending feedback message to client 
        added return string cropping(line 133)
  2.2: added preprocessor: DEBUG_MODE_SIM_GUI and DEBUG_MODE_PACKET_SENDER(default)
       moved/corrected string cropping/trimming into condition
  2.3: - corrected return string trimming(remove entire "AT+TX..." from 
         return string)
       - added "AT+TX " prefix to the transmit command, i.e. client 
         dont need to send message with "AT+TX"
  2.4: - implemented state machine to replace if else situation of transmitting/receiving
       - added new condition for led command length
       - added new condition to stop listening to easylink after 5 timeouts
       - minor changes to debugging msg via serial print
       - serial1 set Timeout(deafult is 1sec)
 */

#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>

/////////////////////////PREPROCESSOR DEFINATIONS//////////////////////////////
//#define DEBUG_
//#define SHOW_UART1_RX
//#define DEBUG_MODE_SIM_GUI //if using simple gui to debug
///////////////////END OF PREPROCESSOR DEFINATIONS/////////////////////////////

#ifndef DEBUG_MODE_SIM_GUI
#define DEBUG_MODE_PACKET_SENDER
#endif

// your network name also called SSID
char ssid[] = "Sub1Ghz";
char password[] = "Seems12345";

unsigned int localPort = 55056;//2390;      // local port to listen on //Packet Sender
unsigned int simpleGuiPort = 55007; //4550;      // server port to send back to

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
//String data = "";
bool bReadUart = false;
bool packetreceiving = false;
WiFiUDP Udp;
String ret;
char  ret_char_array[32] = "";       // a string to send back
bool bButtonFB; //boolean to manage if button feedback has been received

//State machine definition for switch case
#define STATE_IDLE 0 //unused
#define STATE_CHECK_UDP 1
#define STATE_CHECK_EASYLINK 2
#define STATE_FEEDBACK_UDP 3 // when not timeout
int programState = STATE_CHECK_UDP;
int STATE_CHECK_EASYLINK_count = 0;
#define LED_COMMAND_LENGTH 22
#define TIMEOUT_MS 215//200 //1000 //for serial1 timeout and delay after at+rx
#define STR_TIMEOUT_25MHZ "800000" //"4000000" //for timeout of ar+rx
#define STATE_CHECK_EASYLINK_REPEAT 3

void setup() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial1.setTimeout(TIMEOUT_MS);
  
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  printWifiStatus();

  Serial.println("\nWaiting for a connection from a client...");
  Udp.begin(localPort);
  Serial.println("connected.");
  
  AT_init(); //sends AT commands to Easylink API for initialising
}

int lastRemoteIP;
int lastRemotePort;
void loop() {

#ifdef SHOW_UART1_RX
  if(Serial1.available() > 0) 
  {
    Serial.print("Received: ");
    ret = Serial1.readString(); 
    Serial.println(ret); //printout for debug on serial monitor

  }
#endif
 int packetSize;
 
  switch(programState){
    case STATE_CHECK_UDP:
    {
        // if there's data available, read a packet
        packetSize = Udp.parsePacket();
//        #ifdef DEBUG_
//            Serial.print("STATE_CHECK_UDP, packetSize:");
//            Serial.print(packetSize);
//            Serial.print("  bButtonFB: ");
//            Serial.println(bButtonFB);
//        #endif
        if (packetSize)
        {
          Serial.print("\n");
          Serial.print("Received packet of size ");
          Serial.println(packetSize);
          Serial.print("From ");
          IPAddress remoteIp = Udp.remoteIP();
          Serial.print(remoteIp);
          Serial.print(", port ");
          Serial.println(Udp.remotePort());
      
          // read the packet into packetBufffer
          int len = Udp.read(packetBuffer, 255);
          if (len > 0) packetBuffer[len] = 0;
          Serial.println("Contents:");
          Serial.println(packetBuffer);
          
          char processed_pktBuf[30];
          const char *TX_prefix = "AT+TX ";
          const char *TX_msg = packetBuffer;
          strcpy(processed_pktBuf,TX_prefix);
          strcat(processed_pktBuf,TX_msg);
          
          Serial1.println(processed_pktBuf);
          
          lastRemoteIP = Udp.remoteIP();
          lastRemotePort = Udp.remotePort();
          
          // send a reply, to the IP address and port that sent us the packet we received
          Serial.println("last remote ip & port: ");  //Added on 18Dec 
          Serial.println(Udp.remoteIP());
          Serial.println(Udp.remotePort());
          
    #ifdef DEBUG_MODE_SIM_GUI
          Serial.println("DEBUG_MODE_SIM_GUI");
    #ifdef DEBUG_
          Udp.beginPacket(Udp.remoteIP(), simpleGuiPort ); //Udp.remoteIP(), Udp.remotePort()
          Udp.write(ReplyBuffer);
          Udp.endPacket();
    #endif
    #endif
    
    #ifdef DEBUG_MODE_PACKET_SENDER
          Serial.println("DEBUG_MODE_PACKET_SENDER");
          Serial.print("ip: ");
          Serial.println(lastRemoteIP);
          Serial.print("port: ");
          Serial.println(lastRemotePort);
          //resend via lastRemotePort
          Udp.beginPacket(lastRemoteIP, lastRemotePort); //lastRemoteIP, lastRemotePort
          Udp.write(ReplyBuffer); 
          Udp.endPacket();
    #endif
      }
      if(packetSize == LED_COMMAND_LENGTH || bButtonFB == true){
          if(packetSize == LED_COMMAND_LENGTH ){
            // Enable Half-Duplex communication mode..
            Serial.println("bButtonFB = true");
            bButtonFB = true; // for checking for button feedback
          }
        
          programState = STATE_CHECK_EASYLINK;
      }
//      else{
//        Serial.print("invalid led command, length is ");
//        Serial.print(packetSize);
//      }
        
       break;
     }
     case STATE_CHECK_EASYLINK:
     {
      //If not getting any UDP pacwwkets from application///////////////////////////////////////////
      //Receive Mode - Ask EasyLink API to check radio//////////////////////////////////////////////
  #ifdef DEBUG_
      Serial.println("STATE_CHECK_EASYLINK");
  #endif
      // base case..
      if(STATE_CHECK_EASYLINK_count > STATE_CHECK_EASYLINK_REPEAT ){
        Serial.println("Exit receive mode, no feedback received...go back to listening for udp..");
        STATE_CHECK_EASYLINK_count = 0;
        programState = STATE_CHECK_UDP;
        break;
      }
      
      Serial1.println("AT+RX");
      delay(TIMEOUT_MS); 
      ret = Serial1.readString();
      #ifdef DEBUG_
      Serial.print("STATE_CHECK_EASYLINK ret: ");
      Serial.print(ret);
      Serial.println("END of ret");
      #endif

      //if ret not timeout, pass ret thru Udp...?
      if(ret.charAt(27) != '5') //ret.indexOf("Timeout") == -1 is O(N)
      {
        //if return is button feedback, change to simplex mode
        if(ret.indexOf("BB2") > 0 ){
          Serial.println("bButtonFB = false");
          bButtonFB = false;
          programState = STATE_FEEDBACK_UDP;
        }
        else if(ret.indexOf("BB1") > 0 ){
          STATE_CHECK_EASYLINK_count = 0;
          programState = STATE_FEEDBACK_UDP;
        } 
      }
      else
        STATE_CHECK_EASYLINK_count += 1;
      break;
     }
     
     case STATE_FEEDBACK_UDP:
     {
  #ifdef DEBUG_
        Serial.println("STATE_FEEDBACK_UDP");
        Serial.print("FULL RETURN: ");
        Serial.print(ret); //printout for debug on serial monitor
        Serial.println("END of FULL RETURN: ");
  #endif
  
        //trim unesscessary text in return string
        trimReturnString(ret);
        
        if(lastRemoteIP || lastRemotePort)//is valid
        {
  #ifdef DEBUG_
          Serial.println("no timeout, send back to last remote ip, port");
          Serial.print("lastRemoteIP: ");
          Serial.println(lastRemoteIP);
          Serial.print("lastRemotePort: ");
          Serial.println(lastRemotePort);
          Serial.print("ret: ");
          Serial.println(ret);
  #endif
  //        memset(ret_char_array, 0, sizeof(ret_char_array)); // clear/empty ret_char_array
          sendUdpToClient(ret);
          
          Udp.flush(); //not really flushing/doing much
          programState = STATE_CHECK_UDP;
        }
        break;
     }
   } 
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void AT_init(){
  Serial.println("INITIALISE EasyLink AT API");
  Serial1.println("AT+I 0001<CR>");
  Serial1.print("ATPRO=");
  Serial1.print(STR_TIMEOUT_25MHZ); //"4000000"
  Serial1.println("<CR>");
//  Serial1.println("ATPRO=4000000<CR>");

  // to flush the returns
  Serial1.println("AT+RX"); 
  Serial1.readString();
}

void sendUdpToClient(String ret){
  strcpy(ret_char_array, ret.c_str()); //copy to char array for udp write

#ifdef DEBUG_MODE_SIM_GUI
        Serial.print("RET_MODE_SIM_GUI: ");
        Serial.println(ret_char_array);
        Udp.beginPacket(Udp.remoteIP(), simpleGuiPort); //lastRemoteIP, lastRemotePort
        Udp.write(ret_char_array); 
        Udp.endPacket();
#endif
#ifdef DEBUG_MODE_PACKET_SENDER
        Serial.println("RET_MODE_PACKET_SENDER");
#ifdef DEBUG_
        Serial.print("ip: ");
        Serial.println(lastRemoteIP);
        Serial.print("port: ");
        Serial.println(lastRemotePort);
#endif
        //resend via lastRemotePort
        Udp.beginPacket(lastRemoteIP, lastRemotePort); //lastRemoteIP, lastRemotePort
        Udp.write(ret_char_array); 
        Udp.endPacket();
#endif
}

void trimReturnString(String& ret){
      //trim unnecessary text
      size_t strtPos = ret.indexOf("RX: ")+4;//trim "RX: " and entire "AT+TX..."(+4 is to offset)
      size_t endPos = ret.indexOf("BB", strtPos)+3; //to trim away " OK"(+3 is to offset)
#ifdef DEBUG_
      Serial.print("strtPos, endPos: ");
      Serial.print(strtPos);
      Serial.print(",");
      Serial.println(endPos); //printout for debug on serial monitor
#endif
      ret = ret.substring(strtPos, endPos); //trim "AT+RX RX: " and "OK"
}
