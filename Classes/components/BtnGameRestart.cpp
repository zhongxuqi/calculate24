#include "SimpleAudioEngine.h"
#include "BtnGameRestart.h"
#include "../base/Colors.h"

USING_NS_CC;

BtnGameRestart::BtnGameRestart(): borderWidth(4) {

}

bool BtnGameRestart::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

BtnGameRestart* BtnGameRestart::create(float width, float height) {
    auto btnGameRestart = BtnGameRestart::create();
    btnGameRestart->setContentSize(Size(width, height));
    btnGameRestart->setIgnoreAnchorPointForPosition(false);

    // add background
    btnGameRestart->NodeBackground = DrawNode::create();
    btnGameRestart->points = new Vec2[4]{
        Vec2(0, 0),
        Vec2(width, 0),
        Vec2(width, height),
        Vec2(0, height),
    };
    btnGameRestart->NodeBackground->drawPolygon(btnGameRestart->points, 4, Color4F(Colors::Transparent), \
        btnGameRestart->borderWidth, Color4F(Colors::SuccessColor));
    btnGameRestart->addChild(btnGameRestart->NodeBackground, 0);

    // add text
    btnGameRestart->textLabel = Label::createWithTTF("Restart", "fonts/arial.ttf", height * 0.7);
    btnGameRestart->textLabel->enableBold();
    btnGameRestart->textLabel->setAnchorPoint(Point(0.5, 0.5));
    btnGameRestart->textLabel->setPosition(width / 2, height / 2);
    btnGameRestart->textLabel->setTextColor(Colors::SuccessColor);
    btnGameRestart->addChild(btnGameRestart->textLabel, 0);

    // add event listener
    btnGameRestart->eventListener = EventListenerTouchOneByOne::create();
    btnGameRestart->eventListener->onTouchBegan = CC_CALLBACK_2(BtnGameRestart::onTouchBegan, btnGameRestart);
    btnGameRestart->eventListener->onTouchMoved = CC_CALLBACK_2(BtnGameRestart::onTouchMoved, btnGameRestart);
    btnGameRestart->eventListener->onTouchEnded = CC_CALLBACK_2(BtnGameRestart::onTouchEnded, btnGameRestart);
    btnGameRestart->eventListener->setSwallowTouches(true);
    btnGameRestart->_eventDispatcher->addEventListenerWithSceneGraphPriority(btnGameRestart->eventListener, btnGameRestart);

    return btnGameRestart;
}

void BtnGameRestart::setActive(bool isActive) {
    this->NodeBackground->clear();
    if (isActive) {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::SuccessColor), this->borderWidth, Color4F(Colors::SuccessColor));
        this->textLabel->setTextColor(Colors::BgColor);
    } else {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, Color4F(Colors::SuccessColor));
        this->textLabel->setTextColor(Colors::SuccessColor);
    }
}

bool BtnGameRestart::onTouchBegan(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        this->setActive(true);
        return true;
    }
    return false;
}

void BtnGameRestart::onTouchMoved(Touch *touch, Event *unused_event) {
    
}

void BtnGameRestart::onTouchEnded(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        if (this->clickListener != NULL) {
            this->clickListener();
        }
    }
    this->setActive(false);
}

void BtnGameRestart::SetOnClickListener(std::function<void()> listener) {
    this->clickListener = listener;
}