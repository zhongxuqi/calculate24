#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#include "cocos2d.h"

const int SELECTED_MAX = 4;
const int NUMBER_MAX = 13;
const int MATRIX_WIDTH = 8;
const int MATRIX_HEIGHT = 10;
const int NUMBER_DISABLE = -1;

class GameEngine {
protected:
    int numberMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    GameEngine();

public:
    void InitNumberMatrix();
    int GetNumber(int w, int h);

    static GameEngine* Instance;
};

#endif