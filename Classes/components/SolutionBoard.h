#ifndef __SOLUTION_BOARD_H__
#define __SOLUTION_BOARD_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"
#include "Number24Block.h"
#include "OperatePlus.h"
#include "OperateMinus.h"
#include "OperateMult.h"
#include "OperateDiv.h"
#include "OperateBtn.h"

struct InputStep {
    AccurateNumber NumberLeft;
    char OperatorTxt;
    AccurateNumber NumberRight;
    AccurateNumber NumberResult;
};

class SolutionBoard : public cocos2d::Layer {
protected:
    virtual bool init();
    cocos2d::ui::Scale9Sprite* numberLefts[3];
    NumberBlock* numberBlockLefts[3];
    cocos2d::ui::Scale9Sprite* operators[3];
    OperateBtn* operatorOuts[3];
    cocos2d::ui::Scale9Sprite* numberRights[3];
    NumberBlock* numberBlockRights[3];
    cocos2d::ui::Scale9Sprite* numberResults[2];
    NumberBlock* numberBlockResults[2];
    Number24Block* number24BlockResult;
    cocos2d::ui::Button* numberFrames[SELECTED_MAX];
    OperatePlus* operatePlusBtn;
    OperateMinus* operateMinusBtn;
    OperateMult* operateMultBtn;
    OperateDiv* operateDivBtn;
    NumberBlock* numberBlocks[SELECTED_MAX];
    float numberSize;
    float operateSize;
    float equalSize;
    int currLine;
    int currIndex;
    cocos2d::Vec2 getTargetLocation();
    void onNumberClickListener(cocos2d::Ref *pRef);
    void onOperatorClickListener(cocos2d::Ref *pRef);
    void cursorToNext();
    bool checkCursor();
    void calculateLine();
    InputStep *inputSteps[3];
    std::function<void(InputStep*[3])> onFinishListener;
    const float duration = 0.3;

public:
    void InitNumber(AccurateNumber *accurateNumbers[4]);
    static SolutionBoard* create(float width, float height);
    CREATE_FUNC(SolutionBoard);
    void SetOnFinishListener(std::function<void(InputStep*[3])> listener);
    void GoBack();
};

#endif