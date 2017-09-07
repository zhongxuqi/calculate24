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

    auto operateMultBtn = Button::create("res/BgOperateMult.png", "res/BgOperateMult_Pressed.png");
    operateMultBtn->setContentSize(Size(operateSize, operateSize));
    operateMultBtn->setScale9Enabled(true);
    operateMultBtn->setCapInsets(Rect(0, 0, 53, 53));
    operateMultBtn->setContentSize(Size(operateSize, operateSize));
    operateMultBtn->setAnchorPoint(Point(0.5, 0.5));
    operateMultBtn->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMult->addChild(operateMultBtn, 0);

    auto iconOperateMult = Sprite::create("res/IconMult.png");
    iconOperateMult->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperateMult->setAnchorPoint(Point(0.5, 0.5));
    iconOperateMult->setPosition(Point(operateSize / 2, operateSize / 2));
    operateMultBtn->addChild(iconOperateMult, 0);

    return operateMult;
}