#include <Arduino.h>

#include "firmware.h"

void setup() {
  setupEncoder();
  setupTouch();
  setupLeds();
}

void loop() {
  updateEncoder();
  updateTouch();
  updateLeds();
}