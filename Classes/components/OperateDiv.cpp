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
    operateDiv->operatorTxt = '/';

    operateDiv->button = Button::create("res/BgOperateDiv.png", "res/BgOperateDiv_Pressed.png");
    operateDiv->button->setContentSize(Size(operateSize, operateSize));
    operateDiv->button->setScale9Enabled(true);
    operateDiv->button->setCapInsets(Rect(0, 0, 53, 53));
    operateDiv->button->setContentSize(Size(operateSize, operateSize));
    operateDiv->button->setAnchorPoint(Point(0.5, 0.5));
    operateDiv->button->setPosition(Point(operateSize / 2, operateSize / 2));
    operateDiv->addChild(operateDiv->button, 0);

    auto iconOperateDiv = Sprite::create("res/IconDiv.png");
    iconOperateDiv->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperateDiv->setAnchorPoint(Point(0.5, 0.5));
    iconOperateDiv->setPosition(Point(operateSize / 2, operateSize / 2));
    operateDiv->button->addChild(iconOperateDiv, 0);

    return operateDiv;
}