#ifndef __SOLUTION_BOARD_H__
#define __SOLUTION_BOARD_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"
#include "OperatePlus.h"
#include "OperateMinus.h"
#include "OperateMult.h"
#include "OperateDiv.h"

class SolutionBoard : public cocos2d::Layer {
protected:
    virtual bool init();
    cocos2d::ui::Scale9Sprite* numberLefts[3];
    cocos2d::ui::Scale9Sprite* operators[3];
    cocos2d::ui::Scale9Sprite* numberRights[3];
    cocos2d::ui::Scale9Sprite* numberResults[3];
    cocos2d::ui::Scale9Sprite* numberFrames[4];
    OperatePlus* operatePlusBtn;
    OperateMinus* operateMinusBtn;
    OperateMult* operateMultBtn;
    OperateDiv* operateDivBtn;
    NumberBlock* numberBlocks[4];
    NumberBlock* numberOuts[3];
    NumberBlock* numberNewBlocks[2];
    float numberSize;
    float operateSize;
    int currLine;
    int currIndex;
    bool emptyBlock[4];
    cocos2d::Vec2 getTargetLocation();
    void onNumberClickListener(cocos2d::Node* node);

public:
    void InitNumber(int numbers[4]);
    static SolutionBoard* create(float width, float height);
    CREATE_FUNC(SolutionBoard);
};

#endif