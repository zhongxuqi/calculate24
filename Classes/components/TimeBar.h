#ifndef __TIME_BAR_H__
#define __TIME_BAR_H__

#include "cocos2d.h"

class TimeBar : public cocos2d::Layer {
protected:
    virtual bool init();

public:
    static TimeBar* create(float width, float height);
    CREATE_FUNC(TimeBar);
};

#endif