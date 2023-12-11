#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <htmlContent.h>
#include <ledFunctions.h>
#include <gui.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

FASTLED_USING_NAMESPACE

TFT_eSPI tft = TFT_eSPI(); // TFT instance
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10]; // LVGL display buffer

// Default Colors
CRGB mainColor = CRGB::DarkGreen;
CRGB secondaryColor1 = CRGB::Red;
CRGB secondaryColor2 = CRGB::Blue;
CRGB secondaryColor3 = CRGB::WhiteSmoke;

// Defaults
int speedVariability = 50;
int speed = 10;
bool gHueState = false;
uint8_t fadeAmount = 16;
uint8_t brightness = 255;
int mode = 0;

const uint8_t lineHeight = 16; // Height of a text line, adjust as needed
const uint8_t maxLines = 15;   // Maximum number of lines that can fit on the screen
String lineBuffer[15];         // Buffer to store lines of text

const char *ssid = "ESP32";
AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  // Initialize TFT
  tft.begin();
  tft.setRotation(1); // Set if needed

  uint16_t calData[5] = {404, 3488, 289, 3409, 7};
  tft.setTouch(calData);

  // Initialize LVGL
  lv_init();

  // Initialize LVGL display buffer
  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  // Setup display driver
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320; // Set to your display's width
  disp_drv.ver_res = 240; // Set to your display's height
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  // Setup touch driver if touch is available
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  create_main_screen();
  create_color1_screen();
  create_color2_screen();
  create_color3_screen();
  create_color4_screen();
  create_fade_rate_screen();
  create_brightness_screen();
  create_mode_screen();
  create_palette_screen();
  create_speed_screen();
  create_variability_screen();
  create_inc_gHue_screen();

  // Load the main screen initially
  lv_scr_load(main_screen);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  WiFi.mode(WIFI_AP);

  Serial.println("Setting AP (Access Point)…");
  WiFi.softAP(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html); });

  server.on("/setLEDFunction", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String func;
        if (request->hasParam("function", true)) {
            func = request->getParam("function", true)->value();
            Serial.println("Mode = " + func);
            mode = func.toInt();
        } });

  server.on("/toggleHueIncrement", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String incHueToggle;
        if (request->hasParam("hueIncrement", true)) {
            incHueToggle = request->getParam("hueIncrement", true)->value();
            Serial.println("Hue incrementation toggled = " + incHueToggle);
            gHueState = (incHueToggle == "true");
        } });

  server.on("/setColorPalette", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String palette;
        if (request->hasParam("palette", true)) {
            palette = request->getParam("palette", true)->value();
            Serial.println("Palette = " + palette);
            setPallette(palette.toInt());
        } });

  server.on("/setBaseColor", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String color;
        if (request->hasParam("color", true)) {
            color = request->getParam("color", true)->value();
            Serial.println("Base Color = " + color);
            mainColor = hexToCRGB(color);
        } });

  server.on("/setSecondaryColor1", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String color;
        if (request->hasParam("color", true)) {
            color = request->getParam("color", true)->value();
            Serial.println("Secondary Color 1 = " + color);
            secondaryColor1 = hexToCRGB(color);
        } });
  server.on("/setSecondaryColor2", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String color;
        if (request->hasParam("color", true)) {
            color = request->getParam("color", true)->value();
            Serial.println("Secondary Color 2 = " + color);
            secondaryColor2 = hexToCRGB(color);
        } });

  server.on("/setSecondaryColor3", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String color;
        if (request->hasParam("color", true)) {
            color = request->getParam("color", true)->value();
            Serial.println("Secondary Color 3 = " + color);
            secondaryColor3 = hexToCRGB(color);
        } });

  server.on("/setRate", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String rate;
        if (request->hasParam("rate", true)) {
            rate = request->getParam("rate", true)->value();
            Serial.println("Update Rate = " + rate);
            speed = rate.toInt();
        } });

  server.on("/setBrightness", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String brightness;
        if (request->hasParam("brightness", true)) {
            brightness = request->getParam("brightness", true)->value();
            Serial.println("Brightness = " + brightness);
            FastLED.setBrightness(brightness.toInt());
            brightness = brightness.toInt();
        } });

  server.on("/setFadeAmount", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String _fadeAmount;
        if (request->hasParam("fade_amount", true)) {
            _fadeAmount = request->getParam("fade_amount", true)->value();
            Serial.println("Fade Back To Base Amount = " + _fadeAmount);
            fadeAmount = _fadeAmount.toInt();
        } });

  server.on("/setVariability", HTTP_POST, [](AsyncWebServerRequest *request)
            {
        String _speedVariability;
        if (request->hasParam("variability", true)) {
            _speedVariability = request->getParam("variability", true)->value();
            Serial.println("Speed Variability = " + _speedVariability);
            speedVariability = _speedVariability.toInt();
        } });

  ElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");

  Serial.println("Setup done");
}

void loop()
{
  // Handle LVGL tasks
  lv_task_handler();

  ElegantOTA.loop();

  if (mode == 0)
  {
    glitter(secondaryColor1, secondaryColor2, secondaryColor3);
    fadeTowardColor(leds, NUM_LEDS, mainColor, fadeAmount);
  }
  else if (mode == 1)
  {
    colorWaves(gHueState, brightness);
  }
  else if (mode == 2)
  {
    twinklingStars(mainColor);
  }
  else if (mode == 3)
  {
    candyCane(mainColor, secondaryColor1);
  }
  else if (mode == 4)
  {
    risingSparklesEffect();
  }
  else if (mode == 5)
  {
    // meteorRain(mainColor, 10, 64, true, 30);
  }

  // send the 'leds' array out to the actual LED strip
  FastLED.show();

  // insert a delay to keep the framerate modest
  delay(1000 / (random16(speedVariability) + speed));

  delay(5);
}