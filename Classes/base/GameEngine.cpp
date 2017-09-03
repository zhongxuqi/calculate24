#include "GameEngine.h"
#include "Colors.h"

USING_NS_CC;

GameEngine* GameEngine::Instance = new GameEngine();

GameEngine::GameEngine() {
    
}

void GameEngine::InitNumberMatrix() {
    for (int i=0;i<MATRIX_HEIGHT;i++) {
        for (int j=0;j<MATRIX_WIDTH;j++) {
            this->numberMatrix[i][j] = cocos2d::RandomHelper::random_int(1, NUMBER_MAX);
        }
    }
}

int GameEngine::GetNumber(int w, int h) {
    if (w < MATRIX_WIDTH && h < MATRIX_HEIGHT) {
        return this->numberMatrix[h][w];
    }
    return NUMBER_DISABLE;
}