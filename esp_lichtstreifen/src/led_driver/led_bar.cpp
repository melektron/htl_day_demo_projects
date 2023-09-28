#include "led_bar.hpp"
#include <iostream>


std::array<CRGB, NUM_LEDS> led_bar::leds;

void led_bar::setup(const CRGB &default_color)
{
    FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds.data(), leds.size());

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
    FastLED.show();
}

void led_bar::setPercentageAnimation(double distPerc, Animation &on_color, Animation &off_color)
{
    int curr_led_index = 0;
    int stop_led_idnex = int((distPerc / 100) * NUM_LEDS);

    on_color.renderToStrip(leds, 0, stop_led_idnex);
    off_color.renderToStrip(leds, stop_led_idnex);
}


led_bar::Animation::Animation(double led_offset)
    : l_offset(led_offset)
{
}

void led_bar::Animation::stepPercent(double delta)
{
    current_animation_progress += delta;
}

void led_bar::Animation::renderToStrip(
    std::array<CRGB, NUM_LEDS> &strip,
    uint start_index,
    int end_index
)
{
    if (end_index < 0)
        end_index = strip.size();

    for (int i = start_index; i < end_index; i++)
    {
        strip[i] = animate(current_animation_progress + l_offset * i);
    }
    FastLED.show();
}

led_bar::FlowAnimation::FlowAnimation(double led_offset)
    : Animation(led_offset)
{
}

CRGB led_bar::FlowAnimation::animate(double progress)
{
    CHSV out(
        (int)(progress * 2.55),
        255,
        255);

    return out;
}


led_bar::ConstantAnimation::ConstantAnimation(CRGB color)
    : c(color), Animation(0)
{}

void led_bar::ConstantAnimation::renderToStrip(
    std::array<CRGB, NUM_LEDS> &strip,
    uint start_index,
    int end_index
)
{
    if (end_index < 0)
        end_index = strip.size();

    for (int i = start_index; i < end_index; i++)
    {
        strip[i] = c;
    }
    FastLED.show();
}

CRGB led_bar::ConstantAnimation::animate(double progress) {};
