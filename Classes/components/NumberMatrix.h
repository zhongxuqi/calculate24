#ifndef __NUMBER_MATRIX_H__
#define __NUMBER_MATRIX_H__

#include "cocos2d.h"
#include "Base.h"
#include "NumberBlock.h"
#include "../base/GameEngine.h"

class NumberMatrix : public cocos2d::Layer {
protected:
    int selectedBlockIndexes[SELECTED_MAX][2];
    NumberBlock* selectedNumberBlocks[SELECTED_MAX];
    int selectedLen;
    float numberBlockSize;
    float numberBlockInterval;
    void handleTouch(cocos2d::Touch *touch);
    cocos2d::EventListenerTouchOneByOne* eventListener;
    NumberBlock* numberNodeMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    
    void handleSelectBlock();
    void cancelSelectBlock();

    std::function<void(void)> selectListener;

public:
    NumberMatrix();

    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void setTouchable(bool isTouchable);
    void SetOnSelectListener(std::function<void(void)> listener);

    static NumberMatrix* create(float width, float height);
};

#endif