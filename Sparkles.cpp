//
// Created by Dan Richelson on 1/21/16.
//

#include "Sparkles.h"
//Sparkles::Sparkles() {
//    Serial.println("Sparkles ctor");
//    fatBike = FatBike::getInstance();
//    currentPosition = 0.0F;
//}

void Sparkles::Apply(uint32_t inTime) {

    for (int i = 0; i < position && i < NUM_LEDS; i++) {
        fatBike.leds[i] = CHSV(random8(), 255, 255);
    }
    if (position >= NUM_LEDS) increasing = false;
    else if (position <= 0)increasing = true;

    if (increasing) position++;
    else if (!increasing) position--;

    delay(50);
}