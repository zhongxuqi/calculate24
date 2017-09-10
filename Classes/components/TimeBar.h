#ifndef __TIME_BAR_H__
#define __TIME_BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TimeBar : public cocos2d::Layer {
protected:
    virtual bool init();
    cocos2d::ui::LoadingBar *loadingBar;

public:
    static TimeBar* create(float width, float height);
    CREATE_FUNC(TimeBar);
    void SetPercent(float percent);
};

#endif