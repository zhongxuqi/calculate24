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
    cocos2d::ui::Button* closeButton;
    cocos2d::ui::Button* backButton;
    cocos2d::ui::Button* resetButton;
    void addCloseBtn();
    void addBackBtn();
    void addResetBtn();
    SolutionBoard* solutionBoard;
    AccurateNumber *accurateNumbers[4];
    void onBackListener(cocos2d::Ref* pRef);

public:
    void SetNumbers(AccurateNumber*[4]);
    static SolutionDialog* create(float width, float height);
    CREATE_FUNC(SolutionDialog);
    void SetOnCloseListener(std::function<void(cocos2d::Ref*)> listener);
    void SetOnFinishListener(std::function<void(InputStep*[3])> listener);
};

#endif