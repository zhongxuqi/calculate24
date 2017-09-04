#ifndef __NUMBER_BLOCK_H__
#define __NUMBER_BLOCK_H__

#include "cocos2d.h"

class NumberBlock : public cocos2d::Layer {
protected:
    cocos2d::DrawNode* NodeBackground;
    cocos2d::Label* NodeNumber;
    float borderWidth;
    cocos2d::Vec2 *points;
    bool activeState;
    virtual bool init();
    int number;

public:
    static NumberBlock* create(float width, int number);
    CREATE_FUNC(NumberBlock);
    void SetActiveState(bool isActive);
    bool IsActive();
};

#endif