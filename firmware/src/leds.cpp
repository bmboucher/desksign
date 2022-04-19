#include <Arduino.h>
#include "firmware.h"
#include "OctoWS2811.h"

LEDMode mode = LEDMode::RAINBOW;
int brightness = 0;
bool leds_on = false;

#define N_LED_PINS 8
#define LEDS_PER_PIN 9
#define N_LEDS (N_LED_PINS*LEDS_PER_PIN)
#define BYTES_PER_LED 3
#define LED_CONFIG (WS2811_RGB | WS2811_800kHz)

namespace {
    const byte LED_PINS[N_LED_PINS] = {15,16,17,18,19,20,21,22};
    DMAMEM int displayMemory[N_LEDS * BYTES_PER_LED / 4];
    DMAMEM int drawingMemory[N_LEDS * BYTES_PER_LED / 4];
    OctoWS2811 leds(LEDS_PER_PIN, displayMemory, drawingMemory, 
        LED_CONFIG, N_LED_PINS, LED_PINS);
}

void setupLeds() {
    leds.begin();
    leds.show();
}

void updateLeds() {
    leds.show();
}