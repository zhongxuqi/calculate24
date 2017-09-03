#ifndef __SOLUTION_DIALOG_H__
#define __SOLUTION_DIALOG_H__

#include "cocos2d.h"
#include "../base/GameEngine.h"

class SolutionDialog : public cocos2d::Layer {
protected:
    int number[SELECTED_MAX];

public:
    SolutionDialog();

    static SolutionDialog* create(float width, float height);
};

#endif