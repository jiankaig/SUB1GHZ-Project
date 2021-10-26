#define CKI 10
#define SDI 9
#define STRIP_LENGTH 3
long strip_colors[STRIP_LENGTH];
void setup() {
  // put your setup code here, to run once:
  strip_colors[0] = 0xBB0000;
  strip_colors[1] = 0x00BB00;
  strip_colors[2] = 0x0000BB;
  pinMode(CKI, OUTPUT);
  pinMode(SDI, OUTPUT);
//  Serial.begin(9600);
//  Serial.print("sizeof loing: ");
//  Serial.println(sizeof(long));
}

void loop() {
  // put your main code here, to run repeatedly: 
  post_frame();
}

//Takes the current strip color array and pushes it out
void post_frame (void) {
  //Each LED requires 24 bits of data
  //MSB: R7, R6, R5..., G7, G6..., B7, B6... B0 
  //Once the 24 bits have been delivered, the IC immediately relays these bits to its neighbor
  //Pulling the clock low for 500us or more causes the IC to post the data.

  for(int LED_number = 0 ; LED_number < STRIP_LENGTH ; LED_number++) {
    long this_led_color = strip_colors[LED_number]; //24 bits of color data

    for(byte color_bit = 23 ; color_bit != 255 ; color_bit--) {
      //Feed color bit 23 first (red data MSB)
      
      digitalWrite(CKI, LOW); //Only change data when clock is low
      
      long mask = 1L << color_bit;
      //The 1'L' forces the 1 to start as a 32 bit number, otherwise it defaults to 16-bit.
      
      if(this_led_color & mask) 
        digitalWrite(SDI, HIGH);
      else
        digitalWrite(SDI, LOW);
  
      digitalWrite(CKI, HIGH); //Data is latched when clock goes high
    }
  }

  //Pull clock low to put strip into reset/post mode
  digitalWrite(CKI, LOW);
  delayMicroseconds(500); //Wait for 500us to go into reset
}
