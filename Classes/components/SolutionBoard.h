#ifndef __SOLUTION_BOARD_H__
#define __SOLUTION_BOARD_H__

#include "cocos2d.h"

class SolutionBoard : public cocos2d::Layer {
protected:
    virtual bool init();

public:
    static SolutionBoard* create(float width, float height);
    CREATE_FUNC(SolutionBoard);
};

#endif