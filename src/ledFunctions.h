#ifndef ledFunctions_h
#define ledFunctions_h

#include <FastLED.h>

#define NUM_LEDS 500
#define DATA_PIN 25
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define TWINKLE_SPEED 4
#define TWINKLE_DENSITY 5
#define SECONDS_PER_PALETTE  30
#define AUTO_SELECT_BACKGROUND_COLOR 0
#define COOL_LIKE_INCANDESCENT 1
#define COOLING  55
#define SPARKING 120

//extern CRGB leds[NUM_LEDS];
extern CRGBArray<NUM_LEDS> leds;
extern CRGBPalette16 gCurrentPalette;
extern CRGBPalette16 gTargetPalette;

void Fire2012WithPalette();

void drawTwinkles( CRGBSet& L);

CRGB computeOneTwinkle( uint32_t ms, uint8_t salt);

uint8_t attackDecayWave8( uint8_t i);

void coolLikeIncandescent( CRGB& c, uint8_t phase);

void chooseNextColorPalette( CRGBPalette16& pal);

void setPalette(int i);

String CRGBToHex(const CRGB& color);

int getPalette();

void colorWaves(bool increment_gHue, uint8_t brightness);

void twinklingStars(CRGB color1);

void candyCane(CRGB color1, CRGB color2);

void risingSparklesEffect();

void setAll(CRGB color);

void fadeToBlack(int ledNo, byte fadeValue);
void meteorRain(CRGB color, byte meteorSize, byte meteorTrailDecay, bool meteorRandomDecay, int SpeedDelay);

void glitter(CRGB color1, CRGB color2, CRGB color3);

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8(uint8_t &cur, const uint8_t target, uint8_t amount);

// Blend one CRGB color toward another CRGB color by a given amount.
// Blending is linear, and done in the RGB color space.
// This function modifies 'cur' in place.
CRGB fadeTowardColor(CRGB &cur, const CRGB &target, uint8_t amount);

// Fade an entire array of CRGBs toward a given background color by a given amount
// This function modifies the pixel array in place.
void fadeTowardColor(CRGB *L, uint16_t N, const CRGB &bgColor, uint8_t fadeAmount);

// Function to convert a single hexadecimal character to an integer
uint8_t hexCharToUint(char hexChar);

// Function to convert a two-character hexadecimal string to an unsigned byte (uint8_t)
uint8_t hexStringToUint8(String hexString);

// Function to convert a hex color string to a CRGB object
CRGB hexToCRGB(String hexColor);

#endif