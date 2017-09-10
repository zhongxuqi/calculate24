#ifndef __NUMBER24_BLOCK_H__
#define __NUMBER24_BLOCK_H__

#include "cocos2d.h"
#include "../base/GameEngine.h"

class Number24Block : public cocos2d::Layer {
protected:
    cocos2d::DrawNode* NodeBackground;
    cocos2d::Label* NodeNumber;
    float borderWidth;
    cocos2d::Vec2 *points;
    bool activeState;
    virtual bool init();
    cocos2d::Color4B currColor;

public:
    static Number24Block* create(float width);
    CREATE_FUNC(Number24Block);
    void CheckNumberResult(AccurateNumber *accurateNumber);
    void ResetColor();
};

#endif