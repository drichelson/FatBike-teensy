#define USE_OCTOWS2811

#include <Arduino.h>
#include <OctoWS2811.h>
#include <FastLED.h>
//#include <lib8tion.h>
#include "FatBike.h"
#include "FatBike.cpp"
//#include "sensors.h"
//#include "flash.h"
#include "Fire.h"
#include "Sparkles.h"
#include "Sparkles.cpp"

long frameCount = 0L;
long startMillis = 0L;
uint8_t pixelOnGround = 0;
float bikeSpeedMph = 0.0F;
boolean isMovingMode = false;

Fire *fire;
FatBike *fatBike;
Sparkles *sparkles;

void determineMode() {
    isMovingMode = bikeSpeedMph > 4.0F;
}

void setup() {
//    delay(5000);
    Serial.begin(115200);
    Serial.println(F("Starting..."));
    startMillis = millis();
//    initFlash();

//    initSensors();
//    addSensorEntropy();

//    pixelOnGround = getPixelOnGround();
//    bikeSpeedMph = getBikeSpeedMph();

    fatBike = &FatBike::getInstance();
    fire = &Fire::getInstance();
//    sparkles = &Sparkles::getInstance();
}

void loop() {

    if (frameCount % 100 == 0) {
//        addSensorEntropy();
//        Serial.println(bikeSpeedMph);
        long now = millis();
        float secondsPer100Frames = (now - startMillis) / 1000.0F;
        Serial.print(F("FPS: "));
        Serial.print(100.0 / secondsPer100Frames);
        Serial.println(F(""));

        startMillis = now;

        determineMode();
//        showGyro();
        Serial.println(pixelOnGround);
    }

    //BEGIN ANIMATION-SPECIFIC CODE

    //2 fps
//    bikeSpeedMph = getBikeSpeedMph();

    // calling getPixelOnGround every frame vs. every 10th frame costs us ~2-3 fps
//    if (frameCount % 10 == 0 && !isMovingMode && bikeSpeedMph < 0.5F) {
//        pixelOnGround = getPixelOnGround();
//    }
    fire->renderDoubleFire(pixelOnGround, bikeSpeedMph, isMovingMode);
//sparkles->Apply(0);
    //END ANIMATION-SPECIFIC CODE
delay(50);
    FastLED.show();
    fatBike->clearAll();
    frameCount++;
}
