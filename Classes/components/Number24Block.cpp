#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/Colors.h"
#include "Number24Block.h"

USING_NS_CC;

bool Number24Block::init() {
    if (!Layer::init()) {
        return false;
    }
    this->currColor = Colors::Number24DefaultColor;
    return true;
}

Number24Block* Number24Block::create(float width) {
    auto number24Block = Number24Block::create();
    number24Block->setContentSize(Size(width, width));
    number24Block->setIgnoreAnchorPointForPosition(false);

    number24Block->borderWidth = width / 30;
    if (number24Block->borderWidth < 1) {
        number24Block->borderWidth = 1;
    }
    auto halfStrokeWidth = number24Block->borderWidth / 2;
    if (halfStrokeWidth < 1) {
        halfStrokeWidth = 0;
    }

    // add background
    number24Block->NodeBackground = DrawNode::create();
    number24Block->points = new Vec2[4]{
        Vec2(halfStrokeWidth, halfStrokeWidth),
        Vec2(width - halfStrokeWidth, halfStrokeWidth),
        Vec2(width - halfStrokeWidth, width - halfStrokeWidth),
        Vec2(halfStrokeWidth, width - halfStrokeWidth),
    };
    number24Block->NodeBackground->drawPolygon(number24Block->points, 4, Color4F(number24Block->currColor), \
        number24Block->borderWidth, Color4F(number24Block->currColor));
    number24Block->addChild(number24Block->NodeBackground, 0);

    // add number
    number24Block->NodeNumber = Label::createWithTTF("24", "fonts/arial.ttf", width / 2);
    number24Block->NodeNumber->enableBold();
    number24Block->NodeNumber->setAnchorPoint(Point(0.5, 0.5));
    number24Block->NodeNumber->setPosition(width / 2, width / 2);
    number24Block->NodeNumber->setTextColor(Colors::BgColor);
    number24Block->addChild(number24Block->NodeNumber, 0);

    return number24Block;
}

void Number24Block::CheckNumberResult(AccurateNumber *accurateNumber) {
    if (accurateNumber->value / accurateNumber->divider == 24 && accurateNumber->value % accurateNumber->divider == 0) {
        this->currColor = Colors::Number24SuccessColor;
    } else {
        this->currColor = Colors::Number24FailColor;
    }
    this->NodeBackground->clear();
    this->NodeBackground->drawPolygon(this->points, 4, Color4F(this->currColor), \
        this->borderWidth, Color4F(this->currColor));
}

void Number24Block::ResetColor() {
    this->currColor = Colors::Number24DefaultColor;
    this->NodeBackground->clear();
    this->NodeBackground->drawPolygon(this->points, 4, Color4F(this->currColor), \
        this->borderWidth, Color4F(this->currColor));
}