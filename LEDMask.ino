#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(105, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

const uint32_t white = strip.Color(127, 127, 127);
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t off = strip.Color(0, 0, 0);
uint8_t brightness = 255;

uint8_t switch2 = 0;
uint8_t switch3 = 0;
uint8_t switch4 = 0;
uint8_t switch7 = 0;
uint8_t switch8 = 0;
uint8_t switch9 = 0;

//uint16_t timer = 1;
//uint32_t now = millis();

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(13, OUTPUT);
  strip.begin();
  //strip.setBrightness(brightness);
  strip.show();           // Initialize all pixels to 'off'
  Serial.begin(9600);     // Useful for troubleshooting and debug - not needed for production version
  
}


//############################___ PULSE 1 ___################################
void pulse(uint32_t c, int time = 2000) {       // Pulses full mask as one color. Default is 1 second per cycle - delay time is in MICROSECONDS!
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    }

// TODO: determine current intensity before beginning fade. If at full, begin pulse with fadeout. If at zero, begin with fadeup.

  for (int j=0; j<256; j++) {                   // Fades from 0 to 256, with a delay 'time' between steps
    strip.setBrightness(j);
    strip.show();
    delayMicroseconds(time);
  }

delay(5);

  for (int j=256; j>0; j--) {                   // Fades from 256 back down to 0, with a delay 'time' between steps
    strip.setBrightness(j);
    strip.show();
    delayMicroseconds(time);
  }

}

//############################___ PULSE 2 ___################################
void pulse2(uint32_t c, uint16_t fadeStep) {        // Adapted from zbootili's 'rainbowpulse' function: http://forum.arduino.cc/index.php?topic=226932.0
  uint8_t i, j;
  int fadeDirection = -1;                           // change sign to fade up or down

 // for(j=brightness; j < 255; j++) {
   while (digitalRead(8) == 1) { 
    for(i=0; i <= strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
    }
       brightness = brightness + fadeDirection;      // increment the brightness value
       strip.setBrightness(brightness);              // set the strip brightness             
  
      if (brightness < 20 || brightness >= 255) {   // If the brightness value has gone past its limits...
        fadeDirection = fadeDirection * -1;         // change the direction...
        delay(60);
        brightness = brightness + fadeDirection;    // ...and start back.
      }
   
    // Serial.print("brightness is: ");
    //  Serial.println(brightness); 
    strip.show();

//  }
}
}

//############################_____ PULSE 3 _____################################
//############################___ WHY GOD WHY ___################################

void pulse3() {
for (uint8_t r1=0; r1<= 255; r1++) {
  for (uint8_t i=0; i<=strip.numPixels(); i++) {
  strip.setPixelColor(i, r1, 0, 0);
  strip.show();
  }
}

delay(600);

for (uint8_t r1=255; r1>= 0; r1--) {
  for (uint8_t i=0; i<=strip.numPixels(); i++) {
  strip.setPixelColor(i, r1, 0, 0);
  }
  strip.show();


}
}



//############################___ TWINKLE ___################################
void twinkle(uint32_t c) {
  for (uint8_t j=0; j<1; j++) {                         // Only one cycle - loop() keeps it running TODO: this makes no sense
    for (uint8_t q=0; q < 3; q++) {
      for (uint8_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);                //turn every third pixel on
      }
      strip.show();
     
      delay(300);
     
      for (uint8_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);                //turn every third pixel off
      }
    }
  }
}


//############################___ SOLID ___################################
void solid(uint32_t c, uint8_t b = 255) {           // Sets all pixels to same color, solid on. Brightness defaults to full.
  brightness = b;
  for (int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.setBrightness(brightness);
  }
    strip.show();
}

//############################___ MAIN LOOP ___################################
void loop() {

/*if (millis() - now >= 1000) {
  now = millis();
  Serial.println(timer);
  timer++;
}
*/

switch2 = digitalRead(2);
switch3 = digitalRead(3);
switch4 = digitalRead(4);
switch7 = digitalRead(7);
switch8 = digitalRead(8);
switch9 = digitalRead(9);


if (switch2 == HIGH) {
   twinkle(white);
   Serial.println("Switch 2: white twinkle");  // Useful for troubleshooting and debug - not needed for production version
  }

else if (switch3 == HIGH) {
   twinkle(red);
   Serial.println("Switch 3: red twinkle");
  }   

else if (switch4 == HIGH) {
   solid(red);
   Serial.println("Switch 4: red solid");
  }

else if (switch7 == HIGH) {
   solid(blue);
   Serial.println("Switch 7: blue solid");
  }

else if (switch8 == HIGH) {
   pulse2(red, 2);
   Serial.println("Switch 8: pulse red");
  }

else if (switch9 == HIGH) {
   solid(off);
   Serial.println("Switch 9: off");
  }

else {
pulse2(white, 2);
  }




}

  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  //twinkle(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);

//Theatre-style crawling lights.





// OTHER - CURRENTLY UNUSED - FUNCTIONS FROM THE EXAMPLE CODE:

/*


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}



//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

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
