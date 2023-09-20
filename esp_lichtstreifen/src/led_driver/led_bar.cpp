#include "led_bar.hpp"

CRGB led_bar::leds[NUM_LEDS];


void led_bar::setup(const CRGB &default_color)
{
    FastLED.addLeds<WS2813, DATA_PIN, GBR>(leds, NUM_LEDS);

    // global brightness scaling
    FastLED.setBrightness(75);

    // set default color
    setAll(default_color);
}


void led_bar::setAll(const CRGB &_color)
{
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = _color;
    
    FastLED.show();
}

void led_bar::colorSpan()
{
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CHSV(map(i, 0, NUM_LEDS - 1, 60, 255), 255, 255);

    FastLED.show();
}


void led_bar::setPercentage(double distPerc, const CRGB &on_color, const CRGB &off_color)
{
    int curr_led_index = 0;
    int stop_led_idnex = int((distPerc / 100) * NUM_LEDS);

    for (; curr_led_index < stop_led_idnex; curr_led_index++)
    {
        leds[curr_led_index] = on_color;
    }

    for (; curr_led_index < NUM_LEDS; curr_led_index++)
    {
        leds[curr_led_index] = off_color;
    }
}
