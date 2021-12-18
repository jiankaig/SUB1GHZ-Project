__pycache__ 	- Can ignore
simpleGUI   	- Not inuse for now 
simpleGUI-2 	- For running SimpleGUI
UDP_Receiver 	- UDP receiver code
UDP_Sender	- UDP sender code

#Steps
1. Right click simpleGUI-2v -> Edit with IDLE -> Edit with IDLE 3.9
2. Change ip_Addr = << >> #to your PC ip address
3. Change port = << >> #localPort to listen match the port in CC3200 WiFiUdpSendReceiveStringV2.ino line 128
4. Click Run -> Run Module or F5
5. Image Viewer will pop up 
	a. CC3200 IP Address - (User Key in) Taken from Serial monitor of CC3200 
	b. Message to send   - (User Key In)Message you wish to send 
	c. Message Received  - (System Generated) "acknowledged" will be shown when message is sent out successfully