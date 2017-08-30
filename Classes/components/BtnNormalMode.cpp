#include "SimpleAudioEngine.h"
#include "BtnNormalMode.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

BtnNormalMode::BtnNormalMode() {
    
}

BtnNormalMode* BtnNormalMode::create(float width, float height) {
    auto btnNormalMode = new BtnNormalMode();
    btnNormalMode->RootLayer->setContentSize(Size(width, height));
    btnNormalMode->RootLayer->ignoreAnchorPointForPosition(false);
    auto btnSize = btnNormalMode->RootLayer->getContentSize();

    // add sprite
    auto btnBg = Scale9Sprite::create("BgNormalMode.png", Rect(0, 0, 162, 123));
    btnBg->setContentSize(btnNormalMode->RootLayer->getContentSize());
    btnBg->setAnchorPoint(Point(0, 0));
    btnNormalMode->RootLayer->addChild(btnBg, 0);

    // add label
    auto btnText = Label::createWithTTF("Normal Mode", "default_font.ttf", 30);
    btnText->setAnchorPoint(Point(0.5, 1));
    btnText->setPosition(Point(btnSize.width / 2, btnSize.height - 20));
    btnText->setTextColor(Color4B::WHITE);
    btnNormalMode->RootLayer->addChild(btnText, 0);

    return btnNormalMode;
}