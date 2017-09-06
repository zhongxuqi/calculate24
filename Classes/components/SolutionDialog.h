#ifndef __SOLUTION_DIALOG_H__
#define __SOLUTION_DIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../base/GameEngine.h"
#include "SolutionBoard.h"

class SolutionDialog : public cocos2d::Layer {
protected:
    virtual bool init();
    int number[SELECTED_MAX];
    std::function<void(void)> closeListener;
    cocos2d::ui::Button* backButton;
    cocos2d::ui::Button* resetButton;
    void addBackBtn();
    void addResetBtn();
    SolutionBoard* solutionBoard;

public:
    static SolutionDialog* create(float width, float height);
    CREATE_FUNC(SolutionDialog);
    void SetOnCloseListener(std::function<void(cocos2d::Ref*)> listener);
};

#endif