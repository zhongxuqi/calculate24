#include "SimpleAudioEngine.h"
#include "BtnGameJudge.h"
#include "../base/Colors.h"

USING_NS_CC;

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
    btnGameJudge->color = Colors::DangerColor;
    btnGameJudge->NodeBackground = DrawNode::create();
    btnGameJudge->points = new Vec2[4]{
        Vec2(0, 0),
        Vec2(width, 0),
        Vec2(width, height),
        Vec2(0, height),
    };
    btnGameJudge->NodeBackground->drawPolygon(btnGameJudge->points, 4, Color4F(Colors::Transparent), \
        btnGameJudge->borderWidth, Color4F(btnGameJudge->color));
    btnGameJudge->addChild(btnGameJudge->NodeBackground, 0);

    // add text
    btnGameJudge->textLabel = Label::createWithTTF("Over", "fonts/arial.ttf", height / 2);
    btnGameJudge->textLabel->enableBold();
    btnGameJudge->textLabel->setAnchorPoint(Point(0.5, 0.5));
    btnGameJudge->textLabel->setPosition(width / 2, height / 2);
    btnGameJudge->textLabel->setTextColor(btnGameJudge->color);
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

void BtnGameJudge::setActive(bool isActive) {
    this->NodeBackground->clear();
    if (isActive) {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(this->color), this->borderWidth, Color4F(this->color));
        this->textLabel->setTextColor(Colors::BgColor);
    } else {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, Color4F(this->color));
        this->textLabel->setTextColor(this->color);
    }
}

bool BtnGameJudge::onTouchBegan(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        this->setActive(true);
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
    this->setActive(false);
}

void BtnGameJudge::SetOnClickListener(std::function<void()> listener) {
    this->clickListener = listener;
}

void BtnGameJudge::SetPassState(bool passState) {
    this->passState = passState;
    if (passState) {
        this->color = Colors::SuccessColor;
        this->textLabel->setString("Level Up");
    } else {
        this->color = Colors::DangerColor;
        this->textLabel->setString("Over");
    }
    this->setActive(false);
}

bool BtnGameJudge::IsPass() {
    return this->passState;
}