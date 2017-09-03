#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/Colors.h"

USING_NS_CC;

NumberBlock::NumberBlock(int number): Number(number), BaseComponent(LayerColor::create()) {
    
}

NumberBlock* NumberBlock::create(float width, int number) {
    auto numberBlock = new NumberBlock(number);
    numberBlock->RootNode->setContentSize(Size(width, width));
    numberBlock->RootNode->ignoreAnchorPointForPosition(false);

    auto strokeWidth = width / 30;
    if (strokeWidth < 1) {
        strokeWidth = 1;
    }
    auto halfStrokeWidth = strokeWidth / 2;
    if (halfStrokeWidth < 1) {
        halfStrokeWidth = 0;
    }

    // add background
    numberBlock->NodeBackground = DrawNode::create();
    Vec2 *points = new Vec2[4]{
        Vec2(halfStrokeWidth, halfStrokeWidth),
        Vec2(width - halfStrokeWidth, halfStrokeWidth),
        Vec2(width - halfStrokeWidth, width - halfStrokeWidth),
        Vec2(halfStrokeWidth, width - halfStrokeWidth),
    };
    numberBlock->NodeBackground->drawPolygon(points, 4, Color4F(0, 0, 0, 0), strokeWidth, Color4F(Colors::GetColorsByNumber(numberBlock->Number)));
    numberBlock->RootNode->addChild(numberBlock->NodeBackground, 0);

    // add number
    std::stringstream ss;
    ss << number;
    numberBlock->NodeNumber = Label::createWithTTF(ss.str(), "fonts/arial.ttf", 30);
    numberBlock->NodeNumber->setAnchorPoint(Point(0.5, 0.5));
    numberBlock->NodeNumber->setPosition(width / 2, width / 2);
    numberBlock->NodeNumber->setTextColor(Colors::GetColorsByNumber(numberBlock->Number));
    numberBlock->RootNode->addChild(numberBlock->NodeNumber, 0);

    return numberBlock;
}