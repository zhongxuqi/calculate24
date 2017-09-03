#ifndef __NUMBER_BLOCK_H__
#define __NUMBER_BLOCK_H__

#include "cocos2d.h"
#include "Base.h"

class NumberBlock : public BaseComponent {
protected:
    cocos2d::DrawNode* NodeBackground;
    cocos2d::Label* NodeNumber;
    float borderWidth;
    cocos2d::Vec2 *points;
    bool activeState;

public:
    NumberBlock(int number);
    const int Number;
    void SetActiveState(bool isActive);
    bool IsActive();

    static NumberBlock* create(float width, int number);
};

#endif