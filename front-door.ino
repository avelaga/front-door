#include <FastLED.h>

#define NUM_LEDS 150
#define DATA1 7
float brightness = 0;
float hue = 0;
float inc = 0;
float hueInc = .3;
float incSpeed;
int inputPin = 3;
int pirState = LOW;
int val = 0;
CRGB leds[NUM_LEDS];

void setup() {
  LEDS.addLeds<WS2812, DATA1, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(255);
  pinMode(inputPin, INPUT);
  incSpeed = random(4, 6) / 100.0;
  clearAll();
  Serial.begin(9600);
}

void fadeOut() {}

void clearAll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB( 0, 0, 0);
    FastLED.show();
  }
}

void animate() {
  creepBootUp();
  holdWhite();
  //  fadeOut();
}

void readMotion() {
  val = digitalRead(inputPin);
  if (val == HIGH) {
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      animate();
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      Serial.println("Motion ended!");
      clearAll();
      pirState = LOW;
    }
  }
}

void creepBootUp() {
  float start = NUM_LEDS / 2;
  float bright = 0;
  while (start < NUM_LEDS + 10) {
    start += .5;
    for (int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      if (i <= start) {
        bright = (start - i) * 3;
        if (bright > 255) {
          bright = 255;
        }
        leds[i] = CRGB( bright, bright, bright);
        leds[NUM_LEDS / 2 - (i - NUM_LEDS / 2)] = CRGB( bright, bright, bright);
      }
      else {
        leds[i] = CRGB( 0, 0, 0);
        leds[NUM_LEDS / 2 - (i - NUM_LEDS / 2)] = CRGB( 0, 0, 0);
      }
    }
    FastLED.show();
    delay(5);
  }
}

void holdWhite() {
  float start = 0;
  float localHue = start;
  start += .7;
  for (int x = 0; x < 60; x++) { // run for 400 frames
    for (int i = 0; i < NUM_LEDS; i++) {
      if (x == 59) {
        leds[i] = CRGB( 255, 255, 255);
      } else {
        leds[i] = CHSV(localHue, 255, 255);
        localHue += 92;
      }
    }
    FastLED.show();
    delay(50);
  }
}


void toColor() {
  float g = 255;
  float b = 255;
  float changeSpeed = .6;
  while (g > 0 ) {
    g -= changeSpeed;
    b -= changeSpeed;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB( 255, g, b);
    }
    FastLED.show();
  }
}

void loop() {
  readMotion();
  //  hue = inc;
  //  inc += incSpeed;
  //  Serial.println(hue);
  //
  //  for (int i = 0; i < NUM_LEDS; i++) {
  //    leds[i] = CHSV(hue, 255, 255);
  //    hue += .5; // incremenration of hues in the strip
  //  }
  //
  //  FastLED.show();
}
