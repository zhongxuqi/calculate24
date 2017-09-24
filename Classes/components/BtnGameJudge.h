#ifndef __GAME_JUDGE_H__
#define __GAME_JUDGE_H__

#include "cocos2d.h"
#include "cocos-ext.h" 

class BtnGameJudge : public cocos2d::Layer {
protected:
    cocos2d::ui::Scale9Sprite* BackgroundRed;
    cocos2d::ui::Scale9Sprite* BackgroundGreen;
    const float borderWidth;
    cocos2d::Vec2 *points;
    virtual bool init();
    cocos2d::EventListenerTouchOneByOne* eventListener;
    std::function<void()> clickListener;
    cocos2d::Label* textLabel;
    cocos2d::Color4B color;
    bool passState;

public:
    BtnGameJudge();
    static BtnGameJudge* create(float width, float height);
    CREATE_FUNC(BtnGameJudge);
    bool IsActive();
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void SetOnClickListener(std::function<void()> listener);
    void SetPassState(bool passState);
    bool IsPass();
};

#endif