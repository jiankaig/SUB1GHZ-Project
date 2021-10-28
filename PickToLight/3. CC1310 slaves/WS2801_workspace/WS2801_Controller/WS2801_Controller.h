#include <SPI.h>
#define byte uint8_t
//#include <vector>
#define MAX_PIXELS 30

class WS2801_Controller{
    public:
    WS2801_Controller(int pixels);
    ~WS2801_Controller();
    struct Color{
      public:
        byte r;
        byte g;
        byte b;
    };
//    typedef struct color Color;

    // function prototypes
    void begin();
    void sendRGB (byte r, byte g, byte b);
    void show();
    void setPixelColor(Color c, int index); 
    void rainbow(int wait);

    private:
        int RainbowState = 0;
        int pixels_;
        Color Red, Green, Blue, Yellow, Rainbow;
        Color pixelColor[MAX_PIXELS]; //store pixel color data
//        std::vector<Color> pixelColor;

};
