#include "SimpleAudioEngine.h"
#include "BtnOnlineBattle.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

bool BtnOnlineBattle::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

BtnOnlineBattle* BtnOnlineBattle::create(float width, float height) {
    auto btnOnlineBattle = BtnOnlineBattle::create();
    btnOnlineBattle->setContentSize(Size(width, height));
    btnOnlineBattle->ignoreAnchorPointForPosition(false);
    auto btnSize = btnOnlineBattle->getContentSize();

    // add Button
    btnOnlineBattle->button = ui::Button::create("res/BgOnlineBattleBtn.png", "res/BgOnlineBattleBtn_Pressed.png");
    btnOnlineBattle->button->setScale9Enabled(true);
    btnOnlineBattle->button->setContentSize(btnSize);
    btnOnlineBattle->button->setAnchorPoint(Point(0, 0));
    btnOnlineBattle->button->setPosition(Point(0, 0));
    btnOnlineBattle->addChild(btnOnlineBattle->button, 0);

    // add label
    auto btnText = Label::createWithTTF("Online Battle", "fonts/arial.ttf", height / 7);
    btnText->setAnchorPoint(Point(0.5, 1));
    btnText->setPosition(Point(btnSize.width / 2, btnSize.height - 20));
    btnText->setTextColor(Color4B::WHITE);
    btnOnlineBattle->button->addChild(btnText, 0);

    // add icon
    auto btnIcon = Sprite::create("res/Battle.png");
    btnIcon->setAnchorPoint(Point(0.5, 0));
    btnIcon->setScale(0.8 * (btnOnlineBattle->button->getContentSize().height - btnText->getContentSize().height - 40) / btnIcon->getContentSize().height);
    btnIcon->setPosition(Point(btnSize.width / 2, 20));
    btnOnlineBattle->button->addChild(btnIcon, 0);

    return btnOnlineBattle;
}