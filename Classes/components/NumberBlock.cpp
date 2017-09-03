#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/Colors.h"

USING_NS_CC;

NumberBlock::NumberBlock(int number): Number(number) {
    this->activeState = false;
}

NumberBlock* NumberBlock::create(float width, int number) {
    auto numberBlock = new NumberBlock(number);
    numberBlock->setContentSize(Size(width, width));
    numberBlock->ignoreAnchorPointForPosition(false);

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
        numberBlock->borderWidth, Color4F(Colors::GetColorsByNumber(numberBlock->Number)));
    numberBlock->addChild(numberBlock->NodeBackground, 0);

    // add number
    std::stringstream ss;
    ss << number;
    numberBlock->NodeNumber = Label::createWithTTF(ss.str(), "fonts/arial.ttf", 40);
    numberBlock->NodeNumber->enableBold();
    numberBlock->NodeNumber->setAnchorPoint(Point(0.5, 0.5));
    numberBlock->NodeNumber->setPosition(width / 2, width / 2);
    numberBlock->NodeNumber->setTextColor(Colors::GetColorsByNumber(numberBlock->Number));
    numberBlock->addChild(numberBlock->NodeNumber, 0);

    return numberBlock;
}

void NumberBlock::SetActiveState(bool isActive) {
    this->NodeBackground->clear();
    this->activeState = isActive;
    if (this->activeState) {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::GetColorsByNumber(this->Number)), \
            this->borderWidth, Color4F(Colors::GetColorsByNumber(this->Number)));
        this->NodeNumber->setTextColor(Colors::BgColor);
    } else {
        this->NodeBackground->drawPolygon(this->points, 4, Color4F(Colors::Transparent), this->borderWidth, \
            Color4F(Colors::GetColorsByNumber(this->Number)));
        this->NodeNumber->setTextColor(Colors::GetColorsByNumber(this->Number));
    }
}

bool NumberBlock::IsActive() {
    return this->activeState;
}