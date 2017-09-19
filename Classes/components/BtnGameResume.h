#ifndef __GAME_RESUME_H__
#define __GAME_RESUME_H__

#include "cocos2d.h"

class BtnGameResume : public cocos2d::Layer {
protected:
    cocos2d::DrawNode* NodeBackground;
    const float borderWidth;
    cocos2d::Vec2 *points;
    virtual bool init();
    cocos2d::EventListenerTouchOneByOne* eventListener;
    std::function<void()> clickListener;
    cocos2d::Label* textLabel;
    void setActive(bool isActive);

public:
    BtnGameResume();
    static BtnGameResume* create(float width, float height);
    CREATE_FUNC(BtnGameResume);
    bool IsActive();
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void SetOnClickListener(std::function<void()> listener);
};

#endif