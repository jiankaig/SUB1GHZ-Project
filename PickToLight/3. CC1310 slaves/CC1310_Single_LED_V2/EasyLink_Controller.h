#include "EasyLink.h"

class EasyLink_Controller{
public:
  EasyLink_Controller();

  void sendStatusWithFeedback(String strValue, char status_);
  void sendStatus(String strValue);
  void begin();

  EasyLink getEasyLink(){return _myLink;}
  EasyLink_TxPacket getTxPacket(){return _txPacket;}
  EasyLink_RxPacket getRxPacket(){return _rxPacket;}

  bool receive(char (&data)[32]);
  

private:
  EasyLink _myLink;
  EasyLink_TxPacket _txPacket;
  EasyLink_RxPacket _rxPacket;
  
};
