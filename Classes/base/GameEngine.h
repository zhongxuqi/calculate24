#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#include "cocos2d.h"

const int SELECTED_MAX = 4;
const int NUMBER_MAX = 13;
const int MATRIX_WIDTH = 8;
const int MATRIX_HEIGHT = 10;
const int NUMBER_DISABLE = -1;

struct BlockLocation {
    int W;
    int H;
};

struct AccurateNumber {
    int value;
    int divider;
    bool wrong;
};

struct SolutionStep {
    bool IsValueLeft;
    int LocationLeft[2];
    SolutionStep *SolutionStepLeft;
    char Operator;
    bool IsValueRight;
    int LocationRight[2];
    SolutionStep *SolutionStepRight;
};

struct BlockTransfer {
    BlockLocation OldLocation;
    BlockLocation NewLocation;
    BlockTransfer *Next;
};

struct Response {
    BlockTransfer *blockTransfer;
    bool isValid;
};

class GameEngine {
protected:
    int numberMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];
    GameEngine();
    BlockLocation selectedBlocks[SELECTED_MAX];
    int selectedLen;
    AccurateNumber calculateSolution(SolutionStep *solution);
    BlockTransfer* sortMatrix();

public:
    void InitNumberMatrix();
    int GetNumber(int w, int h);
    Response PostSolution(SolutionStep *solution);
    AccurateNumber *CalculateFormula(AccurateNumber accurateNumberLeft, char theOp, AccurateNumber accurateNumberRight);

    static GameEngine* Instance;
};

#endif