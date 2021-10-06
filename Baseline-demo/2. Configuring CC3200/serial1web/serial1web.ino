#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

char ssid[] = "Pixel_9059"; // your network name also called SSID
char password[] = "Watermelon123"; // your network password
int keyIndex = 0; // your network key Index number (needed only for WEP)

WiFiServer server(80);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid); // print the network name (SSID);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("."); // print dots while we wait to connect
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    Serial.print("."); // print dots while we wait for an ip addresss
    delay(300);
  }

  printWifiStatus(); // you're connected now, so print out the status

  Serial.println("Starting webserver on port 80");
  server.begin();   // start the web server on port 80
  Serial.println("Webserver started!");
}

String data;

void loop() {
  // put your main code here, to run repeatedly:
  //data = 0;
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 0.5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          if (Serial1.available() > 0) {
            data = Serial1.readString();
          }

          Serial.print(data);
          if (data != 0)
            client.println(data);

          client.println("<br />");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(5000);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
