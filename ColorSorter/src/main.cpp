


#include <Arduino.h>
#include "sorter.h"
#include "colors.h"
#include "interface.h"

void setup() {
    
    Serial.begin(9600);

    sorter::init();

    colors::pins_init();

    interface::ap_init("ColorSorter", "rogybesp");
    interface::ws_init();

    delay(1000);

    sorter::start_thread();
}


void loop() {
	interface::handle();
}
