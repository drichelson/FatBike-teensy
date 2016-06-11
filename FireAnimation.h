//
// Created by Dan Richelson on 1/21/16.
//

#ifndef TEENSYCMAKE_FIREANIMATION_H
#define TEENSYCMAKE_FIREANIMATION_H

#include "AnimationBase.h"

class FireAnimation : AnimationBase {
public:
    FireAnimation();
    void Apply(uint32_t inTime);
private:
    FatBike &fatBike;
    float currentPosition;
};

#endif //TEENSYCMAKE_FIREANIMATION_H
