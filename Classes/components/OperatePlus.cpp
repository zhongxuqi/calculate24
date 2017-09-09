#include "SimpleAudioEngine.h"
#include "OperatePlus.h"

USING_NS_CC;
using namespace ui;

bool OperatePlus::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

OperatePlus* OperatePlus::create(float operateSize) {
    auto operatePlus = OperatePlus::create();
    operatePlus->setContentSize(Size(operateSize, operateSize));
    operatePlus->setIgnoreAnchorPointForPosition(false);
    operatePlus->operatorTxt = '+';

    operatePlus->button = Button::create("res/BgOperatePlus.png", "res/BgOperatePlus_Pressed.png");
    operatePlus->button->setContentSize(Size(operateSize, operateSize));
    operatePlus->button->setScale9Enabled(true);
    operatePlus->button->setCapInsets(Rect(0, 0, 53, 53));
    operatePlus->button->setContentSize(Size(operateSize, operateSize));
    operatePlus->button->setAnchorPoint(Point(0.5, 0.5));
    operatePlus->button->setPosition(Point(operateSize / 2, operateSize / 2));
    operatePlus->addChild(operatePlus->button, 0);

    auto iconOperatePlus = Sprite::create("res/IconPlus.png");
    iconOperatePlus->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperatePlus->setAnchorPoint(Point(0.5, 0.5));
    iconOperatePlus->setPosition(Point(operateSize / 2, operateSize / 2));
    operatePlus->button->addChild(iconOperatePlus, 0);

    return operatePlus;
}