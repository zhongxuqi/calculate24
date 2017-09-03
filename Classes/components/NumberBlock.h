#ifndef __NUMBER_BLOCK_H__
#define __NUMBER_BLOCK_H__

#include "cocos2d.h"
#include "Base.h"

class NumberBlock : public BaseComponent {
protected:
    cocos2d::DrawNode* NodeBackground;
    cocos2d::Label* NodeNumber;

public:
    NumberBlock(int number);
    const int Number;

    static NumberBlock* create(float width, int number);
};

#endif