# 1 "/tmp/tmpdgxyl2ii"
#include <Arduino.h>
# 1 "/home/gbe/projects/Watchy/src/7_SEG.ino"
#include "Watchy_7_SEG.h"
#include "settings.h"

Watchy7SEG watchy(settings);
void setup();
void loop();
#line 6 "/home/gbe/projects/Watchy/src/7_SEG.ino"
void setup() {
 watchy.init();
}

void loop() {}