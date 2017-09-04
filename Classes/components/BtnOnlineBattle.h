#ifndef __BTN_ONLINE_BATTLE_H__
#define __BTN_ONLINE_BATTLE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class BtnOnlineBattle: public cocos2d::Layer {
protected:
    cocos2d::ui::Button* button;
    virtual bool init();

public:
    static BtnOnlineBattle* create(float width, float height);
    CREATE_FUNC(BtnOnlineBattle);
};

#endif