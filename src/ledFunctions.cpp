#include <ledFunctions.h>

CRGBPalette16 currentPalette = RainbowColors_p;
CRGB leds[NUM_LEDS];

void setPallette(int i) {
  switch (i) {
    case 0:
      currentPalette = RainbowColors_p;
      break;
    case 1:
      currentPalette = RainbowStripeColors_p;
      break;
    case 2:
      currentPalette = CloudColors_p;
      break;
    case 3:
      currentPalette = LavaColors_p;
      break;
    case 4:
      currentPalette = OceanColors_p;
      break;
    case 5:
      currentPalette = ForestColors_p;
      break;
    case 6:
      currentPalette = PartyColors_p;
      break;
    case 7:
      currentPalette = HeatColors_p;
      break;
  }
}

void colorWaves(bool increment_gHue, uint8_t brightness) {
  static uint8_t gHue = 0;
  if (increment_gHue) {
    gHue++;
  }
  fill_palette(leds, NUM_LEDS, gHue, 7, currentPalette, brightness, LINEARBLEND);
}

void twinklingStars(CRGB color1) {
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = random(NUM_LEDS);
  leds[pos] += color1; // cool white color
}

void candyCane(CRGB color1, CRGB color2) {
  static uint8_t stripePattern = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = (i + stripePattern) % 4 < 2 ? color1 : color2;
  }
  stripePattern++;
}

void risingSparklesEffect() {
    const uint8_t sparkleChance = 5; // Chance of new sparkle
    const uint8_t sparkleFade = 80;  // Sparkle fade out speed

    // Shift everything up one pixel per frame
    for (int i = 0; i < NUM_LEDS - 1; i++) {
        leds[i] = leds[i + 1];
    }

    // Randomly create new sparkle at the bottom
    if (random8() < sparkleChance) {
        leds[NUM_LEDS - 1] = CHSV(random8(160, 200), 255, 255); // Cool color range
    } else {
        leds[NUM_LEDS - 1] = CRGB::Black;
    }

    // Fade the LEDs
    fadeToBlackBy(leds, NUM_LEDS, sparkleFade);
}

void setAll(CRGB color) {
    for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = color;
    }
    FastLED.show();
}

void fadeToBlack(int ledNo, byte fadeValue) {
    leds[ledNo].fadeToBlackBy(fadeValue);
}

void meteorRain(CRGB color, byte meteorSize, byte meteorTrailDecay, bool meteorRandomDecay, int SpeedDelay) {
    setAll(CRGB::Black);

    for(int i = 0; i < NUM_LEDS + meteorSize; i++) {
        // Fade brightness all LEDs one step
        for(int j = 0; j < NUM_LEDS; j++) {
            if((!meteorRandomDecay) || (random(10) > 5)) {
                fadeToBlack(j, meteorTrailDecay);        
            }
        }
        
        // Draw meteor
        for(int j = 0; j < meteorSize; j++) {
            if((i - j < NUM_LEDS) && (i - j >= 0)) {
                leds[i - j] = color;
            } 
        }
   
        FastLED.show();
        delay(SpeedDelay);
    }
}

void glitter(CRGB color1, CRGB color2, CRGB color3)
{

  if (random8() < 255)
  {
    // set random LED to white
    leds[random16(NUM_LEDS)] = color1;

    // set random LED to red
    leds[random16(NUM_LEDS)] = color2;

    // set random LED to red
    leds[random16(NUM_LEDS)] = color3;
  }
}

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8(uint8_t &cur, const uint8_t target, uint8_t amount)
{
  if (cur == target)
    return;

  if (cur < target)
  {
    uint8_t delta = target - cur;
    delta = scale8_video(delta, amount);
    cur += delta;
  }
  else
  {
    uint8_t delta = cur - target;
    delta = scale8_video(delta, amount);
    cur -= delta;
  }
}

// Blend one CRGB color toward another CRGB color by a given amount.
CRGB fadeTowardColor(CRGB &cur, const CRGB &target, uint8_t amount)
{
  nblendU8TowardU8(cur.red, target.red, amount);
  nblendU8TowardU8(cur.green, target.green, amount);
  nblendU8TowardU8(cur.blue, target.blue, amount);
  return cur;
}

// Fade an entire array of CRGBs toward a given background color by a given amount
void fadeTowardColor(CRGB *L, uint16_t N, const CRGB &bgColor, uint8_t fadeAmount)
{
  for (uint16_t i = 0; i < N; i++)
  {
    fadeTowardColor(L[i], bgColor, fadeAmount);
  }
}

// Function to convert a single hexadecimal character to an integer
uint8_t hexCharToUint(char hexChar)
{
  if (hexChar >= '0' && hexChar <= '9')
  {
    return hexChar - '0';
  }
  else if (hexChar >= 'A' && hexChar <= 'F')
  {
    return 10 + (hexChar - 'A');
  }
  else if (hexChar >= 'a' && hexChar <= 'f')
  {
    return 10 + (hexChar - 'a');
  }
  else
  {
    return 0;
  }
}

// Function to convert a two-character hexadecimal string to an unsigned byte (uint8_t)
uint8_t hexStringToUint8(String hexString)
{
  return 16 * hexCharToUint(hexString.charAt(0)) + hexCharToUint(hexString.charAt(1));
}

// Function to convert a hex color string to a CRGB object
CRGB hexToCRGB(String hexColor)
{
  if (hexColor.length() < 6)
  {
    // Return black or some default color if the string is too short
    return CRGB::Black;
  }

  uint8_t r = hexStringToUint8(hexColor.substring(1, 3));
  uint8_t g = hexStringToUint8(hexColor.substring(3, 5));
  uint8_t b = hexStringToUint8(hexColor.substring(5, 7));

  return CRGB(r, g, b);
}