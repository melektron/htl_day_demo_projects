#include "led_bar.hpp"


void led_bar::setup()
{
    FastLED.addLeds<WS2813, DATA_PIN, GBR>(leds, NUM_LEDS);

    // global brightness scaling
    FastLED.setBrightness(75);

    // set default color
    setAll(CRGB::White);
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
