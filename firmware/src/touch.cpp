#include <Arduino.h>
#include "firmware.h"
#include "pins.h"
#include "debounce.h"

// 15000us = 15ms debounce time
#define DEBOUNCE_TOUCH 15000

// 10000ms = 10s on when touched
#define ON_TIME 10000

bool touch_enabled = true;

namespace {
    DebouncedInput touch(CAP_TOUCH_PIN, DEBOUNCE_TOUCH);
    uint32_t leds_on_since = 0;
}

void setupTouch(void) {
    // Nothing to do here?
}

void updateTouch(void) {
    touch.update();
    if (!touch_enabled) { return; }
    if (!leds_on && touch.value()) {
        // Turn on when touched
        leds_on_since = millis();
        leds_on = true;
        updateLeds();
    } else if (leds_on) {
        // Turn off after ON_TIME
        const uint32_t curr_t = millis();
        if (curr_t < leds_on_since || curr_t > leds_on_since + ON_TIME) {
            leds_on = false;
            updateLeds();
        }
    }
}