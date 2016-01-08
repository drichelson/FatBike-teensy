#ifndef FATBIKE_FATBIKE_H
#define FATBIKE_FATBIKE_H

#include <FastLED.h>

//#define USE_OCTOWS2811
#define NUM_LEDS 244.0F
#define NUM_STRIPS 8
#define DATA_PIN 6

//Singleton to make all the other things easier.
class FatBike {
public:
    CRGB leds[(int) NUM_LEDS];

    static float Forward(float thisPixel, float shiftAmount);

    static float Back(float thisPixel, float shiftAmount);

    static float Forward1(float thisPixel);

    static float Back1(float thisPixel);

    void testPattern();

    void clearAll();

    static FatBike &getInstance() {
        static FatBike instance;
        return instance;
    }

private:
    FatBike();;

    FatBike(FatBike const &);              // Don't Implement
    void operator=(FatBike const &);
};

#endif //FATBIKE_FATBIKE_H
