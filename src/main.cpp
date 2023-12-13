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
#include <ArduinoJson.h>

FASTLED_USING_NAMESPACE

TFT_eSPI tft = TFT_eSPI(); // TFT instance
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10]; // LVGL display buffer

// Default Colors
CRGB color1 = CRGB::DarkGreen;
CRGB color2 = CRGB::Red;
CRGB color3 = CRGB::Blue;
CRGB color4 = CRGB::WhiteSmoke;

CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;

// setup millis timer
unsigned long timer;

// Defaults
int fpsVariability = 50;
int fps = 10;
bool inc_gHueState = false;
uint8_t fadeAmount = 16;
uint8_t brightness = 255;
int mode = 0;

const char *ssid = "ESP32";
AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // WebSocket endpoint

void sendMessageToClients(const String& message) {
    ws.textAll(message);
}
void onWsEvent(AsyncWebSocket *server, 
               AsyncWebSocketClient *client, 
               AwsEventType type, 
               void *arg, 
               uint8_t *data, 
               size_t len) {

    if (type == WS_EVT_CONNECT) {
        Serial.println("WebSocket client connected");
        Serial.println(CRGBToHex(color1));
        sendMessageToClients("{\"type\":\"Mode\",\"value\":\"" + String(mode) + "\"}");
        sendMessageToClients("{\"type\":\"Increment gHue\",\"value\":\"" + String(inc_gHueState) + "\"}");
        sendMessageToClients("{\"type\":\"Palette\",\"value\":\"" + String(getPalette()) + "\"}");
        sendMessageToClients("{\"type\":\"Color 1\",\"value\":\"" + CRGBToHex(color1) + "\"}");
        sendMessageToClients("{\"type\":\"Color 2\",\"value\":\"" + CRGBToHex(color2) + "\"}");
        sendMessageToClients("{\"type\":\"Color 3\",\"value\":\"" + CRGBToHex(color3) + "\"}");
        sendMessageToClients("{\"type\":\"Color 4\",\"value\":\"" + CRGBToHex(color4) + "\"}");
        sendMessageToClients("{\"type\":\"FPS\",\"value\":\"" + String(fps) + "\"}");
        sendMessageToClients("{\"type\":\"Fade Amount\",\"value\":\"" + String(fadeAmount) + "\"}");
        sendMessageToClients("{\"type\":\"Brightness\",\"value\":\"" + String(brightness) + "\"}");
        sendMessageToClients("{\"type\":\"FPS Variability\",\"value\":\"" + String(fpsVariability) + "\"}");
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("WebSocket client disconnected");
    } else if (type == WS_EVT_DATA) {
        // Handle incoming data
        DynamicJsonDocument doc(1024); // Adjust size according to your needs
        deserializeJson(doc, data); // Parse the JSON data

        String type = doc["type"]; // Get the type of message
        String value = doc["value"]; // Get the value

        Serial.println("Type: " + type);
        Serial.println("Value: " + value);

        // Act based on the type of message
        if (type == "Mode") {
            mode = value.toInt();
        } else if (type == "Increment gHue") {
            if (value == "true") {
                inc_gHueState = true;
            } else {
                inc_gHueState = false;
            }
        } else if (type == "Palette") {
            setPalette(value.toInt());
        } else if (type == "Color 1") {
            color1 = hexToCRGB(value);
        } else if (type == "Color 2") {
            color2 = hexToCRGB(value);
        } else if (type == "Color 3") {
            color3 = hexToCRGB(value);
        } else if (type == "Color 4") {
            color4 = hexToCRGB(value);
        } else if (type == "FPS") {
            fps = value.toInt();
        } else if (type == "Fade Amount") {
            fadeAmount = value.toInt();
        } else if (type == "Brightness") {
            brightness = value.toInt();
        } else if (type == "FPS Variability") {
            fpsVariability = 66 - value.toInt();
        }

        // Optionally, send a response back to the client
        String response = "{\"status\":\"OK\"}";
        client->text(response);
    }
}


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
  create_fps_screen();
  create_fps_variability_screen();
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

  ElegantOTA.begin(&server);

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  server.begin();
  Serial.println("HTTP server started");

  timer = millis();
  chooseNextColorPalette(gTargetPalette);
  Serial.println("Setup Done");
}

void loop()
{
  // Handle LVGL tasks
  lv_task_handler();

  ElegantOTA.loop();

  if (mode == 5) {
    EVERY_N_SECONDS( SECONDS_PER_PALETTE ) { 
    chooseNextColorPalette( gTargetPalette ); 
    }
  
    EVERY_N_MILLISECONDS( 10 ) {
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 12);
    }

    drawTwinkles(leds);
  
    FastLED.show();
  } else if (timer - millis() > 1000/ (random16(fpsVariability) + fps) ) {

    if (mode == 0)
    {
        glitter(color2, color3, color4);
        fadeTowardColor(leds, NUM_LEDS, color1, fadeAmount);
    }
    else if (mode == 1)
    {
        colorWaves(inc_gHueState, brightness);
    }
    else if (mode == 2)
    {
        twinklingStars(color1);
    }
    else if (mode == 3)
    {
        candyCane(color1, color2);
    }
    else if (mode == 4)
    {
        risingSparklesEffect();
    } else if (mode == 6) {
        
      random16_add_entropy(random());
      Fire2012WithPalette(); // run simulation frame, using palette colors
    }

    // send the 'leds' array out to the actual LED strip
    FastLED.show();
  }

  delay(20);

}