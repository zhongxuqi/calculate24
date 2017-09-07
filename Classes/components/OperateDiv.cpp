#include "SimpleAudioEngine.h"
#include "OperateDiv.h"

USING_NS_CC;
using namespace ui;

bool OperateDiv::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

OperateDiv* OperateDiv::create(float operateSize) {
    auto operateDiv = OperateDiv::create();
    operateDiv->setContentSize(Size(operateSize, operateSize));
    operateDiv->setIgnoreAnchorPointForPosition(false);

    auto operateDivBtn = Button::create("res/BgOperateDiv.png", "res/BgOperateDiv_Pressed.png");
    operateDivBtn->setContentSize(Size(operateSize, operateSize));
    operateDivBtn->setScale9Enabled(true);
    operateDivBtn->setCapInsets(Rect(0, 0, 53, 53));
    operateDivBtn->setContentSize(Size(operateSize, operateSize));
    operateDivBtn->setAnchorPoint(Point(0.5, 0.5));
    operateDivBtn->setPosition(Point(operateSize / 2, operateSize / 2));
    operateDiv->addChild(operateDivBtn, 0);

    auto iconOperateDiv = Sprite::create("res/IconDiv.png");
    iconOperateDiv->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperateDiv->setAnchorPoint(Point(0.5, 0.5));
    iconOperateDiv->setPosition(Point(operateSize / 2, operateSize / 2));
    operateDivBtn->addChild(iconOperateDiv, 0);

    return operateDiv;
}