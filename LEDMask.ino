#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(94, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const uint32_t white = strip.Color(255, 255, 255);
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t off = strip.Color(0, 0, 0);
uint8_t brightness = 255;
uint8_t dimPin = 1;
uint8_t potLevel = 0;      // doesn't need to be global?
uint8_t oldLevel = 0;
float scale = 1.0;
uint8_t dimLevel;


uint8_t switch2 = 0;
uint8_t switch3 = 0;
uint8_t switch4 = 0;
uint8_t switch7 = 0;
uint8_t switch8 = 0;
uint8_t switch9 = 0;


void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  //pinMode(13, OUTPUT);
  checkPot();
  strip.begin();
  strip.setBrightness(dimLevel);
  strip.show();                    // Initialize all pixels to 'off'
  //Serial.begin(9600);           // Useful for troubleshooting and debug - not needed for production version
  
}


uint8_t checkPot() {
  potLevel = map(analogRead(dimPin), 0, 1023, 1, 100);   // set dimmer level to number between 1 and 100
  if ((potLevel > oldLevel) || (potLevel < oldLevel)) {
    oldLevel = potLevel;                                 // store this so we can see if it's changed
    scale = potLevel * 0.01;                             // convert level into decimal
    dimLevel = 250 * scale;                              // and then dimLevel is what we use in setBrightness()
    return dimLevel;
    }
}


void pulse(uint32_t c) {
  uint8_t i, j;
  checkPot();
  float w = (map(dimLevel, 2, 250, 20, 1));
  
  for (i = 0; i <= strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }

  for (j = dimLevel; j >= 1; j--) {
    strip.setBrightness(j);
    strip.show();
    delay(w);
  }
  delay(60);
  
  for (j = 1; j <= dimLevel; j++) {
    strip.setBrightness(j);
    strip.show();
    delay(w);
}
}


/* THIS IS STUPID AND OVERCOMPLICATED AND I'M GLAD IT'S DEAD

//############################___ PULSE ___################################
void pulse2(uint32_t c, uint16_t fadeStep) {        // Adapted from zbootili's 'rainbowpulse' function: http://forum.arduino.cc/index.php?topic=226932.0
  uint8_t i, j;
  uint8_t b = dimLevel;
  int fadeDirection = -1;                          // change sign to fade up or down
   
//   while (digitalRead(8) == 1) { 
    while (1==1) {
    for(i=0; i <= strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
    }
       b = b + fadeDirection;      // increment the brightness value
       strip.setBrightness(b);              // set the strip brightness             
       checkPot();
       //int w = map(dimLevel, 2.5, 250, 50, 1);
       delay(1);
      if (b < 5 || b >= dimLevel) {       // If the brightness value has gone past its limits...
        fadeDirection = fadeDirection * -1;         // change the direction...
        delay(60);
        b = b + fadeDirection;    // ...and start back.
      }
    //checkPot();
    //brightness = dimLevel;
    strip.show();

//  }
}
}

*/




//############################___ TWINKLE ___################################
void twinkle(uint32_t c) {

  checkPot();
    for (uint8_t q=0; q < 3; q++) {
      strip.setBrightness(dimLevel);
      for (uint8_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);                      //turn every third pixel on
      }
      strip.show();
      
      delay(300);
     
      for (uint8_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);                     //turn every third pixel off
      }
    }
}



//############################___ SOLID ___################################
void solid(uint32_t c) {           // Sets all pixels to same color, solid on.
  checkPot();
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.setBrightness(dimLevel);
  }
    strip.show();
}



//############################___ MAIN LOOP ___################################
void loop() {

switch2 = digitalRead(2);
switch3 = digitalRead(3);
switch4 = digitalRead(4);
switch7 = digitalRead(7);
switch8 = digitalRead(8);
switch9 = digitalRead(9);





if (switch2 == HIGH) {
   twinkle(white);
 //  Serial.println("Switch 2: white twinkle");  // Useful for troubleshooting and debug - not needed for production version
  }

else if (switch3 == HIGH) {
   twinkle(red);
 //  Serial.println("Switch 3: red twinkle");
  }   

else if (switch4 == HIGH) {
   solid(red);
 //  Serial.println("Switch 4: red solid");
  }

else if (switch7 == HIGH) {
   solid(blue);
 //  Serial.println("Switch 7: blue solid");
  }

else if (switch8 == HIGH) {
   pulse(red);
  // Serial.println("Switch 8: pulse red");
  }

else if (switch9 == HIGH) {
   solid(off);
 //  Serial.println("Switch 9: off");
  }

else {
solid(off);
  }






}

 
/*
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
*/

