#ifndef __FIRMWARE_H__
#define __FIRMWARE_H__

enum LEDMode {
    MIN = 0,
    RAINBOW = 1
};

extern LEDMode mode;
extern int brightness;
extern bool leds_on;

void setupLeds(void);
void updateLeds(void);

void setupEncoder(void);
void updateEncoder(void);

void setupTouch(void);
void updateTouch(void);

#endif // __FIRMWARE_H__