#include <Arduino.h>
#include "firmware.h"
#include "pins.h"
#include "debounce.h"

// 5000us = 5ms debounce time
#define DEBOUNCE_ENCODER 5000

namespace {
    DebouncedInput encoderBtn(ENCODER_BTN, DEBOUNCE_ENCODER);
    DebouncedInput encoderRotA(ENCODER_ROT_A, DEBOUNCE_ENCODER);
    DebouncedInput encoderRotB(ENCODER_ROT_B, DEBOUNCE_ENCODER);

    // State variables
    bool btn_down = false;
    int encoder_bin = 0;
    int readEncoderBin(void) {
        return (encoderRotA.value() ? 2 : 0) + (encoderRotB.value() ? 1 : 0);
    }

    enum EncoderMode {
        NONE = 0,
        SEL_MODE = 1,
        SEL_BRIGHTNESS = 2
    };
    EncoderMode encoder_mode = EncoderMode::NONE;

    void onEncoderBtnPress() {
        if (encoder_mode == EncoderMode::NONE) {
            touch_enabled = false;
            leds_on = true;
            encoder_mode = EncoderMode::SEL_MODE;
        } else if (encoder_mode == EncoderMode::SEL_MODE) {
            encoder_mode = EncoderMode::SEL_BRIGHTNESS;
        } else if (encoder_mode == EncoderMode::SEL_BRIGHTNESS) {
            touch_enabled = true;
            leds_on = false;
            encoder_mode = EncoderMode::NONE;
        }
    }

    void onEncoderInc(int sign) {
        switch(encoder_mode) {
            case EncoderMode::SEL_MODE:
                {
                    int new_mode = (int)(mode) + sign;
                    if (new_mode == LEDMode::MAX) {
                        new_mode = (int)(LEDMode::DEFAULT);
                    } else if (new_mode == LEDMode::MIN) {
                        new_mode = (int)(LEDMode::MAX) - 1;
                    }
                    if (new_mode != (int)mode) {
                        mode = (LEDMode)new_mode;
                        paintLeds();
                    }
                    break;
                }
            case EncoderMode::SEL_BRIGHTNESS:
                {
                    int new_brightness = brightness + sign;
                    if (new_brightness < 0) {
                        new_brightness = 0;
                    } else if (new_brightness > 255) {
                        new_brightness = 255;
                    }
                    if (new_brightness != brightness) { 
                        brightness = new_brightness;
                        paintLeds();
                    }
                    break;
                }
            default:
                break;
        }
    }
}


void setupEncoder(void) {
    encoder_bin = readEncoderBin();
}

void updateEncoder(void) {
    encoderBtn.update();
    encoderRotA.update();
    encoderRotB.update();

    if (btn_down != encoderBtn.value()) {
        btn_down = encoderBtn.value();
        if (btn_down) { onEncoderBtnPress(); }
    }

    const int new_bin = readEncoderBin();
    if (new_bin != encoder_bin) {
        if (new_bin == (encoder_bin + 1) % 4) {
            onEncoderInc(1);  // Step up
        } else if (new_bin == (encoder_bin - 1) % 4) {
            onEncoderInc(-1); // Step down
        }
        encoder_bin = new_bin;
    }
}