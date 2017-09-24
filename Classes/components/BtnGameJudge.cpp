#include "SimpleAudioEngine.h"
#include "BtnGameJudge.h"
#include "../base/Colors.h"

USING_NS_CC;
using namespace cocos2d::extension;

BtnGameJudge::BtnGameJudge(): borderWidth(4) {

}

bool BtnGameJudge::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

BtnGameJudge* BtnGameJudge::create(float width, float height) {
    auto btnGameJudge = BtnGameJudge::create();
    btnGameJudge->setContentSize(Size(width, height));
    btnGameJudge->setIgnoreAnchorPointForPosition(false);

    // add background
    btnGameJudge->NodeBackground = Scale9Sprite::create("res/BgButtonRed.png", Rect(0, 0, 208, 66), Rect(50, 20, 108, 26));
    btnGameJudge->NodeBackground->setContentSize(btnGameJudge->getContentSize());
    btnGameJudge->NodeBackground->setAnchorPoint(Point(0, 0));
    btnGameJudge->NodeBackground->setPosition(Point(width / 2, height / 2));
    btnGameJudge->addChild(btnGameJudge->NodeBackground, 0);

    // add text
    btnGameJudge->textLabel = Label::createWithTTF("Over", "fonts/arial.ttf", height / 2);
    btnGameJudge->textLabel->enableBold();
    btnGameJudge->textLabel->setAnchorPoint(Point(0.5, 0.5));
    btnGameJudge->textLabel->setPosition(width / 2, height / 2);
    btnGameJudge->textLabel->setTextColor(Colors::White);
    btnGameJudge->addChild(btnGameJudge->textLabel, 0);

    // add event listener
    btnGameJudge->eventListener = EventListenerTouchOneByOne::create();
    btnGameJudge->eventListener->onTouchBegan = CC_CALLBACK_2(BtnGameJudge::onTouchBegan, btnGameJudge);
    btnGameJudge->eventListener->onTouchMoved = CC_CALLBACK_2(BtnGameJudge::onTouchMoved, btnGameJudge);
    btnGameJudge->eventListener->onTouchEnded = CC_CALLBACK_2(BtnGameJudge::onTouchEnded, btnGameJudge);
    btnGameJudge->eventListener->setSwallowTouches(true);
    btnGameJudge->_eventDispatcher->addEventListenerWithSceneGraphPriority(btnGameJudge->eventListener, btnGameJudge);

    return btnGameJudge;
}

bool BtnGameJudge::onTouchBegan(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        return true;
    }
    return false;
}

void BtnGameJudge::onTouchMoved(Touch *touch, Event *unused_event) {
    
}

void BtnGameJudge::onTouchEnded(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        if (this->clickListener != NULL) {
            this->clickListener();
        }
    }
}

void BtnGameJudge::SetOnClickListener(std::function<void()> listener) {
    this->clickListener = listener;
}

void BtnGameJudge::SetPassState(bool passState) {
    this->passState = passState;
    if (passState) {
        this->color = Colors::SuccessColor;
        this->textLabel->setString("LevelUp");
        this->NodeBackground->initWithFile("res/BgButtonGreen.png", Rect(0, 0, 208, 66), Rect(50, 20, 108, 26));
        this->NodeBackground->setContentSize(this->getContentSize());
    } else {
        this->color = Colors::DangerColor;
        this->textLabel->setString("GiveUp");
        this->NodeBackground->initWithFile("res/BgButtonRed.png", Rect(0, 0, 208, 66), Rect(50, 20, 108, 26));
        this->NodeBackground->setContentSize(this->getContentSize());
    }
}

bool BtnGameJudge::IsPass() {
    return this->passState;
}