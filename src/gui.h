// gui.h
#ifndef GUI_h
#define GUI_h

#include <lvgl.h>
#include <FastLED.h>
#include <TFT_eSPI.h>
#include <Arduino.h>

// Declare screens
extern lv_obj_t *main_screen;
extern lv_obj_t *color1_screen;
extern lv_obj_t *color2_screen;
extern lv_obj_t *color3_screen;
extern lv_obj_t *color4_screen;
extern lv_obj_t *inc_gHue_screen;
extern lv_obj_t *brightness_screen;
extern lv_obj_t *fps_screen;
extern lv_obj_t *fps_variability_screen;
extern lv_obj_t *palette_screen;
extern lv_obj_t *mode_screen;
extern lv_obj_t *fade_rate_screen;

extern CRGB color1;
extern CRGB color2;
extern CRGB color3;
extern CRGB color4;

extern int fpsVariability;
extern int fps;
extern bool inc_gHueState;
extern uint8_t fadeAmount;
extern uint8_t brightness;
extern int mode;

extern TFT_eSPI tft;

void btn_event_handler_to_color1_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_color2_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_color3_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_color4_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_brightness_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_fps_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_fps_variability_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_fade_rate_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_mode_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_palette_screen(lv_obj_t *btn, lv_event_t event);

void btn_event_handler_to_inc_gHue_screen(lv_obj_t *btn, lv_event_t event);

void back_btn_event_handler(lv_obj_t *btn, lv_event_t event);

void create_main_screen();

void create_color1_screen();

void create_color2_screen();

void create_color3_screen();

void create_color4_screen();

void create_brightness_screen();

void create_inc_gHue_screen();

void create_fps_screen();

void create_fps_variability_screen();

void create_palette_screen();

void create_mode_screen();

void create_fade_rate_screen();

void color1_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event);

void color2_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event);

void color3_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event);

void color4_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event);

void fps_variability_event_handler(lv_obj_t* slider, lv_event_t event);

void fps_event_handler(lv_obj_t* slider, lv_event_t event);

void fade_rate_event_handler(lv_obj_t* slider, lv_event_t event);

void brightness_event_handler(lv_obj_t* slider, lv_event_t event);

void inc_gHue_event_handler(lv_obj_t* sw, lv_event_t event);

void mode_event_handler(lv_obj_t* dd, lv_event_t event);

void palette_event_handler(lv_obj_t* dd, lv_event_t event);

// Flush function for LVGL to write to the TFT display
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

// Touch read function for LVGL to get input data
bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

#endif