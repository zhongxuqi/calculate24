#ifndef __NUMBER_MATRIX_H__
#define __NUMBER_MATRIX_H__

#include "cocos2d.h"
#include "NumberBlock.h"
#include "../base/GameEngine.h"
#include "SolutionBoard.h"

class NumberMatrix : public cocos2d::Layer {
protected:
    virtual bool init();
    BlockLocation selectedBlockIndexes[SELECTED_MAX];
    NumberBlock* selectedNumberBlocks[SELECTED_MAX];
    int selectedLen;
    float numberBlockSize;
    float numberBlockInterval;
    bool handleTouch(cocos2d::Touch *touch);
    cocos2d::EventListenerTouchOneByOne* eventListener;
    NumberBlock* numberNodeMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    void handleSelectBlock();
    std::function<void(AccurateNumber*[4])> selectListener;
    void handleTransfer(BlockTransfer *transfer);

public:
    static NumberMatrix* create(float width, float height);
    CREATE_FUNC(NumberMatrix);
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void setTouchable(bool isTouchable);
    void SetOnSelectListener(std::function<void(AccurateNumber*[4])> listener);
    bool PushSolution(InputStep* inputSteps[3]);
    void CancelSelectBlock();
};

#endif