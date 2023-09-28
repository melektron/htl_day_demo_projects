/**
 * @file led_bar.hpp
 * @author Nilusink
 * @brief Driver for the LED-bar
 * @version 1.0
 * @date 2023-09-20
 * 
 * @copyright Copyright Nilusink (c) 2023
 * 
 */
#pragma once
#include <FastLED.h>
#include <array>

#define DATA_PIN 23
#define NUM_LEDS 60


namespace led_bar
{
    extern std::array<CRGB, NUM_LEDS> leds;

    /**
     * @brief setup the leds (and sett all to white)
     * 
     */
    void setup(const CRGB &default_color = CRGB::Black);

    /**
     * @brief set the color of all leds
     * 
     * @param _color color to set
     */
    void setAll(const CRGB &_color);

    /**
     * @brief sweeps all colors
     * 
     */
    void colorSpan();

    /**
     * @brief Set the Percentage object
     * 
     * @param distPerc how many to set
     * @param on_color color of on leds
     * @param off_color color of off leds
     */
    void setPercentage(double distPerc, const CRGB &on_color, const CRGB &off_color);


    class Animation
    {
        protected:
            double current_animation_progress = 0;
            double l_offset;

            virtual CRGB animate(double progresss) = 0;

        public:
            Animation(double led_offset);

            void stepPercent(double delta);
            virtual void renderToStrip(
                std::array<CRGB, NUM_LEDS> &strip,
                uint start_index = 0,
                int end_index = -1
            );
    };


    void setPercentageAnimation(double distPerc, Animation &on_color, Animation &off_color);


    class FlowAnimation : public Animation
    {
        private:
            virtual CRGB animate(double progress) override;

        public:
            FlowAnimation(double led_offset);
    };

    class ConstantAnimation : public Animation
    {
        private:
            CRGB c;
            virtual CRGB animate(double progress) override;

        public:
            ConstantAnimation(CRGB color);
            void renderToStrip(
                std::array<CRGB, NUM_LEDS> &strip,
                uint start_index = 0,
                int end_index = -1
            );
    };
}
