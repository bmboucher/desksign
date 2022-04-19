#ifndef __FIRMWARE_H__
#define __FIRMWARE_H__

// Implemented in leds.cpp
enum LEDMode {
    MIN = 0,
    RAINBOW = 1
};

extern LEDMode mode;
extern int brightness;
extern bool leds_on;

void setupLeds(void);
void updateLeds(void);

// Implemented in encoder.cpp
void setupEncoder(void);
void updateEncoder(void);

// Implemented in touch.cpp
extern bool touch_enabled;

void setupTouch(void);
void updateTouch(void);

#endif // __FIRMWARE_H__