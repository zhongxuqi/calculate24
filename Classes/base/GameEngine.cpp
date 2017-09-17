#include "GameEngine.h"
#include "Colors.h"
#include "../utils/TimeUtils.h"

USING_NS_CC;

GameEngine* GameEngine::Instance = new GameEngine();

GameEngine::GameEngine() {
    this->isEnd = true;
    this->level = 1;
}

void GameEngine::initNumberMatrix() {
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

void GameEngine::printSolution(SolutionStep *solution, int layer) {
    if (solution->IsValueLeft) {
        int w = solution->LocationLeft.W, h = solution->LocationLeft.H;
        CCLOG("[%d] Value Left: %d", layer, this->numberMatrix[h][w]);
    } else {
        printSolution(solution->SolutionStepLeft, layer + 1);
    }
    CCLOG("[%d] Operator: %c", layer, solution->Operator);
    if (solution->IsValueRight) {
        int w = solution->LocationRight.W, h = solution->LocationRight.H;
        CCLOG("[%d] Value Right: %d", layer, this->numberMatrix[h][w]);
    } else {
        printSolution(solution->SolutionStepRight, layer + 1);
    }
}

Response *GameEngine::PushSolution(SolutionStep *solution) {
    auto resp = new Response{};
    resp->isValid = false;
    printSolution(solution, 0);
    if (this->isEnd) {
        return resp;
    }
    this->selectedLen = 0;
    auto calculateResult = this->calculateSolution(solution);
    if (calculateResult->wrong || calculateResult->value / calculateResult->divider != 24 || calculateResult->value % calculateResult->divider != 0) {
        return resp;
    }
    if (this->selectedLen != 4) {
        return resp;
    }
    for (int i = 0; i < SELECTED_MAX; i++) {
        this->numberMatrix[this->selectedBlocks[i].H][this->selectedBlocks[i].W] = 0;
    }
    resp->isValid = true;
    resp->blockTransfer = this->sortMatrix();
    return resp;
}

BlockTransfer* GameEngine::sortMatrix() {
    BlockTransfer *head = NULL, *curr = NULL;
    for (int h = 0; h < MATRIX_HEIGHT - 1; h++) {
        for (int w = 0; w < MATRIX_WIDTH; w++) {
            if (this->numberMatrix[h][w] <= 0) {
                for (int ht = h + 1; ht < MATRIX_HEIGHT; ht++) {
                    if (this->numberMatrix[ht][w] > 0) {
                        this->numberMatrix[h][w] = this->numberMatrix[ht][w];
                        this->numberMatrix[ht][w] = 0;

                        // add transfer to chain
                        CCLOG("Transfer (%d, %d) => (%d, %d)", ht, w, h, w);
                        if (head == NULL) {
                            head = new BlockTransfer{};
                            head->OldLocation.H = ht;
                            head->OldLocation.W = w;
                            head->NewLocation.H = h;
                            head->NewLocation.W = w;
                            head->Next = NULL;
                            curr = head;
                        } else {
                            curr->Next = new BlockTransfer{};
                            curr->Next->OldLocation.H = ht;
                            curr->Next->OldLocation.W = w;
                            curr->Next->NewLocation.H = h;
                            curr->Next->NewLocation.W = w;
                            curr->Next->Next = NULL;
                            curr = curr->Next;
                        }
                        break;
                    }
                }
            }
        }
    }
    for (int w = 0; w < MATRIX_WIDTH - 1; w++) {
        if (this->numberMatrix[0][w] <= 0) {
            int wt;
            bool hasFind = false;
            for (wt = w + 1; wt < MATRIX_WIDTH; wt++) {
                if (this->numberMatrix[0][wt] > 0) {
                    hasFind = true;
                    break;
                }
            }
            if (!hasFind) {
                break;
            }
            for (int h = 0; h < MATRIX_HEIGHT; h++) {
                if (this->numberMatrix[h][wt] <= 0) {
                    break;
                }
                this->numberMatrix[h][w] = this->numberMatrix[h][wt];
                this->numberMatrix[h][wt] = 0;

                // add transfer to chain
                CCLOG("Transfer (%d, %d) => (%d, %d)", h, wt, h, w);
                if (head == NULL) {
                    head = new BlockTransfer{};
                    head->OldLocation.H = h;
                    head->OldLocation.W = wt;
                    head->NewLocation.H = h;
                    head->NewLocation.W = w;
                    head->Next = NULL;
                    curr = head;
                } else {
                    curr->Next = new BlockTransfer{};
                    curr->Next->OldLocation.H = h;
                    curr->Next->OldLocation.W = wt;
                    curr->Next->NewLocation.H = h;
                    curr->Next->NewLocation.W = w;
                    curr->Next->Next = NULL;
                    curr = curr->Next;
                }
            }
        }
    }
    return head;
}

AccurateNumber *GameEngine::calculateSolution(SolutionStep *solution) {
    CCLOG("calculateSolution");
    auto accurateNumber = new AccurateNumber{};
    accurateNumber->value = 0;
    accurateNumber->divider = 1;
    accurateNumber->wrong = true;
    if (solution == NULL) {
        accurateNumber->wrong = false;
        return accurateNumber;
    }
    
    // check operator
    if (solution->Operator != '+' && solution->Operator != '-' && solution->Operator != '*' && solution->Operator != '/') {
        accurateNumber->wrong = true;
        return accurateNumber;
    }

    if (solution->IsValueLeft) {
        int w = solution->LocationLeft.W, h = solution->LocationLeft.H;
        CCLOG("accurateNumberLeft (%d, %d) %d", w, h, this->numberMatrix[h][w]);
    }

    // get left accurate number
    auto accurateNumberLeft = new AccurateNumber{};
    accurateNumberLeft->value = 0;
    accurateNumberLeft->divider = 1;
    accurateNumberLeft->wrong = false;

    int leftW = solution->LocationLeft.W, leftH = solution->LocationLeft.H;
    if (solution->IsValueLeft && leftW >= 0 && leftW < MATRIX_WIDTH && leftH >= 0 && leftH < MATRIX_HEIGHT && \
    this->numberMatrix[leftH][leftW] > 0) {
        if (this->selectedLen == SELECTED_MAX) {
            accurateNumber->wrong = true;
            return accurateNumber;
        }
        // check left location
        for (int i = 0; i < this->selectedLen; i++) {
            if (this->selectedBlocks[i].H == leftH && this->selectedBlocks[i].W == leftW) {
                accurateNumber->wrong = true;
                return accurateNumber;
            }
        }
        this->selectedBlocks[this->selectedLen].H = leftH;
        this->selectedBlocks[this->selectedLen].W = leftW;
        this->selectedLen++;
        accurateNumberLeft->value = this->numberMatrix[leftH][leftW];
    } else if (!(solution->IsValueLeft) && solution->SolutionStepLeft != NULL) {
        accurateNumberLeft = this->calculateSolution(solution->SolutionStepLeft);
    } else {
        accurateNumberLeft->wrong = true;
    }
    if (accurateNumberLeft->wrong) {
        accurateNumber->wrong = true;
        return accurateNumber;
    }

    CCLOG("accurateNumberLeft %d %d", accurateNumberLeft->value, accurateNumberLeft->divider);

    if (solution->IsValueRight) {
        int w = solution->LocationRight.W, h = solution->LocationRight.H;
        CCLOG("accurateNumberRight %d", this->numberMatrix[h][w]);
    }

    // get right accurate number
    auto accurateNumberRight = new AccurateNumber{};
    accurateNumberRight->value = 0;
    accurateNumberRight->divider = 1;
    accurateNumberRight->wrong = false;

    int rightW = solution->LocationRight.W, rightH = solution->LocationRight.H;
    if (solution->IsValueRight && rightW >= 0 && rightW < MATRIX_WIDTH && rightH >= 0 && rightH < MATRIX_HEIGHT && \
    this->numberMatrix[rightH][rightW] > 0) {
        if (this->selectedLen == SELECTED_MAX) {
            accurateNumber->wrong = true;
            return accurateNumber;
        }
        // check right location
        for (int i = 0; i < this->selectedLen; i++) {
            if (this->selectedBlocks[i].H == rightH && this->selectedBlocks[i].W == rightW) {
                accurateNumber->wrong = true;
                return accurateNumber;
            }
        }
        this->selectedBlocks[this->selectedLen].H = rightH;
        this->selectedBlocks[this->selectedLen].W = rightW;
        this->selectedLen++;
        accurateNumberRight->value = this->numberMatrix[rightH][rightW];
    } else if (!(solution->IsValueRight) && solution->SolutionStepRight != NULL) {
        accurateNumberRight = this->calculateSolution(solution->SolutionStepRight);
    } else {
        accurateNumberRight->wrong = true;
    }
    if (accurateNumberRight->wrong) {
        accurateNumber->wrong = true;
        return accurateNumber;
    }

    CCLOG("accurateNumberRight %d %d", accurateNumberRight->value, accurateNumberRight->divider);

    // calculate result
    accurateNumber = this->CalculateFormula(*accurateNumberLeft, solution->Operator, *accurateNumberRight);

    delete accurateNumberLeft;
    delete accurateNumberRight;
    return accurateNumber;
}

AccurateNumber *GameEngine::CalculateFormula(AccurateNumber accurateNumberLeft, char theOp, AccurateNumber accurateNumberRight) {
    auto accurateNumber = new AccurateNumber{};
    switch (theOp) {
    case '+':
        accurateNumber->value = accurateNumberLeft.value * accurateNumberRight.divider + accurateNumberRight.value * accurateNumberLeft.divider;
        accurateNumber->divider = accurateNumberLeft.divider * accurateNumberRight.divider;
        break;
    case '-':
        accurateNumber->value = accurateNumberLeft.value * accurateNumberRight.divider - accurateNumberRight.value * accurateNumberLeft.divider;
        accurateNumber->divider = accurateNumberLeft.divider * accurateNumberRight.divider;
        break;
    case '*':
        accurateNumber->value = accurateNumberLeft.value * accurateNumberRight.value;
        accurateNumber->divider = accurateNumberLeft.divider * accurateNumberRight.divider;
        break;
    case '/':
        accurateNumber->value = accurateNumberLeft.value * accurateNumberRight.divider;
        accurateNumber->divider = accurateNumberLeft.divider * accurateNumberRight.value;
        break;
    default:
        accurateNumber->wrong = true;
    }
    if (accurateNumber->value % accurateNumber->divider == 0) {
        accurateNumber->value = accurateNumber->value / accurateNumber->divider;
        accurateNumber->divider = 1;
    }
    return accurateNumber;
}

int GameEngine::GetScore() {
    return this->score;
}

int GameEngine::GetRoundTarget() {
    return this->roundTarget;
}

void GameEngine::StartGame() {
    this->initNumberMatrix();
    this->isEnd = false;
    auto listener = this->onStartListener;
    this->level = 0;
    this->roundTarget = 0;
    this->levelUp();
    if (listener != NULL) {
        listener();
    }
}

void GameEngine::levelUp() {
    this->tick = TOTAL_TICK;
    this->level++;
    this->roundTarget = 8;
}

void GameEngine::TimeTick() {
    this->tick--;
    if (this->tick <= 0) {
        this->isEnd = true;
        auto listener = this->onEndListener;
        if (listener != NULL) {
            listener();
        }
    }
}

long GameEngine::GetTick() {
    return this->tick;
}

int GameEngine::GetLevel() {
    return this->level;
}

void GameEngine::SetOnStartListener(std::function<void()> listener) {
    this->onStartListener = listener;
}

void GameEngine::SetOnEndListener(std::function<void()> listener) {
    this->onEndListener = listener;
}