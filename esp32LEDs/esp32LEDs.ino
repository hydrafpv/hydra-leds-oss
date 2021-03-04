#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define LED_COUNT         130
#define DATA_PIN          23
#define INIT_BRIGHTNESS   75  // The brightness your gate will power up with, adjustable between 0 and 255. 
#define LED_TYPE          WS2812B
#define COLOR_ORDER       GRB
#define MAX_MAMPS         500

CRGB leds[LED_COUNT];
uint8_t hueCycle = 0; // rotating "base color" used by many of the patterns
CRGBPalette16 palette = PartyColors_p;  // http://fastled.io/docs/3.1/colorpalettes_8h_source.html

void setup() {
  Serial.begin(115200);
  
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MAX_MAMPS);
  FastLED.setBrightness(INIT_BRIGHTNESS);  
  Serial.println("Setup Complete");
}

void loop() {
  // do some periodic updates
  EVERY_N_MILLISECONDS( 5 ) {
    hueCycle++;  // slowly cycle the "base color" through the rainbow
  }
  
  fill_rainbow(leds, LED_COUNT, hueCycle, 7); // http://fastled.io/docs/3.1/group___colorutils.html
  FastLED.show();
}
