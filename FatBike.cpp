#include "FatBike.h"

FatBike::FatBike() {
    LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS);
    FastLED.setMaxRefreshRate(MAX_FPS, true);
    FastLED.setBrightness(GLOBAL_BRIGHTNESS);
    FastLED.countFPS(1000);
    testPattern();
}

float FatBike::Forward1(float thisPixel) {
    return Forward(thisPixel, 1.0);
}

// Forward = same direction as motion of wheel (see arrow on tire)
float FatBike::Forward(float thisPixel, float shiftAmount) {
//    Serial.println(shiftAmount);
    float newPosition = thisPixel + shiftAmount;
    if (newPosition < NUM_LEDS) {
        return newPosition;
    }
    else {
        return newPosition - NUM_LEDS;
    }
}

float FatBike::Back1(float thisPixel) {
    return Back(thisPixel, 1.0);
}

float FatBike::Back(float thisPixel, float shiftAmount) {
//    Serial.println(shiftAmount);
    float newPosition = thisPixel - shiftAmount;
    if (newPosition >= 0) {
        return newPosition;
    }
    else {
        return newPosition + NUM_LEDS;
    }
}

void FatBike::clearAll() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
    }
}

void FatBike::testPattern() {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
//            delay(1);
        FastLED.show();
        leds[i] = CRGB::Black;
    }
}
