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
        auto numberLeft = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        numberLeft->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        numberLeft->setAnchorPoint(Point(0.5, 0.5));
        numberLeft->setPosition(Point(leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(numberLeft, 0);
    
        auto oper = Scale9Sprite::create("res/IconFrame_Circle.png", Rect(0, 0, 118, 118), Rect(40, 40, 38, 36));
        oper->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        oper->setAnchorPoint(Point(0.5, 0.5));
        oper->setPosition(Point(leftWidth * 3 / 14 + leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(oper, 0);
    
        auto numberRight = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        numberRight->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        numberRight->setAnchorPoint(Point(0.5, 0.5));
        numberRight->setPosition(Point(leftWidth * 6 / 14 + leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(numberRight, 0);
    
        auto equal = Label::createWithTTF("=", "fonts/arial.ttf", leftWidth * 2 / 14 * showProp);
        equal->setAnchorPoint(Point(0.5, 0.5));
        equal->setPosition(Point(leftWidth * 9 / 14 + leftWidth * 2 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(equal, 0);
    
        auto numberResult = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        numberResult->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        numberResult->setAnchorPoint(Point(0.5, 0.5));
        numberResult->setPosition(Point(leftWidth * 11 / 14 + leftWidth * 3 / 14 / 2, (i + 1) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(numberResult, 0);
    }

    // add number block
    for (int i = 0; i < 4; i++) {
        auto numberBlock = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        numberBlock->setContentSize(Size(leftWidth / 4 * showProp, leftWidth / 4 * showProp));
        numberBlock->setAnchorPoint(Point(0.5, 0.5));
        numberBlock->setPosition(Point(leftWidth * i / 4 + leftWidth / 4 / 2, height / 4 / 2));
        solutionBoard->addChild(numberBlock, 0);
    }

    float rightWidth = width - leftWidth;
    auto operateSize = MIN(rightWidth, height / 4) * showProp;

    // add operate +
    auto operatePlusBtn = Button::create("res/BgOperatePlus.png", "res/BgOperatePlus_Pressed.png");
    operatePlusBtn->setScale9Enabled(true);
    operatePlusBtn->setCapInsets(Rect(0, 0, 53, 53));
    operatePlusBtn->setContentSize(Size(operateSize, operateSize));
    operatePlusBtn->setAnchorPoint(Point(0.5, 0.5));
    operatePlusBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 3 / 4 + height / 4 / 2));
    auto textOperatePlus = Label::createWithTTF("＋", "fonts/DefaultFont.ttf", operateSize);
    textOperatePlus->setTextColor(Colors::BgColor);
    textOperatePlus->setAnchorPoint(Point(0.5, 0.5));
    textOperatePlus->setPosition(Point(operatePlusBtn->getContentSize().width / 2, operatePlusBtn->getContentSize().height / 2));
    operatePlusBtn->addChild(textOperatePlus, 0);
    solutionBoard->addChild(operatePlusBtn, 0);

    // add operate -
    auto operateMinusBtn = Button::create("res/BgOperateMinus.png", "res/BgOperateMinus_Pressed.png");
    operateMinusBtn->setScale9Enabled(true);
    operateMinusBtn->setCapInsets(Rect(0, 0, 53, 53));
    operateMinusBtn->setContentSize(Size(operateSize, operateSize));
    operateMinusBtn->setAnchorPoint(Point(0.5, 0.5));
    operateMinusBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 2 / 4 + height / 4 / 2));
    auto textOperateMinus = Label::createWithTTF("－", "fonts/DefaultFont.ttf", operateSize);
    textOperateMinus->setTextColor(Colors::BgColor);
    textOperateMinus->setAnchorPoint(Point(0.5, 0.5));
    textOperateMinus->setPosition(Point(operateMinusBtn->getContentSize().width / 2, operateMinusBtn->getContentSize().height / 2));
    operateMinusBtn->addChild(textOperateMinus, 0);
    solutionBoard->addChild(operateMinusBtn, 0);

    // add operate x
    auto operateMultBtn = Button::create("res/BgOperateMult.png", "res/BgOperateMult_Pressed.png");
    operateMultBtn->setScale9Enabled(true);
    operateMultBtn->setCapInsets(Rect(0, 0, 53, 53));
    operateMultBtn->setContentSize(Size(operateSize, operateSize));
    operateMultBtn->setAnchorPoint(Point(0.5, 0.5));
    operateMultBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 1 / 4 + height / 4 / 2));
    auto textOperateMult = Label::createWithTTF("×", "fonts/DefaultFont.ttf", operateSize);
    textOperateMult->setTextColor(Colors::BgColor);
    textOperateMult->setAnchorPoint(Point(0.5, 0.5));
    textOperateMult->setPosition(Point(operateMultBtn->getContentSize().width / 2, operateMultBtn->getContentSize().height / 2));
    operateMultBtn->addChild(textOperateMult, 0);
    solutionBoard->addChild(operateMultBtn, 0);

    // add operate /
    auto operateDivBtn = Button::create("res/BgOperateDiv.png", "res/BgOperateDiv_Pressed.png");
    operateDivBtn->setScale9Enabled(true);
    operateDivBtn->setCapInsets(Rect(0, 0, 53, 53));
    operateDivBtn->setContentSize(Size(operateSize, operateSize));
    operateDivBtn->setAnchorPoint(Point(0.5, 0.5));
    operateDivBtn->setPosition(Point(leftWidth + rightWidth / 2, height / 4 / 2));
    auto textOperateDiv = Label::createWithTTF("÷", "fonts/DefaultFont.ttf", operateSize);
    textOperateDiv->setTextColor(Colors::BgColor);
    textOperateDiv->setAnchorPoint(Point(0.5, 0.5));
    textOperateDiv->setPosition(Point(operateDivBtn->getContentSize().width / 2, operateDivBtn->getContentSize().height / 2));
    operateDivBtn->addChild(textOperateDiv, 0);
    solutionBoard->addChild(operateDivBtn, 0);

    return solutionBoard;
}