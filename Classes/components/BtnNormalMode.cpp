#include "SimpleAudioEngine.h"
#include "BtnNormalMode.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

BtnNormalMode::BtnNormalMode(): BaseComponent(LayerColor::create()) {
    
}

BtnNormalMode* BtnNormalMode::create(float width, float height) {
    auto btnNormalMode = new BtnNormalMode();
    btnNormalMode->RootNode->setContentSize(Size(width, height));
    btnNormalMode->RootNode->ignoreAnchorPointForPosition(false);
    auto btnSize = btnNormalMode->RootNode->getContentSize();

    // add Button
    btnNormalMode->button = ui::Button::create("res/BgNormalModeBtn.png", "res/BgNormalModeBtn_Pressed.png");
    btnNormalMode->button->setScale9Enabled(true);
    btnNormalMode->button->setContentSize(btnSize);
    btnNormalMode->button->setAnchorPoint(Point(0, 0));
    btnNormalMode->button->setPosition(Point(0, 0));
    btnNormalMode->RootNode->addChild(btnNormalMode->button, 0);

    // add label
    auto btnText = Label::createWithTTF("Normal Mode", "fonts/arial.ttf", 60);
    btnText->setAnchorPoint(Point(0.5, 1));
    btnText->setPosition(Point(btnSize.width / 2, btnSize.height - 20));
    btnText->setTextColor(Color4B::WHITE);
    btnNormalMode->button->addChild(btnText, 0);

    // add icon
    auto btnIcon = Sprite::create("res/Star_White.png");
    btnIcon->setAnchorPoint(Point(0.5, 0));
    btnIcon->setScale(0.8 * (btnNormalMode->button->getContentSize().height - btnText->getContentSize().height - 40) / btnIcon->getContentSize().height);
    btnIcon->setPosition(Point(btnSize.width / 2, 20));
    btnNormalMode->button->addChild(btnIcon, 0);

    return btnNormalMode;
}

void BtnNormalMode::SetOnClickListener(std::function<void(Ref*)> clickListener) {
    this->button->addClickEventListener(clickListener);
}