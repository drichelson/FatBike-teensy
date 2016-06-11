//
// Created by Dan Richelson on 1/21/16.
//

#ifndef TEENSYCMAKE_ANIMATIONBASE_H
#define TEENSYCMAKE_ANIMATIONBASE_H
/**
 * Common abstract base class for all animation classes.
 *
 */
class AnimationBase
{
public:
    virtual ~AnimationBase() {}
    virtual void Apply(uint32_t inTime) = 0;
};
#endif //TEENSYCMAKE_ANIMATIONBASE_H
