// developed by abhi velaga
// github.com/avelaga/drum-led

#include <FastLED.h>

#define NUM_LEDS 150
#define LED_PIN 7
#define PIR_PIN 3

float brightness = 0;
float hue = 0;
float inc = 0;
float hueInc = .3;
float incSpeed;
int pirState = LOW;
int val = 0;
CRGB leds[NUM_LEDS];

void setup() {
  LEDS.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(255);
  pinMode(PIR_PIN, INPUT);
  incSpeed = random(4, 6) / 100.0;
  clearAll();
}

void clearAll() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB( 0, 0, 0);
    FastLED.show();
  }
}

// led code to run when motion is detected
void animate() {
  creepBootUp();
  holdWhite();
}

void readMotion() {
  val = digitalRead(PIR_PIN);
  if (val == HIGH) {
    if (pirState == LOW) { // motion detected
      animate(); // run led patterns
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) { // no motion
      clearAll(); // turns led strip off
      pirState = LOW;
    }
  }
}

// do that gradual white fill from the middle
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
  for (int x = 0; x < 60; x++) {
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

void loop() {
  readMotion();
}
