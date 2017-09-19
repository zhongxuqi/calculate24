#include "SimpleAudioEngine.h"
#include "BtnGameResume.h"
#include "../base/Colors.h"

USING_NS_CC;

BtnGameResume::BtnGameResume(): borderWidth(4) {

}

bool BtnGameResume::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

BtnGameResume* BtnGameResume::create(float width, float height) {
    auto btnGameResume = BtnGameResume::create();
    btnGameResume->setContentSize(Size(width, height));
    btnGameResume->setIgnoreAnchorPointForPosition(false);

    // add background
    btnGameResume->NodeBackground = DrawNode::create();
    btnGameResume->points = new Vec2[4]{
        Vec2(0, 0),
        Vec2(width, 0),
        Vec2(width, height),
        Vec2(0, height),
    };
    btnGameResume->NodeBackground->drawPolygon(btnGameResume->points, 4, Color4F(Colors::Transparent), \
        btnGameResume->borderWidth, Color4F(Colors::SuccessColor));
    btnGameResume->addChild(btnGameResume->NodeBackground, 0);

    // add text
    btnGameResume->textLabel = Label::createWithTTF("Next", "fonts/arial.ttf", height * 0.7);
    btnGameResume->textLabel->enableBold();
    btnGameResume->textLabel->setAnchorPoint(Point(0.5, 0.5));
    btnGameResume->textLabel->setPosition(width / 2, height / 2);
    btnGameResume->textLabel->setTextColor(Colors::SuccessColor);
    btnGameResume->addChild(btnGameResume->textLabel, 0);

    // add event listener
    btnGameResume->eventListener = EventListenerTouchOneByOne::create();
    btnGameResume->eventListener->onTouchBegan = CC_CALLBACK_2(BtnGameResume::onTouchBegan, btnGameResume);
    btnGameResume->eventListener->onTouchMoved = CC_CALLBACK_2(BtnGameResume::onTouchMoved, btnGameResume);
    btnGameResume->eventListener->onTouchEnded = CC_CALLBACK_2(BtnGameResume::onTouchEnded, btnGameResume);
    btnGameResume->eventListener->setSwallowTouches(true);
    btnGameResume->_eventDispatcher->addEventListenerWithSceneGraphPriority(btnGameResume->eventListener, btnGameResume);

    return btnGameResume;
}

void BtnGameResume::setActive(bool isActive) {
    this->NodeBackground->clear();
    if (isActive) {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::SuccessColor), this->borderWidth, Color4F(Colors::SuccessColor));
        this->textLabel->setTextColor(Colors::BgColor);
    } else {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, Color4F(Colors::SuccessColor));
        this->textLabel->setTextColor(Colors::SuccessColor);
    }
}

bool BtnGameResume::onTouchBegan(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        this->setActive(true);
        return true;
    }
    return false;
}

void BtnGameResume::onTouchMoved(Touch *touch, Event *unused_event) {
    
}

void BtnGameResume::onTouchEnded(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        if (this->clickListener != NULL) {
            this->clickListener();
        }
    }
    this->setActive(false);
}

void BtnGameResume::SetOnClickListener(std::function<void()> listener) {
    this->clickListener = listener;
}