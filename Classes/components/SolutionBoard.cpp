#include "SimpleAudioEngine.h"
#include "SolutionBoard.h"
#include "../base/Colors.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

bool SolutionBoard::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

SolutionBoard* SolutionBoard::create(float width, float height) {
    auto solutionBoard = SolutionBoard::create();
    solutionBoard->setContentSize(Size(width, height));
    solutionBoard->setIgnoreAnchorPointForPosition(false);

    // add formula
    float leftWidth = width * 14 / 17, showProp = 0.7;
    for (int i = 0; i < 3; i++) {
        solutionBoard->numberLefts[i] = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        solutionBoard->numberLefts[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->numberLefts[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberLefts[i]->setPosition(Point(leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberLefts[i], 0);
    
        solutionBoard->operators[i] = Scale9Sprite::create("res/IconFrame_Circle.png", Rect(0, 0, 118, 118), Rect(40, 40, 38, 36));
        solutionBoard->operators[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->operators[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->operators[i]->setPosition(Point(leftWidth * 3 / 14 + leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->operators[i], 0);
    
        solutionBoard->numberRights[i] = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        solutionBoard->numberRights[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->numberRights[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberRights[i]->setPosition(Point(leftWidth * 6 / 14 + leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberRights[i], 0);
    
        auto equal = Label::createWithTTF("=", "fonts/arial.ttf", leftWidth * 2 / 14 * showProp);
        equal->setAnchorPoint(Point(0.5, 0.5));
        equal->setPosition(Point(leftWidth * 9 / 14 + leftWidth * 2 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(equal, 0);
    
        solutionBoard->numberResults[i] = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        solutionBoard->numberResults[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->numberResults[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberResults[i]->setPosition(Point(leftWidth * 11 / 14 + leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberResults[i], 0);
    }

    solutionBoard->numberSize = solutionBoard->numberLefts[0]->getContentSize().width;
    solutionBoard->operateSize = solutionBoard->operators[0]->getContentSize().width;

    // add number block
    for (int i = 0; i < 4; i++) {
        solutionBoard->numberFrames[i] = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        solutionBoard->numberFrames[i]->setContentSize(Size(solutionBoard->numberSize, solutionBoard->numberSize));
        solutionBoard->numberFrames[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberFrames[i]->setPosition(Point(leftWidth * i / 4 + leftWidth / 4 / 2, height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberFrames[i], 0);
    }

    float rightWidth = width - leftWidth;

    // add operate +
    solutionBoard->operatePlusBtn = OperatePlus::create(solutionBoard->operateSize);
    solutionBoard->operatePlusBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operatePlusBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 3 / 4 + height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operatePlusBtn, 0);

    // add operate -
    solutionBoard->operateMinusBtn = OperateMinus::create(solutionBoard->operateSize);
    solutionBoard->operateMinusBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operateMinusBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 2 / 4 + height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operateMinusBtn, 0);

    // add operate *
    solutionBoard->operateMultBtn = OperateMult::create(solutionBoard->operateSize);
    solutionBoard->operateMultBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operateMultBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 1 / 4 + height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operateMultBtn, 0);

    // add operate /
    solutionBoard->operateDivBtn = OperateDiv::create(solutionBoard->operateSize);
    solutionBoard->operateDivBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operateDivBtn->setPosition(Point(leftWidth + rightWidth / 2, height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operateDivBtn, 0);

    return solutionBoard;
}

void SolutionBoard::InitNumber(int numbers[4]) {
    for (int i = 0; i < 4; i++) {
        this->numberBlocks[i] = NumberBlock::create(this->numberFrames[i]->getContentSize().width, numbers[i]);
        this->numberBlocks[i]->setAnchorPoint(Point(0.5, 0.5));
        this->numberBlocks[i]->setPosition(this->numberFrames[i]->getPosition());
        this->numberBlocks[i]->SetActiveState(true);
        this->addChild(this->numberBlocks[i], 0);
    }
}