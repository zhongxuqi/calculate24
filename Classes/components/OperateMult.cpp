#include "SimpleAudioEngine.h"
#include "OperateMult.h"

USING_NS_CC;
using namespace ui;

bool OperateMult::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

OperateMult* OperateMult::create(float operateSize) {
    auto operateMult = OperateMult::create();
    operateMult->setContentSize(Size(operateSize, operateSize));
    operateMult->setIgnoreAnchorPointForPosition(false);
    operateMult->operatorTxt = '*';

    operateMult->button = Button::create("res/BgOperateMult.png", "res/BgOperateMult_Pressed.png");
    operateMult->button->setContentSize(Size(operateSize, operateSize));
    operateMult->button->setScale9Enabled(true);
    operateMult->button->setCapInsets(Rect(0, 0, 53, 53));
    operateMult->button->setContentSize(Size(operateSize, operateSize));
    operateMult->button->setAnchorPoint(Point(0.5, 0.5));
    operateMult->button->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMult->addChild(operateMult->button, 0);

    auto iconOperateMult = Sprite::create("res/IconMult.png");
    iconOperateMult->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperateMult->setAnchorPoint(Point(0.5, 0.5));
    iconOperateMult->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMult->button->addChild(iconOperateMult, 0);

    return operateMult;
}