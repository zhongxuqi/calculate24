#include "SimpleAudioEngine.h"
#include "OperateMinus.h"

USING_NS_CC;
using namespace ui;

bool OperateMinus::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

OperateMinus* OperateMinus::create(float operateSize) {
    auto operateMinus = OperateMinus::create();
    operateMinus->setContentSize(Size(operateSize, operateSize));
    operateMinus->setIgnoreAnchorPointForPosition(false);

    auto operateMinusBtn = Button::create("res/BgOperateMinus.png", "res/BgOperateMinus_Pressed.png");
    operateMinusBtn->setContentSize(Size(operateSize, operateSize));
    operateMinusBtn->setScale9Enabled(true);
    operateMinusBtn->setCapInsets(Rect(0, 0, 53, 53));
    operateMinusBtn->setContentSize(Size(operateSize, operateSize));
    operateMinusBtn->setAnchorPoint(Point(0.5, 0.5));
    operateMinusBtn->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMinus->addChild(operateMinusBtn, 0);

    auto iconOperateMinus = Sprite::create("res/IconMinus.png");
    iconOperateMinus->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperateMinus->setAnchorPoint(Point(0.5, 0.5));
    iconOperateMinus->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMinusBtn->addChild(iconOperateMinus, 0);

    return operateMinus;
}