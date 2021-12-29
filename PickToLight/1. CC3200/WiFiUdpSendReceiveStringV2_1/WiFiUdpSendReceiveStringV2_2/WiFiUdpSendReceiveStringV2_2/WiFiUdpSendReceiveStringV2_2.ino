
/*
  WiFi UDP Send and Receive String

 This sketch wait an UDP packet on localPort using the CC3200 launchpad
 When a packet is received an Acknowledge packet is sent to the client on port remotePort


 created 30 December 2012
 by dlf (Metodo2 srl)
 
 modified 1 July 2014
 by Noah Luskey

 Version:
  2.0:  NIL
  2.1:  added simpleGuiPort parameter for sending feedback message to client 
        added return string cropping(line 133)
 */

#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>
//#define SHOW_UART1_RX

// your network name also called SSID
char ssid[] = "Sub1Ghz";
char password[] = "Seems12345";

unsigned int localPort = 2390;      // local port to listen on
unsigned int simpleGuiPort = 4550;      // server port to send back to

char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
//String data = "";
bool bReadUart = false;
bool packetreceiving = false;
WiFiUDP Udp;
String ret;
char  ret_char_array[32] = "";       // a string to send back

void setup() {
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(115200);

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
 
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
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
    Serial1.println(packetBuffer);
    
    lastRemoteIP = Udp.remoteIP();
    lastRemotePort = Udp.remotePort();
    
    // send a reply, to the IP address and port that sent us the packet we received
    Serial.println("Sending back to: ");  //Added on 18Dec 
    Serial.println(Udp.remoteIP());
    Serial.println(Udp.remotePort());
    Udp.beginPacket(Udp.remoteIP(), simpleGuiPort ); //Udp.remoteIP(), Udp.remotePort()
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  else{
    //If not getting any UDP pacwwkets from application
    //Receive Mode - Ask EasyLink API to check radio
    Serial1.println("AT+RX");
    delay(1000); 
    ret = Serial1.readString();
    
      //trim unnecessary text
//    size_t strtPos = 10;
//    size_t endPos = ret.indexOf("OK");    
//    ret = ret.substring(strtPos, endPos); //trim "AT+RX RX: " and "OK"
    
    //if ret not timeout, pass ret thru Udp...?
    if(ret.indexOf("Timeout") == -1){
      Serial.println(ret); //printout for debug on serial monitor
      if(lastRemoteIP || lastRemotePort)//is valid
      {
        Serial.println("no timeout, send back to last remote ip, port");
        Serial.print("lastRemoteIP: ");
        Serial.println(lastRemoteIP);
        strcpy(ret_char_array, ret.c_str()); //copy to char array for udp write
        Udp.beginPacket(lastRemoteIP, simpleGuiPort); //lastRemoteIP, lastRemotePort
        Udp.write(ret_char_array); 
        Udp.endPacket();

        //resend via lastRemotePort
        Udp.beginPacket(lastRemoteIP, lastRemotePort); //lastRemoteIP, lastRemotePort
        Udp.write(ret_char_array); 
        Udp.endPacket();
      }
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
  Serial.println("INITIALISING EasyLink AT API..");
  Serial1.println("AT+I 0001<CR>");
  Serial1.println("ATPRO=4000000<CR>");
}
