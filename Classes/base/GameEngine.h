#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#include "cocos2d.h"

const int SELECTED_MAX = 4;
const int NUMBER_MAX = 13;
const int MATRIX_WIDTH = 8;
const int MATRIX_HEIGHT = 10;
const int NUMBER_DISABLE = -1;
const int TOTAL_TICK = 60;

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
    BlockLocation LocationLeft;
    SolutionStep *SolutionStepLeft;
    char Operator;
    bool IsValueRight;
    BlockLocation LocationRight;
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
    AccurateNumber *calculateSolution(SolutionStep *solution);
    BlockTransfer *sortMatrix();
    void printSolution(SolutionStep *solution, int layer);
    void initNumberMatrix();

    // game info
    int score;
    int roundTarget;
    int level;
    long tick;
    bool isEnd;
    std::function<void()> onStartListener;
    void levelUp();
    std::function<void()> onEndListener; 

public:
    int GetNumber(int w, int h);
    Response *PushSolution(SolutionStep *solution);
    AccurateNumber *CalculateFormula(AccurateNumber accurateNumberLeft, char theOp, AccurateNumber accurateNumberRight);
    int GetScore();
    int GetRoundTarget();
    static GameEngine* Instance;
    void StartGame();
    void TimeTick();
    int GetLevel();
    long GetTick();
    void SetOnEndListener();
    void SetOnStartListener(std::function<void()> listener);
    void SetOnEndListener(std::function<void()> listener);
};

#endif