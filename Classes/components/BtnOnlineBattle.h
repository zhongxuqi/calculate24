#ifndef __BTN_ONLINE_BATTLE_H__
#define __BTN_ONLINE_BATTLE_H__

#include "cocos2d.h"
#include "Base.h"
#include "ui/CocosGUI.h"

class BtnOnlineBattle: public BaseComponent {
protected:
    cocos2d::ui::Button* button;

public:
    BtnOnlineBattle();

    static BtnOnlineBattle* create(float width, float height);
};

#endif