#ifndef __TARGET_BAR_H__
#define __TARGET_BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TargetBar : public cocos2d::Layer {
protected:
    virtual bool init();
    int target;
    cocos2d::Label *targetLabel;

public:
    static TargetBar* create(float width, float height);
    CREATE_FUNC(TargetBar);
    TargetBar();
    cocos2d::Layer* const ContentLayer;
    void SetTarget(int target);
    int GetTarget();
};

#endif