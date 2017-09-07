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

    auto operatePlusBtn = Button::create("res/BgOperatePlus.png", "res/BgOperatePlus_Pressed.png");
    operatePlusBtn->setContentSize(Size(operateSize, operateSize));
    operatePlusBtn->setScale9Enabled(true);
    operatePlusBtn->setCapInsets(Rect(0, 0, 53, 53));
    operatePlusBtn->setContentSize(Size(operateSize, operateSize));
    operatePlusBtn->setAnchorPoint(Point(0.5, 0.5));
    operatePlusBtn->setPosition(Point(operateSize / 2, operateSize / 2));
    operatePlus->addChild(operatePlusBtn, 0);

    auto iconOperatePlus = Sprite::create("res/IconPlus.png");
    iconOperatePlus->setContentSize(Size(operateSize * 0.6, operateSize * 0.6));
    iconOperatePlus->setAnchorPoint(Point(0.5, 0.5));
    iconOperatePlus->setPosition(Point(operateSize / 2, operateSize / 2));
    operatePlusBtn->addChild(iconOperatePlus, 0);

    return operatePlus;
}