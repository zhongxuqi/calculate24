#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/GameEngine.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;

bool NumberMatrix::init() {
    if (!Layer::init()) {
        return false;
    }
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
    return this->handleTouch(touch);
}

void NumberMatrix::onTouchMoved(Touch *touch, Event *unused_event) {
    this->handleTouch(touch);
}

void NumberMatrix::onTouchEnded(Touch *touch, Event *unused_event) {
    this->handleSelectBlock();
}

bool NumberMatrix::handleTouch(Touch *touch) {
    int selectedLen = this->selectedLen;
    if (selectedLen >= SELECTED_MAX) {
        return false;
    }
    float locationX = touch->getLocation().x - (this->getPosition().x - this->getAnchorPoint().x * this->getContentSize().width);
    float locationY = touch->getLocation().y - (this->getPosition().y - this->getAnchorPoint().y * this->getContentSize().height);
    int w = (int)(locationX / (this->numberBlockSize + this->numberBlockInterval));
    int h = (int)(locationY / (this->numberBlockSize + this->numberBlockInterval));
    if (w >= 0 && w < MATRIX_WIDTH && h >= 0 && h < MATRIX_HEIGHT && !this->numberNodeMatrix[h][w]->IsActive() && \
    this->numberNodeMatrix[h][w]->isVisible()) {

        // check the block is continuous
        if (selectedLen > 0) {
            auto isLegel = false;
            for (int i=0;i<selectedLen;i++) {
                if (abs(this->selectedBlockIndexes[i].W - w) + abs(this->selectedBlockIndexes[i].H - h) <= 1) {
                    isLegel = true;
                    break;
                }
            }
            if (!isLegel) {
                return false;
            }
        }
        this->selectedLen = selectedLen + 1;

        this->selectedNumberBlocks[selectedLen] = this->numberNodeMatrix[h][w];
        this->selectedBlockIndexes[selectedLen].W = w;
        this->selectedBlockIndexes[selectedLen].H = h;
        this->numberNodeMatrix[h][w]->SetActiveState(true);
        return true;
    }
    return false;
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
    } else {
        this->CancelSelectBlock();
    }
}

void NumberMatrix::CancelSelectBlock() {
    int selectedLen = this->selectedLen;
    for (int i=0;i<selectedLen;i++) {
        this->selectedNumberBlocks[i]->SetActiveState(false);
    }
    this->selectedLen = 0;
}

void NumberMatrix::SetOnSelectListener(std::function<void(AccurateNumber*[4])> listener) {
    this->selectListener = listener;
}

bool NumberMatrix::PushSolution(InputStep* inputSteps[3]) {
    bool numberUsed[6];
    for (int i = 0; i < 6; i++) {
        if (i < 4) {
            numberUsed[i] = false;
        } else {
            numberUsed[i] = true;
        }
    }
    AccurateNumber accurateNumbers[4];
    for (int i = 0; i < SELECTED_MAX; i++) {
        accurateNumbers[i] = *(this->numberNodeMatrix[this->selectedBlockIndexes[i].H][this->selectedBlockIndexes[i].W]->GetNumber());
    }
    SolutionStep *solutionSteps[2];
    AccurateNumber resultAccurateNumbers[2];
    for (int i = 0; i < 2; i++) {
        solutionSteps[i] = NULL;
    }

    SolutionStep *solution;
    AccurateNumber lastResult;
    for (int i = 0; i < 3; i++) {
        auto solutionStep = new SolutionStep{};
        
        // add left number
        bool matched = false;
        for (int j = 0; j < 4; j++) {
            if (!numberUsed[j] && (inputSteps[i]->NumberLeft.value * accurateNumbers[j].divider == inputSteps[i]->NumberLeft.divider * accurateNumbers[j].value)) {
                numberUsed[j] = true;
                solutionStep->IsValueLeft = true;
                solutionStep->LocationLeft.W = this->selectedBlockIndexes[j].W;
                solutionStep->LocationLeft.H = this->selectedBlockIndexes[j].H;
                matched = true;
                break;
            }
        }
        if (!matched) {
            for (int j = 0; j < 2; j++) {
                if (!numberUsed[4 + j] && (inputSteps[i]->NumberLeft.value * resultAccurateNumbers[j].divider == inputSteps[i]->NumberLeft.divider * resultAccurateNumbers[j].value)) {
                    numberUsed[4 + j] = true;
                    solutionStep->IsValueLeft = false;
                    solutionStep->SolutionStepLeft = solutionSteps[j];
                    matched = true;
                    break;
                }
            }
        }
        if (!matched) {
            return false;
        }

        // add operator
        solutionStep->Operator = inputSteps[i]->OperatorTxt;

        // add right number
        matched = false;
        for (int j = 0; j < 4; j++) {
            if (!numberUsed[j] && (inputSteps[i]->NumberRight.value * accurateNumbers[j].divider == inputSteps[i]->NumberRight.divider * accurateNumbers[j].value)) {
                numberUsed[j] = true;
                solutionStep->IsValueRight = true;
                solutionStep->LocationRight.W = this->selectedBlockIndexes[j].W;
                solutionStep->LocationRight.H = this->selectedBlockIndexes[j].H;
                matched = true;
                break;
            }
        }
        if (!matched) {
            for (int j = 0; j < 2; j++) {
                if (!numberUsed[4 + j] && (inputSteps[i]->NumberRight.value * resultAccurateNumbers[j].divider == inputSteps[i]->NumberRight.divider * resultAccurateNumbers[j].value)) {
                    numberUsed[4 + j] = true;
                    solutionStep->IsValueRight = false;
                    solutionStep->SolutionStepRight = solutionSteps[j];
                    matched = true;
                    break;
                }
            }
        }
        if (!matched) {
            return false;
        }

        if (i < 2) {
            solutionSteps[i] = solutionStep;
            resultAccurateNumbers[i] = inputSteps[i]->NumberResult;
            numberUsed[4 + i] = false;
        } else {
            solution = solutionStep;
            lastResult = inputSteps[i]->NumberResult;
        }
    }

    auto resp = gameEngine->PushSolution(solution);
    if (resp->isValid) {
        this->handleTransfer(resp->blockTransfer);
        return true;
    }
    return false;
}

void NumberMatrix::handleTransfer(BlockTransfer *transfer) {
    // clear selected number block
    for (int i = 0; i < SELECTED_MAX; i++) {
        if (this->selectedBlockIndexes[i].H >= 0 && this->selectedBlockIndexes[i].H < MATRIX_HEIGHT && \
        this->selectedBlockIndexes[i].W >= 0 && this->selectedBlockIndexes[i].W < MATRIX_WIDTH) {
            this->numberNodeMatrix[this->selectedBlockIndexes[i].H][this->selectedBlockIndexes[i].W]->setVisible(false);
        }
    }
    this->CancelSelectBlock();
    auto cursor = transfer;
    while (cursor != NULL) {
        if (cursor->OldLocation.H >= 0 && cursor->OldLocation.H < MATRIX_HEIGHT && \
            cursor->OldLocation.W >= 0 && cursor->OldLocation.W < MATRIX_WIDTH && \
            cursor->NewLocation.H >= 0 && cursor->NewLocation.H < MATRIX_HEIGHT && \
            cursor->NewLocation.W >= 0 && cursor->NewLocation.W < MATRIX_WIDTH) {
            int oldH = cursor->OldLocation.H, oldW = cursor->OldLocation.W;
            int newH = cursor->NewLocation.H, newW = cursor->NewLocation.W;
            this->numberNodeMatrix[oldH][oldW]->setVisible(false);
            this->numberNodeMatrix[newH][newW]->SetNumber(this->numberNodeMatrix[oldH][oldW]->GetNumber());
            this->numberNodeMatrix[newH][newW]->setVisible(true);

            auto originPosition = this->numberNodeMatrix[oldH][oldW]->getPosition();
            auto targetPosition = this->numberNodeMatrix[newH][newW]->getPosition();
            this->numberNodeMatrix[newH][newW]->setPosition(originPosition);
            this->numberNodeMatrix[newH][newW]->runAction(MoveTo::create(this->duration, targetPosition));
        }
        cursor = cursor->Next;
    }
}