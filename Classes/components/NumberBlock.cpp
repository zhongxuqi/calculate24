#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/Colors.h"

USING_NS_CC;

bool NumberBlock::init() {
    if (!Layer::init()) {
        return false;
    }
    this->activeState = false;
    this->visible = true;
    return true;
}

NumberBlock* NumberBlock::create(float width, AccurateNumber *accurateNumber) {
    auto numberBlock = NumberBlock::create();
    numberBlock->accurateNumber = new AccurateNumber{};
    numberBlock->accurateNumber->value = accurateNumber->value;
    numberBlock->accurateNumber->divider = accurateNumber->divider;
    numberBlock->setContentSize(Size(width, width));
    numberBlock->setIgnoreAnchorPointForPosition(false);

    numberBlock->borderWidth = width / 30;
    if (numberBlock->borderWidth < 1) {
        numberBlock->borderWidth = 1;
    }
    auto halfStrokeWidth = numberBlock->borderWidth / 2;
    if (halfStrokeWidth < 1) {
        halfStrokeWidth = 0;
    }

    // add background
    numberBlock->NodeBackground = DrawNode::create();
    numberBlock->points = new Vec2[4]{
        Vec2(halfStrokeWidth, halfStrokeWidth),
        Vec2(width - halfStrokeWidth, halfStrokeWidth),
        Vec2(width - halfStrokeWidth, width - halfStrokeWidth),
        Vec2(halfStrokeWidth, width - halfStrokeWidth),
    };
    numberBlock->NodeBackground->drawPolygon(numberBlock->points, 4, Color4F(Colors::Transparent), \
        numberBlock->borderWidth, Color4F(Colors::GetColorsByNumber(numberBlock->accurateNumber)));
    numberBlock->addChild(numberBlock->NodeBackground, 0);

    // add number
    std::stringstream numberStr;
    numberStr << numberBlock->accurateNumber->value;
    if (numberBlock->accurateNumber->divider != 1) {
        numberStr << '/' << numberBlock->accurateNumber->divider;
    }
    numberBlock->NodeNumber = Label::createWithTTF(numberStr.str(), "fonts/arial.ttf", width / 2);
    numberBlock->NodeNumber->enableBold();
    numberBlock->NodeNumber->setAnchorPoint(Point(0.5, 0.5));
    numberBlock->NodeNumber->setPosition(width / 2, width / 2);
    numberBlock->NodeNumber->setTextColor(Colors::GetColorsByNumber(numberBlock->accurateNumber));
    numberBlock->addChild(numberBlock->NodeNumber, 0);

    // add event listener
    numberBlock->eventListener = EventListenerTouchOneByOne::create();
    numberBlock->eventListener->onTouchBegan = CC_CALLBACK_2(NumberBlock::onTouchBegan, numberBlock);
    numberBlock->eventListener->onTouchMoved = CC_CALLBACK_2(NumberBlock::onTouchMoved, numberBlock);
    numberBlock->eventListener->onTouchEnded = CC_CALLBACK_2(NumberBlock::onTouchEnded, numberBlock);
    numberBlock->eventListener->setSwallowTouches(true);
    numberBlock->_eventDispatcher->addEventListenerWithSceneGraphPriority(numberBlock->eventListener, numberBlock);

    return numberBlock;
}

void NumberBlock::SetActiveState(bool isActive) {
    this->NodeBackground->clear();
    this->activeState = isActive;
    if (this->activeState) {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::GetColorsByNumber(this->accurateNumber)), \
            this->borderWidth, Color4F(Colors::GetColorsByNumber(this->accurateNumber)));
        this->NodeNumber->setTextColor(Colors::BgColor);
    } else {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, \
            Color4F(Colors::GetColorsByNumber(this->accurateNumber)));
        this->NodeNumber->setTextColor(Colors::GetColorsByNumber(this->accurateNumber));
    }
}

bool NumberBlock::IsActive() {
    return this->activeState;
}

AccurateNumber *NumberBlock::GetNumber() {
    return this->accurateNumber;
}

void NumberBlock::SetNumber(AccurateNumber *accurateNumber) {
    if (this->accurateNumber != NULL) {
        delete this->accurateNumber;
    }
    this->accurateNumber = new AccurateNumber{};
    this->accurateNumber->value = accurateNumber->value;
    this->accurateNumber->divider = accurateNumber->divider;
    std::stringstream numberStr;
    numberStr << this->accurateNumber->value;
    if (this->accurateNumber->divider != 1) {
        numberStr << '/' << this->accurateNumber->divider;
    }
    this->NodeNumber->setString(numberStr.str());
    this->NodeNumber->setTextColor(Colors::GetColorsByNumber(this->accurateNumber));
    this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, \
    Color4F(Colors::GetColorsByNumber(this->accurateNumber)));
}

bool NumberBlock::onTouchBegan(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        if (this->clickListener != NULL) {
            return true;
        }
    }
    return false;
}

void NumberBlock::onTouchMoved(Touch *touch, Event *unused_event) {
    
}

void NumberBlock::onTouchEnded(Touch *touch, Event *unused_event) {
    auto locationOnView = this->convertToNodeSpace(touch->getLocation());
    if (locationOnView.x > 0 && locationOnView.x < this->getContentSize().width && \
    locationOnView.y > 0 && locationOnView.y < this->getContentSize().height) {
        if (this->clickListener != NULL) {
            this->clickListener(unused_event->getCurrentTarget());
        }
    }
    this->clickListener(unused_event->getCurrentTarget());
}

void NumberBlock::SetOnClickListener(std::function<void(cocos2d::Node*)> listener) {
    this->clickListener = listener;
}