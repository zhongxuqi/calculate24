#ifndef __TIME_BAR_H__
#define __TIME_BAR_H__

#include "cocos2d.h"
#include "Base.h"

class TimeBar : public BaseComponent {
public:
    TimeBar();

    static TimeBar* create(float width, float height);
};

#endif