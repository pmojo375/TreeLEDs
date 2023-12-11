#ifndef ledFunctions_h
#define ledFunctions_h

#include <FastLED.h>

#define NUM_LEDS 500
#define DATA_PIN 25
#define LED_TYPE WS2811
#define COLOR_ORDER RGB

extern CRGB leds[NUM_LEDS];

void setPallette(int i);

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