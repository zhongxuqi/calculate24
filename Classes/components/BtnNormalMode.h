#ifndef __BTN_NORMAL_MODE_H__
#define __BTN_NORMAL_MODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

class BtnNormalMode: public cocos2d::Layer {
protected:
    cocos2d::ui::Button* button;

public:
    BtnNormalMode();
    void SetOnClickListener(std::function<void(cocos2d::Ref*)>);

    static BtnNormalMode* create(float width, float height);
};

#endif