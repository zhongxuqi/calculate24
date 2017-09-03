#include "SimpleAudioEngine.h"
#include "NumberMatrix.h"
#include "../base/GameEngine.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;

NumberMatrix::NumberMatrix(): BaseComponent(LayerColor::create()) {
    gameEngine->InitNumberMatrix();
}

NumberMatrix* NumberMatrix::create(float width, float height) {
    auto numberMatrix = new NumberMatrix();
    numberMatrix->RootNode->setContentSize(Size(width, height));
    numberMatrix->RootNode->ignoreAnchorPointForPosition(false);

    auto numberBlockSize = (1 - (MATRIX_WIDTH - 1) * 0.02) * width / MATRIX_WIDTH;
    auto numberBlockInterval = 0.02 * width;
    for (int h=0;h<MATRIX_HEIGHT;h++) {
        for (int w=0;w<MATRIX_WIDTH;w++) {
            auto numberBlock = NumberBlock::create(numberBlockSize, gameEngine->GetNumber(w, h));
            numberMatrix->numberNodeMatrix[h][w] = numberBlock;

            // add number block
            numberBlock->GetRootNode()->setAnchorPoint(Point(0, 0));
            numberBlock->GetRootNode()->setPosition(w * (numberBlockInterval + numberBlockSize), h * (numberBlockInterval + numberBlockSize));
            numberMatrix->RootNode->addChild(numberBlock->GetRootNode(), 0);
        }
    }
    return numberMatrix;
}