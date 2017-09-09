#ifndef __OPERATE_BTN_H__
#define __OPERATE_BTN_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class OperateBtn : public cocos2d::Layer {
protected:
    cocos2d::ui::Button* button;
    char operatorTxt;

public:
    void SetOnClickListener(std::function<void(cocos2d::Ref*)> clickListener);
    cocos2d::Ref *GetRef();
    char GetOperator();
};

#endif