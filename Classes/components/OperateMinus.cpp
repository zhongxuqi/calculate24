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
    operateMinus->operatorTxt = '-';

    operateMinus->button = Button::create("res/BgOperateMinus.png", "res/BgOperateMinus_Pressed.png");
    operateMinus->button->setContentSize(Size(operateSize, operateSize));
    operateMinus->button->setScale9Enabled(true);
    operateMinus->button->setCapInsets(Rect(0, 0, 53, 53));
    operateMinus->button->setContentSize(Size(operateSize, operateSize));
    operateMinus->button->setAnchorPoint(Point(0.5, 0.5));
    operateMinus->button->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMinus->addChild(operateMinus->button, 0);

    auto iconOperateMinus = Sprite::create("res/IconMinus.png");
    iconOperateMinus->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperateMinus->setAnchorPoint(Point(0.5, 0.5));
    iconOperateMinus->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMinus->button->addChild(iconOperateMinus, 0);

    return operateMinus;
}