#ifndef __NUMBER_BLOCK_H__
#define __NUMBER_BLOCK_H__

#include "cocos2d.h"

class NumberBlock : public cocos2d::Layer {
protected:
    cocos2d::DrawNode* NodeBackground;
    cocos2d::Label* NodeNumber;
    float borderWidth;
    cocos2d::Vec2 *points;
    bool activeState;
    virtual bool init();
    int number;
    cocos2d::EventListenerTouchOneByOne* eventListener;
    std::function<void(cocos2d::Node*)> clickListener;
    

public:
    static NumberBlock* create(float width, int number);
    CREATE_FUNC(NumberBlock);
    void SetActiveState(bool isActive);
    bool IsActive();
    int GetNumber();
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void SetOnClickListener(std::function<void(cocos2d::Node*)> listener);
};

#endif