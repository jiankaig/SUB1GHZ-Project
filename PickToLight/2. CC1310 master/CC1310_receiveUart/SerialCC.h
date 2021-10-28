
#include "Energia.h"

class SerialCC
{
  public:
    void Begin(long baud);
    int  Print(String str);
    int  Print(char str);
    int  Println(String str);
    int Read(void);
};
