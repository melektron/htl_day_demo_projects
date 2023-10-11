#include <Arduino.h>
#pragma once



namespace stepper
{
    extern const bool steps[4][4];

    union stepper_pins_t
    {
        struct 
        {
            int a;
            int b;
            int c;
            int d;
        };
        int as_array[4];
    };

    /**
     * @brief Stepper motor driver
     * 
     */
    class Stepper
    {
        private:
            stepper_pins_t p;
            int current_position;
            int target_position;
            int max_steps_per_update = 100;
            double s;

            /**
             * @brief step once
             * 
             * @param direction false = forward, true = backward 
             */
            void stepOnce(bool direction = false);

        public:
            /**
             * @brief create a new stepper
             * 
             * @param speed motor speed (0 to 0)
             * @param starting_position should be set if the motor starts offset
             */
            Stepper(
                stepper_pins_t pins,
                double speed = 1,
                int starting_position = 0
            );

            /**
             * @brief needs to be called if setPosition is used
             * 
             */
            void update();

            /**
             * @brief step n steps
             * 
             * @param n how many steps to take
             */
            void step(int n);
            /**
             * @brief set a target position
             * 
             * @param position 
             */
            void setPosition(int position);

            void setMaxStepsPerUpdate(int steps);

            /**
             * @brief get the current position
             * 
             * @return int 
             */
            int getPosition();
            /**
             * @brief get the currently targeted position
             * 
             * @return int 
             */
            int getTargetPosition();
    };
}