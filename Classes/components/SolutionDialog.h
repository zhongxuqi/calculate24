#ifndef __SOLUTION_DIALOG_H__
#define __SOLUTION_DIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../base/GameEngine.h"

class SolutionDialog : public cocos2d::Layer {
protected:
    int number[SELECTED_MAX];
    std::function<void(void)> closeListener;
    cocos2d::ui::Button* backButton;

public:
    SolutionDialog();
    void SetOnCloseListener(std::function<void(cocos2d::Ref*)> listener);

    static SolutionDialog* create(float width, float height);
};

#endif