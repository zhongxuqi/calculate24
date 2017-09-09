#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/GameEngine.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;

bool NumberMatrix::init() {
    if (!Layer::init()) {
        return false;
    }
    gameEngine->InitNumberMatrix();
    this->selectedLen = 0;
    return true;
}

NumberMatrix* NumberMatrix::create(float width, float height) {
    auto numberMatrix = NumberMatrix::create();
    numberMatrix->setContentSize(Size(width, height));
    numberMatrix->setIgnoreAnchorPointForPosition(false);

    numberMatrix->numberBlockSize = (1 - (MATRIX_WIDTH - 1) * 0.02) * width / MATRIX_WIDTH;
    numberMatrix->numberBlockInterval = 0.02 * width;
    for (int h=0;h<MATRIX_HEIGHT;h++) {
        for (int w=0;w<MATRIX_WIDTH;w++) {
            auto accurateNumber = new AccurateNumber{};
            accurateNumber->value = gameEngine->GetNumber(w, h);
            accurateNumber->divider = 1;
            auto numberBlock = NumberBlock::create(numberMatrix->numberBlockSize, accurateNumber);
            numberMatrix->numberNodeMatrix[h][w] = numberBlock;

            // add number block
            numberBlock->setAnchorPoint(Point(0, 0));
            numberBlock->setPosition(w * (numberMatrix->numberBlockInterval + numberMatrix->numberBlockSize), \
                h * (numberMatrix->numberBlockInterval + numberMatrix->numberBlockSize));
            numberMatrix->addChild(numberBlock, 0);
        }
    }

    // set touchable
    numberMatrix->eventListener = EventListenerTouchOneByOne::create();
    numberMatrix->eventListener->onTouchBegan = CC_CALLBACK_2(NumberMatrix::onTouchBegan, numberMatrix);
    numberMatrix->eventListener->onTouchMoved = CC_CALLBACK_2(NumberMatrix::onTouchMoved, numberMatrix);
    numberMatrix->eventListener->onTouchEnded = CC_CALLBACK_2(NumberMatrix::onTouchEnded, numberMatrix);
    numberMatrix->eventListener->setSwallowTouches(true);
    numberMatrix->_eventDispatcher->addEventListenerWithSceneGraphPriority(numberMatrix->eventListener, numberMatrix);
    numberMatrix->setTouchable(true);

    return numberMatrix;
}

bool NumberMatrix::onTouchBegan(Touch *touch, Event *unused_event) {
    this->handleTouch(touch);
    return true;
}

void NumberMatrix::onTouchMoved(Touch *touch, Event *unused_event) {
    this->handleTouch(touch);
}

void NumberMatrix::onTouchEnded(Touch *touch, Event *unused_event) {
    this->handleSelectBlock();
}

void NumberMatrix::handleTouch(Touch *touch) {
    int selectedLen = this->selectedLen;
    if (selectedLen >= SELECTED_MAX) {
        return;
    }
    float locationX = touch->getLocation().x - (this->getPosition().x - this->getAnchorPoint().x * this->getContentSize().width);
    float locationY = touch->getLocation().y - (this->getPosition().y - this->getAnchorPoint().y * this->getContentSize().height);
    int w = (int)(locationX / (this->numberBlockSize + this->numberBlockInterval));
    int h = (int)(locationY / (this->numberBlockSize + this->numberBlockInterval));
    if (w >= 0 && w < MATRIX_WIDTH && h >= 0 && h < MATRIX_HEIGHT && !this->numberNodeMatrix[h][w]->IsActive()) {

        // check the block is continuous
        if (selectedLen > 0) {
            auto isLegel = false;
            for (int i=0;i<selectedLen;i++) {
                if (abs(this->selectedBlockIndexes[i][0] - w) + abs(this->selectedBlockIndexes[i][1] - h) <= 1) {
                    isLegel = true;
                    break;
                }
            }
            if (!isLegel) {
                return;
            }
        }
        this->selectedLen = selectedLen + 1;

        this->selectedNumberBlocks[selectedLen] = this->numberNodeMatrix[h][w];
        this->selectedBlockIndexes[selectedLen][0] = w;
        this->selectedBlockIndexes[selectedLen][1] = h;
        this->numberNodeMatrix[h][w]->SetActiveState(true);
    }
}

void NumberMatrix::setTouchable(bool isTouchable) {
    if (isTouchable) {
        this->_eventDispatcher->resumeEventListenersForTarget(this);
    } else {
        this->_eventDispatcher->pauseEventListenersForTarget(this);
    }
}

void NumberMatrix::handleSelectBlock() {
    if (this->selectListener != NULL && this->selectedLen == SELECTED_MAX) {
        auto accurateNumbers = new AccurateNumber*[4];
        for (int i = 0; i < 4; i++) {
            accurateNumbers[i] = this->selectedNumberBlocks[i]->GetNumber();
        }
        this->selectListener(accurateNumbers);
    }
    this->cancelSelectBlock();
}

void NumberMatrix::cancelSelectBlock() {
    int selectedLen = this->selectedLen;
    for (int i=0;i<selectedLen;i++) {
        this->selectedNumberBlocks[i]->SetActiveState(false);
    }
    this->selectedLen = 0;
}

void NumberMatrix::SetOnSelectListener(std::function<void(AccurateNumber*[4])> listener) {
    this->selectListener = listener;
}