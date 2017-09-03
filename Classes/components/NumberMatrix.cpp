#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/GameEngine.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;

NumberMatrix::NumberMatrix() {
    gameEngine->InitNumberMatrix();
    this->selectedLen = 0;
}

NumberMatrix* NumberMatrix::create(float width, float height) {
    auto numberMatrix = new NumberMatrix();
    numberMatrix->setContentSize(Size(width, height));
    numberMatrix->ignoreAnchorPointForPosition(false);

    numberMatrix->numberBlockSize = (1 - (MATRIX_WIDTH - 1) * 0.02) * width / MATRIX_WIDTH;
    numberMatrix->numberBlockInterval = 0.02 * width;
    for (int h=0;h<MATRIX_HEIGHT;h++) {
        for (int w=0;w<MATRIX_WIDTH;w++) {
            auto numberBlock = NumberBlock::create(numberMatrix->numberBlockSize, gameEngine->GetNumber(w, h));
            numberMatrix->numberNodeMatrix[h][w] = numberBlock;

            // add number block
            numberBlock->setAnchorPoint(Point(0, 0));
            numberBlock->setPosition(w * (numberMatrix->numberBlockInterval + numberMatrix->numberBlockSize), \
                h * (numberMatrix->numberBlockInterval + numberMatrix->numberBlockSize));
            numberMatrix->addChild(numberBlock, 0);
        }
    }

    // set touchable
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
        this->eventListener = EventListenerTouchOneByOne::create();
        this->eventListener->onTouchBegan = CC_CALLBACK_2(NumberMatrix::onTouchBegan, this);
        this->eventListener->onTouchMoved = CC_CALLBACK_2(NumberMatrix::onTouchMoved, this);
        this->eventListener->onTouchEnded = CC_CALLBACK_2(NumberMatrix::onTouchEnded, this);
        this->eventListener->setSwallowTouches(true);
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(this->eventListener, this);
    } else {
        this->_eventDispatcher->removeEventListener(this->eventListener);
    }
}

void NumberMatrix::handleSelectBlock() {
    if (this->selectListener != NULL && this->selectedLen == SELECTED_MAX) {
        this->selectListener();
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

void NumberMatrix::SetOnSelectListener(std::function<void(void)> listener) {
    this->selectListener = listener;
}