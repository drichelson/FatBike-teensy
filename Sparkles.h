//
// Created by Dan Richelson on 1/21/16.
//


#ifndef TEENSYCMAKE_SPARKLES_H
#define TEENSYCMAKE_SPARKLES_H

#include "AnimationBase.h"

class Sparkles : public AnimationBase {
public:
    static Sparkles &getInstance() {
        static Sparkles instance;
        return instance;
    }

    void Apply(uint32_t inTime);

private:
    Sparkles():
            fatBike(FatBike::getInstance()),
            currentPosition(0.0F) { }

    FatBike &fatBike;
    float currentPosition;
    boolean increasing = true;
    uint8_t position = 0;

    //These 2 are to keep the singleton pattern intact
    Sparkles(Sparkles const &);              // Don't Implement
    void operator=(Sparkles const &);
};


#endif //TEENSYCMAKE_SPARKLES_H
