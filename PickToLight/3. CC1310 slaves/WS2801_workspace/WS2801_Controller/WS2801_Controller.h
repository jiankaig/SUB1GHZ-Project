#include <SPI.h>
#define PIXELS 3 // number of pixels along led strip

class WS2801_Controller{
    public:
    struct Color{
        byte r;
        byte g;
        byte b;
    };
    //typedef struct color Color;

    // function prototypes
    void begin();
    void sendRGB (byte r, byte g, byte b);
    void show();
    void setPixelColor(Color c, int index); 
    void rainbow(int wait);

    private:
        int RainbowState = 0;
        Color Red, Green, Blue, Yellow, Rainbow;
        Color pixelColor[PIXELS] = {0}; //store pixel color data

};