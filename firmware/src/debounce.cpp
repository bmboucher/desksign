#include <Arduino.h>
#include "debounce.h"

DebouncedInput::DebouncedInput(int pin, uint32_t debounce) 
    : pin(pin), debounce(debounce) {
    pinMode(pin, INPUT_PULLUP);
    this->oldValue = (digitalRead(pin) == HIGH);
}

bool DebouncedInput::value(void) {
    return this->oldValue;
}

void DebouncedInput::update(void) {
    const bool readValue = (digitalRead(this->pin) == HIGH);
    if (readValue != this->oldValue) {
        const uint32_t curr_t = micros();
        if (readValue == this->newValue) {
            if (curr_t < this->lastChange || curr_t > this->lastChange + this->debounce) {
                // Input has been different long enough to change held value
                this->oldValue = readValue;
            }
        } else {
            // This is the first time the input has changed, mark the time
            this->newValue = readValue;
            this->lastChange = curr_t;
        }
    } else {
        // Reset to "not changing"
        this->newValue = this->oldValue;
    }
}