#include "SimpleAudioEngine.h"
#include "SolutionBoard.h"
#include "../base/Colors.h"
#include "../base/GameEngine.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

GameEngine* const gameEngine = GameEngine::Instance;

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
        solutionBoard->numberLefts[i]->setPosition(Point(leftWidth * 3 / 14 / 2, (3 - i) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberLefts[i], 0);
    
        solutionBoard->operators[i] = Scale9Sprite::create("res/IconFrame_Circle.png", Rect(0, 0, 118, 118), Rect(40, 40, 38, 36));
        solutionBoard->operators[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->operators[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->operators[i]->setPosition(Point(leftWidth * 3 / 14 + leftWidth * 3 / 14 / 2, (3 - i) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->operators[i], 0);
    
        solutionBoard->numberRights[i] = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        solutionBoard->numberRights[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->numberRights[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberRights[i]->setPosition(Point(leftWidth * 6 / 14 + leftWidth * 3 / 14 / 2, (3 - i) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberRights[i], 0);
    
        auto equal = Label::createWithTTF("=", "fonts/arial.ttf", leftWidth * 2 / 14 * showProp);
        equal->setAnchorPoint(Point(0.5, 0.5));
        equal->setPosition(Point(leftWidth * 9 / 14 + leftWidth * 2 / 14 / 2, (3 - i) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(equal, 0);
    
        solutionBoard->numberResults[i] = Scale9Sprite::create("res/IconFrame.png", Rect(0, 0, 76, 76), Rect(20, 20, 36, 36));
        solutionBoard->numberResults[i]->setContentSize(Size(leftWidth * 3 / 14 * showProp, leftWidth * 3 / 14 * showProp));
        solutionBoard->numberResults[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberResults[i]->setPosition(Point(leftWidth * 11 / 14 + leftWidth * 3 / 14 / 2, (3 - i) * height / 4 + height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberResults[i], 0);
    }

    solutionBoard->numberSize = solutionBoard->numberLefts[0]->getContentSize().width;
    solutionBoard->operateSize = solutionBoard->operators[0]->getContentSize().width;

    // add number frames
    for (int i = 0; i < 4; i++) {
        solutionBoard->numberFrames[i] = Button::create("res/IconFrame.png", "res/IconFrame.png");
        solutionBoard->numberFrames[i]->setCapInsets(Rect(20, 20, 36, 36));
        solutionBoard->numberFrames[i]->setContentSize(Size(solutionBoard->numberSize, solutionBoard->numberSize));
        solutionBoard->numberFrames[i]->setAnchorPoint(Point(0.5, 0.5));
        solutionBoard->numberFrames[i]->setPosition(Point(leftWidth * i / 4 + leftWidth / 4 / 2, height / 4 / 2));
        solutionBoard->addChild(solutionBoard->numberFrames[i], 0);
        solutionBoard->numberFrames[i]->addClickEventListener(CC_CALLBACK_1(SolutionBoard::onNumberClickListener, solutionBoard));
    }

    float rightWidth = width - leftWidth;

    // add operate +
    solutionBoard->operatePlusBtn = OperatePlus::create(solutionBoard->operateSize);
    solutionBoard->operatePlusBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operatePlusBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 3 / 4 + height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operatePlusBtn, 0);
    solutionBoard->operatePlusBtn->SetOnClickListener(CC_CALLBACK_1(SolutionBoard::onOperatorClickListener, solutionBoard));

    // add operate -
    solutionBoard->operateMinusBtn = OperateMinus::create(solutionBoard->operateSize);
    solutionBoard->operateMinusBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operateMinusBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 2 / 4 + height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operateMinusBtn, 0);
    solutionBoard->operateMinusBtn->SetOnClickListener(CC_CALLBACK_1(SolutionBoard::onOperatorClickListener, solutionBoard));

    // add operate *
    solutionBoard->operateMultBtn = OperateMult::create(solutionBoard->operateSize);
    solutionBoard->operateMultBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operateMultBtn->setPosition(Point(leftWidth + rightWidth / 2, height * 1 / 4 + height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operateMultBtn, 0);
    solutionBoard->operateMultBtn->SetOnClickListener(CC_CALLBACK_1(SolutionBoard::onOperatorClickListener, solutionBoard));

    // add operate /
    solutionBoard->operateDivBtn = OperateDiv::create(solutionBoard->operateSize);
    solutionBoard->operateDivBtn->setAnchorPoint(Point(0.5, 0.5));
    solutionBoard->operateDivBtn->setPosition(Point(leftWidth + rightWidth / 2, height / 4 / 2));
    solutionBoard->addChild(solutionBoard->operateDivBtn, 0);
    solutionBoard->operateDivBtn->SetOnClickListener(CC_CALLBACK_1(SolutionBoard::onOperatorClickListener, solutionBoard));

    return solutionBoard;
}

void SolutionBoard::InitNumber(AccurateNumber *accurateNumbers[4]) {
    for (int i = 0; i < 4; i++) {
        if (this->numberBlocks[i] != NULL) {
            this->removeChild(this->numberBlocks[i]);
        }

        this->numberBlocks[i] = NumberBlock::create(this->numberFrames[i]->getContentSize().width, accurateNumbers[i]);
        this->numberBlocks[i]->setAnchorPoint(Point(0.5, 0.5));
        this->numberBlocks[i]->setPosition(this->numberFrames[i]->getPosition());
        this->numberBlocks[i]->SetActiveState(true);
        this->addChild(this->numberBlocks[i], 0);
    }
    this->currLine = 0;
    this->currIndex = 0;
    for (int i = 0; i < 4; i++) {
        this->emptyBlock[i] = false;
    }
    for (int i = 0; i < 3; i++) {
        if (this->numberBlockLefts[i] != NULL) {
            this->removeChild(this->numberBlockLefts[i]);
            this->numberBlockLefts[i] = NULL;
        }
        if (this->operatorOuts[i] != NULL) {
            this->removeChild(this->operatorOuts[i]);
            this->operatorOuts[i] = NULL;
        }
        if (this->numberBlockRights[i] != NULL) {
            this->removeChild(this->numberBlockRights[i]);
            this->numberBlockRights[i] = NULL;
        }
        if (this->numberBlockResults[i] != NULL) {
            this->removeChild(this->numberBlockResults[i]);
            this->numberBlockResults[i] = NULL;
        }
    }
}

Vec2 SolutionBoard::getTargetLocation() {
    switch (this->currIndex) {
    case 0:
        return this->numberLefts[this->currLine]->getPosition();
    case 1:
        return this->operators[this->currLine]->getPosition();
    case 2:
        return this->numberRights[this->currLine]->getPosition();
    }
    return NULL;
}

void SolutionBoard::onNumberClickListener(Ref *pRef) {
    if (!this->checkCursor()) {
        return;
    }
    if (this->currIndex % 2 != 0) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (this->numberFrames[i] == pRef) {
            auto numberBlock = this->numberBlocks[i];
            this->numberBlocks[i] = NULL;
            if (numberBlock != NULL) {
                numberBlock->setPosition(this->getTargetLocation());
                switch (this->currIndex) {
                case 0:
                    this->numberBlockLefts[this->currLine] = numberBlock;
                    break;
                case 2:
                    this->numberBlockRights[this->currLine] = numberBlock;
                    break;
                }
            }
        }
    }
    this->cursorToNext();
}

void SolutionBoard::onOperatorClickListener(Ref *pRef) {
    if (!this->checkCursor()) {
        return;
    }
    if (this->currIndex % 2 == 0) {
        return;
    }
    if (pRef == this->operatePlusBtn->GetRef()) {
        this->operatorOuts[this->currLine] = OperatePlus::create(this->operateSize);
    } else if (pRef == this->operateMinusBtn->GetRef()) {
        this->operatorOuts[this->currLine] = OperateMinus::create(this->operateSize);
    } else if (pRef == this->operateMultBtn->GetRef()) {
        this->operatorOuts[this->currLine] = OperateMult::create(this->operateSize);
    } else if (pRef == this->operateDivBtn->GetRef()) {
        this->operatorOuts[this->currLine] = OperateDiv::create(this->operateSize);
    }
    this->operatorOuts[this->currLine]->setAnchorPoint(Point(0.5, 0.5));
    this->operatorOuts[this->currLine]->setPosition(this->getTargetLocation());
    this->addChild(this->operatorOuts[this->currLine], 0);
    this->cursorToNext();
}

bool SolutionBoard::checkCursor() {
    if (this->currIndex > 2) {
        return false;
    } else if (this->currLine > 2) {
        return false;
    }
    return true;
}

void SolutionBoard::cursorToNext() {
    this->currIndex++;
    if (this->currIndex > 2) {
        this->currIndex = 0;
        if (this->currLine < 3) {
            this->calculateLine();
            this->currLine++;
        }
    }
}

void SolutionBoard::calculateLine() {
    auto accurateNumberLeft = this->numberBlockLefts[this->currLine]->GetNumber();
    auto accurateNumberRight = this->numberBlockRights[this->currLine]->GetNumber();
    auto accurateNumber = gameEngine->CalculateFormula(*(this->numberBlockLefts[this->currLine]->GetNumber()), \
    this->operatorOuts[this->currLine]->GetOperator(), *(this->numberBlockRights[this->currLine]->GetNumber()));

    // add number result
    this->numberBlockResults[this->currLine] = NumberBlock::create(numberSize, accurateNumber);
    this->numberBlockResults[this->currLine]->setAnchorPoint(Point(0.5, 0.5));
    this->numberBlockResults[this->currLine]->setPosition(this->numberResults[this->currLine]->getPosition());
    this->numberBlockResults[this->currLine]->SetActiveState(true);
    this->addChild(this->numberBlockResults[this->currLine], 0);

    // add number
    if (this->currLine < 2) {
        for (int i = 0; i < 4; i++) {
            if (this->numberBlocks[i] == NULL) {
                this->numberBlocks[i] = NumberBlock::create(numberSize, accurateNumber);
                this->numberBlocks[i]->setAnchorPoint(Point(0.5, 0.5));
                this->numberBlocks[i]->setPosition(this->numberFrames[i]->getPosition());
                this->numberBlocks[i]->SetActiveState(true);
                this->addChild(this->numberBlocks[i], 0);
                break;
            }
        }
    }
}