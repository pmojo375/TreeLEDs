#include <gui.h>
#include <ledFunctions.h>

lv_obj_t *main_screen = nullptr;
lv_obj_t *color1_screen = nullptr;
lv_obj_t *color2_screen = nullptr;
lv_obj_t *color3_screen = nullptr;
lv_obj_t *color4_screen = nullptr;
lv_obj_t *brightness_screen = nullptr;
lv_obj_t *inc_gHue_screen = nullptr;
lv_obj_t *speed_screen = nullptr;
lv_obj_t *variability_screen = nullptr;
lv_obj_t *palette_screen = nullptr;
lv_obj_t *mode_screen = nullptr;
lv_obj_t *fade_rate_screen = nullptr;

// Button event handler to switch to a settings screen
void btn_event_handler_to_color1_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(color1_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_color2_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(color2_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_color3_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(color3_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_color4_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(color4_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_brightness_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(brightness_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_speed_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(speed_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_variability_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(variability_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_fade_rate_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(fade_rate_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_palette_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(palette_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_mode_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(mode_screen); // Load the respective settings screen
    }
}

// Button event handler to switch to a settings screen
void btn_event_handler_to_inc_gHue_screen(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(inc_gHue_screen); // Load the respective settings screen
    }
}

// Back button event handler
void back_btn_event_handler(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        lv_scr_load(main_screen); // Load the main screen
    }
}

void color1_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_color_t color = lv_cpicker_get_color(cpicker);
        mainColor = CRGB(color.ch.red, color.ch.green, color.ch.blue);
    }
}

void color2_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_color_t color = lv_cpicker_get_color(cpicker);
        secondaryColor1 = CRGB(color.ch.red, color.ch.green, color.ch.blue);
    }
}

void color3_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_color_t color = lv_cpicker_get_color(cpicker);
        secondaryColor2 = CRGB(color.ch.red, color.ch.green, color.ch.blue);
    }
}

void color4_cpicker_event_handler(lv_obj_t *cpicker, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        lv_color_t color = lv_cpicker_get_color(cpicker);
        secondaryColor3 = CRGB(color.ch.red, color.ch.green, color.ch.blue);
    }
}

void brightness_event_handler(lv_obj_t* slider, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        int value = lv_slider_get_value(slider);
        // Code to handle the slider value
        // For example, you can print the value to the serial console
        Serial.print("Slider Value: ");
        Serial.println(value);
        brightness = value;
    }
}

void fade_rate_event_handler(lv_obj_t* slider, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        int value = lv_slider_get_value(slider);
        // Code to handle the slider value
        // For example, you can print the value to the serial console
        Serial.print("Slider Value: ");
        Serial.println(value);
        fadeAmount = value;
    }
}

void speed_event_handler(lv_obj_t* slider, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        int value = lv_slider_get_value(slider);
        // Code to handle the slider value
        // For example, you can print the value to the serial console
        Serial.print("Slider Value: ");
        Serial.println(value);
        speed = value;
    }
}

void variability_event_handler(lv_obj_t* slider, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        int value = lv_slider_get_value(slider);
        // Code to handle the slider value
        // For example, you can print the value to the serial console
        Serial.print("Slider Value: ");
        Serial.println(value);
        speedVariability = value;
    }
}

void inc_gHue_event_handler(lv_obj_t* sw, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        if(lv_switch_get_state(sw)) {
            gHueState = true;
        } else {
            gHueState = false;
        }
    }
}

void palette_event_handler(lv_obj_t* dd, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        int selected_index = lv_dropdown_get_selected(dd); // Get the index of the selected option
        Serial.print("Selected Option Index: ");
        Serial.println(selected_index);
        setPallette(selected_index);
    }
}

void mode_event_handler(lv_obj_t* dd, lv_event_t event) {
    if(event == LV_EVENT_VALUE_CHANGED) {
        int selected_index = lv_dropdown_get_selected(dd); // Get the index of the selected option
        Serial.print("Selected Option Index: ");
        Serial.println(selected_index);
        mode = selected_index;
    }
}

// Function to create the main screen
void create_main_screen()
{
    main_screen = lv_obj_create(NULL, NULL); // Create a screen object

    lv_obj_t *btn_to_color2 = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_color2, btn_event_handler_to_color2_screen);

    // Set the button size
    lv_obj_set_size(btn_to_color2, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_color2, NULL, LV_ALIGN_CENTER, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *color2_btn_label = lv_label_create(btn_to_color2, NULL);
    lv_label_set_text(color2_btn_label, "Set Color 2"); // Repeat for other buttons


    // Create buttons on the main screen
    lv_obj_t *btn_to_color1 = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_color1, btn_event_handler_to_color1_screen);

    // Set the button size
    lv_obj_set_size(btn_to_color1, 100, 40);

    // Set the button position
    lv_obj_align(btn_to_color1, btn_to_color2, LV_ALIGN_OUT_LEFT_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *color1_btn_label = lv_label_create(btn_to_color1, NULL);
    lv_label_set_text(color1_btn_label, "Set Color 1"); // Repeat for other buttons


    lv_obj_t *btn_to_color3 = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_color3, btn_event_handler_to_color3_screen);

    // Set the button size
    lv_obj_set_size(btn_to_color3, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_color3, btn_to_color2, LV_ALIGN_OUT_RIGHT_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *color3_btn_label = lv_label_create(btn_to_color3, NULL);
    lv_label_set_text(color3_btn_label, "Set Color 3"); // Repeat for other buttons


    lv_obj_t *btn_to_color4 = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_color4, btn_event_handler_to_color4_screen);

    // Set the button size
    lv_obj_set_size(btn_to_color4, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_color4, btn_to_color1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *color4_btn_label = lv_label_create(btn_to_color4, NULL);
    lv_label_set_text(color4_btn_label, "Set Color 4"); // Repeat for other buttons


    lv_obj_t *btn_to_brightness = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_brightness, btn_event_handler_to_brightness_screen);

    // Set the button size
    lv_obj_set_size(btn_to_brightness, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_brightness, btn_to_color2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *brightness_btn_label = lv_label_create(btn_to_brightness, NULL);
    lv_label_set_text(brightness_btn_label, "Brightness"); // Repeat for other buttons

    

    lv_obj_t *btn_to_speed = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_speed, btn_event_handler_to_speed_screen);

    // Set the button size
    lv_obj_set_size(btn_to_speed, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_speed, btn_to_color3, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *speed_btn_label = lv_label_create(btn_to_speed, NULL);
    lv_label_set_text(speed_btn_label, "Speed"); // Repeat for other buttons

    
    lv_obj_t *btn_to_variability = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_variability, btn_event_handler_to_variability_screen);

    // Set the button size
    lv_obj_set_size(btn_to_variability, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_variability, btn_to_color1, LV_ALIGN_OUT_TOP_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *variability_btn_label = lv_label_create(btn_to_variability, NULL);
    lv_label_set_text(variability_btn_label, "Variability"); // Repeat for other buttons
    

    lv_obj_t *btn_to_fade_rate = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_fade_rate, btn_event_handler_to_fade_rate_screen);

    // Set the button size
    lv_obj_set_size(btn_to_fade_rate, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_fade_rate, btn_to_color2, LV_ALIGN_OUT_TOP_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *fade_rate_btn_label = lv_label_create(btn_to_fade_rate, NULL);
    lv_label_set_text(fade_rate_btn_label, "Fade Rate"); // Repeat for other buttons


    lv_obj_t *btn_to_mode = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_mode, btn_event_handler_to_mode_screen);

    // Set the button size
    lv_obj_set_size(btn_to_mode, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_mode, btn_to_color3, LV_ALIGN_OUT_TOP_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *mode_btn_label = lv_label_create(btn_to_mode, NULL);
    lv_label_set_text(mode_btn_label, "Mode"); // Repeat for other buttons


    lv_obj_t *btn_to_palette = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_palette, btn_event_handler_to_palette_screen);

    // Set the button size
    lv_obj_set_size(btn_to_palette, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_palette, btn_to_variability, LV_ALIGN_OUT_TOP_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *palette_btn_label = lv_label_create(btn_to_palette, NULL);
    lv_label_set_text(palette_btn_label, "Palette"); // Repeat for other buttons


    lv_obj_t *btn_to_inc_gHue = lv_btn_create(main_screen, NULL);
    lv_obj_set_event_cb(btn_to_inc_gHue, btn_event_handler_to_inc_gHue_screen);

    // Set the button size
    lv_obj_set_size(btn_to_inc_gHue, 100, 40);

    // Set the button position to next to the first button
    lv_obj_align(btn_to_inc_gHue, btn_to_fade_rate, LV_ALIGN_OUT_TOP_MID, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *inc_gHue_btn_label = lv_label_create(btn_to_inc_gHue, NULL);
    lv_label_set_text(inc_gHue_btn_label, "Inc gHue"); // Repeat for other buttons
}

// Function to create a settings screen
void create_color1_screen()
{
    color1_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(color1_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    // Create a color picker
    lv_obj_t *cpicker;
    cpicker = lv_cpicker_create(color1_screen, NULL);
    lv_obj_set_size(cpicker, 200, 200);
    lv_obj_align(cpicker, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_event_cb(cpicker, color1_cpicker_event_handler);
}

// Function to create a settings screen
void create_color2_screen()
{
    color2_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(color2_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    // Create a color picker
    lv_obj_t *cpicker;
    cpicker = lv_cpicker_create(color2_screen, NULL);
    lv_obj_set_size(cpicker, 200, 200);
    lv_obj_align(cpicker, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_event_cb(cpicker, color2_cpicker_event_handler);
}

// Function to create a settings screen
void create_color3_screen()
{
    color3_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(color3_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    // Create a color picker
    lv_obj_t *cpicker;
    cpicker = lv_cpicker_create(color3_screen, NULL);
    lv_obj_set_size(cpicker, 200, 200);
    lv_obj_align(cpicker, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_event_cb(cpicker, color3_cpicker_event_handler);
}

// Function to create a settings screen
void create_color4_screen()
{
    color4_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(color4_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    // Create a color picker
    lv_obj_t *cpicker;
    cpicker = lv_cpicker_create(color4_screen, NULL);
    lv_obj_set_size(cpicker, 200, 200);
    lv_obj_align(cpicker, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_set_event_cb(cpicker, color4_cpicker_event_handler);
}

void create_brightness_screen() {
    brightness_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(brightness_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* brightness_slider = lv_slider_create(brightness_screen, NULL); // Create a slider and attach it to the parent (a screen or a container)

    // Position the slider (optional, depends on your layout)
    lv_obj_set_width(brightness_slider, 200); // Set the width of the slider
    lv_obj_align(brightness_slider, NULL, LV_ALIGN_CENTER, 0, 0); // Center the slider

    // Set the range of the slider
    lv_slider_set_range(brightness_slider, 0, 255);

    // Set the initial value
    lv_slider_set_value(brightness_slider, 50, LV_ANIM_OFF);

    lv_obj_set_event_cb(brightness_slider, brightness_event_handler);
}

void create_fade_rate_screen() {
    fade_rate_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(fade_rate_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* fade_rate_slider = lv_slider_create(fade_rate_screen, NULL); // Create a slider and attach it to the parent (a screen or a container)

    // Position the slider (optional, depends on your layout)
    lv_obj_set_width(fade_rate_slider, 200); // Set the width of the slider
    lv_obj_align(fade_rate_slider, NULL, LV_ALIGN_CENTER, 0, 0); // Center the slider

    // Set the range of the slider
    lv_slider_set_range(fade_rate_slider, 0, 255);

    // Set the initial value
    lv_slider_set_value(fade_rate_slider, 50, LV_ANIM_OFF);

    lv_obj_set_event_cb(fade_rate_slider, fade_rate_event_handler);
}

void create_speed_screen() {
    speed_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(speed_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* speed_slider = lv_slider_create(speed_screen, NULL); // Create a slider and attach it to the parent (a screen or a container)

    // Position the slider (optional, depends on your layout)
    lv_obj_set_width(speed_slider, 200); // Set the width of the slider
    lv_obj_align(speed_slider, NULL, LV_ALIGN_CENTER, 0, 0); // Center the slider

    // Set the range of the slider
    lv_slider_set_range(speed_slider, 1, 100);

    // Set the initial value
    lv_slider_set_value(speed_slider, 50, LV_ANIM_OFF);

    lv_obj_set_event_cb(speed_slider, speed_event_handler);
}

void create_variability_screen() {
    variability_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(variability_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* variability_slider = lv_slider_create(variability_screen, NULL); // Create a slider and attach it to the parent (a screen or a container)

    // Position the slider (optional, depends on your layout)
    lv_obj_set_width(variability_slider, 200); // Set the width of the slider
    lv_obj_align(variability_slider, NULL, LV_ALIGN_CENTER, 0, 0); // Center the slider

    // Set the range of the slider
    lv_slider_set_range(variability_slider, 0, 200);

    // Set the initial value
    lv_slider_set_value(variability_slider, 50, LV_ANIM_OFF);

    lv_obj_set_event_cb(variability_slider, variability_event_handler);
}

void create_inc_gHue_screen() {
    inc_gHue_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(inc_gHue_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* sw = lv_switch_create(inc_gHue_screen, NULL); // Create a switch and attach it to the parent (a screen or a container)

    // Position the switch (optional, depends on your layout)
    lv_obj_align(sw, NULL, LV_ALIGN_CENTER, 0, 0);

    // You can set the state of the switch (on/off)
    lv_switch_on(sw, LV_ANIM_OFF); // Turns the switch on without animation
    // or lv_switch_off(sw, LV_ANIM_ON); to turn it off with animation
    
    lv_obj_set_event_cb(sw, inc_gHue_event_handler);
}

void create_palette_screen() {
    palette_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(palette_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* palette_dropdown = lv_dropdown_create(palette_screen, NULL); // Create a dropdown and attach it to the parent (a screen or a container)

    // Add options to the dropdown
    lv_dropdown_set_options(palette_dropdown, "RainbowColors\nRainbowStripeColors\nCloudColors\nLavaColors\nOceanColors\nForestColors\nPartyColors\nHeatColors");

    // Position the dropdown (optional, depends on your layout)
    lv_obj_align(palette_dropdown, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);

    // Set the initial selected option
    lv_dropdown_set_selected(palette_dropdown, 0); // Selects the first option

    lv_obj_set_event_cb(palette_dropdown, palette_event_handler);
}

void create_mode_screen() {
    mode_screen = lv_obj_create(NULL, NULL);

    // Create a back button
    lv_obj_t *back_btn = lv_btn_create(mode_screen, NULL);

    lv_obj_set_event_cb(back_btn, back_btn_event_handler);

    // Set the button size
    lv_obj_set_size(back_btn, 70, 40);

    // Set the button position
    lv_obj_align(back_btn, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // Create label for the button (optional)
    lv_obj_t *label = lv_label_create(back_btn, NULL);
    lv_label_set_text(label, "Back"); // Repeat for other buttons

    lv_obj_t* mode_dropdown = lv_dropdown_create(mode_screen, NULL); // Create a dropdown and attach it to the parent (a screen or a container)

    // Add options to the dropdown
    lv_dropdown_set_options(mode_dropdown, "Normal\nColor Waves\nTwinkling Stars\nCandy Cane\nRising Sparkles\nMeteor Rain");

    // Position the dropdown (optional, depends on your layout)
    lv_obj_align(mode_dropdown, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);

    // Set the initial selected option
    lv_dropdown_set_selected(mode_dropdown, 0); // Selects the first option

    lv_obj_set_event_cb(mode_dropdown, mode_event_handler);
}

// Flush function for LVGL to write to the TFT display
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    tft.pushColors(&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
    tft.endWrite();
    lv_disp_flush_ready(disp);
}

// Touch read function for LVGL to get input data
bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch(&touchX, &touchY);
    if (touched)
    {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    return touched; // Return 'true' if there is touch data to read, 'false' otherwise
}
