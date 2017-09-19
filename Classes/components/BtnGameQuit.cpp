#include "SimpleAudioEngine.h"
#include "BtnGameQuit.h"
#include "../base/Colors.h"

USING_NS_CC;

BtnGameQuit::BtnGameQuit(): borderWidth(4) {

}

bool BtnGameQuit::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

BtnGameQuit* BtnGameQuit::create(float width, float height) {
    auto btnGameQuit = BtnGameQuit::create();
    btnGameQuit->setContentSize(Size(width, height));
    btnGameQuit->setIgnoreAnchorPointForPosition(false);

    // add background
    btnGameQuit->NodeBackground = DrawNode::create();
    btnGameQuit->points = new Vec2[4]{
        Vec2(0, 0),
        Vec2(width, 0),
        Vec2(width, height),
        Vec2(0, height),
    };
    btnGameQuit->NodeBackground->drawPolygon(btnGameQuit->points, 4, Color4F(Colors::Transparent), \
        btnGameQuit->borderWidth, Color4F(Colors::DangerColor));
    btnGameQuit->addChild(btnGameQuit->NodeBackground, 0);

    // add text
    btnGameQuit->textLabel = Label::createWithTTF("Quit", "fonts/arial.ttf", height * 0.7);
    btnGameQuit->textLabel->enableBold();
    btnGameQuit->textLabel->setAnchorPoint(Point(0.5, 0.5));
    btnGameQuit->textLabel->setPosition(width / 2, height / 2);
    btnGameQuit->textLabel->setTextColor(Colors::DangerColor);
    btnGameQuit->addChild(btnGameQuit->textLabel, 0);

    // add event listener
    btnGameQuit->eventListener = EventListenerTouchOneByOne::create();
    btnGameQuit->eventListener->onTouchBegan = CC_CALLBACK_2(BtnGameQuit::onTouchBegan, btnGameQuit);
    btnGameQuit->eventListener->onTouchMoved = CC_CALLBACK_2(BtnGameQuit::onTouchMoved, btnGameQuit);
    btnGameQuit->eventListener->onTouchEnded = CC_CALLBACK_2(BtnGameQuit::onTouchEnded, btnGameQuit);
    btnGameQuit->eventListener->setSwallowTouches(true);
    btnGameQuit->_eventDispatcher->addEventListenerWithSceneGraphPriority(btnGameQuit->eventListener, btnGameQuit);

    return btnGameQuit;
}

void BtnGameQuit::setActive(bool isActive) {
    this->NodeBackground->clear();
    if (isActive) {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::DangerColor), this->borderWidth, Color4F(Colors::DangerColor));
        this->textLabel->setTextColor(Colors::BgColor);
    } else {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, Color4F(Colors::DangerColor));
        this->textLabel->setTextColor(Colors::DangerColor);
    }
}

bool BtnGameQuit::onTouchBegan(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        this->setActive(true);
        return true;
    }
    return false;
}

void BtnGameQuit::onTouchMoved(Touch *touch, Event *unused_event) {
    
}

void BtnGameQuit::onTouchEnded(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        if (this->clickListener != NULL) {
            this->clickListener();
        }
    }
    this->setActive(false);
}

void BtnGameQuit::SetOnClickListener(std::function<void()> listener) {
    this->clickListener = listener;
}