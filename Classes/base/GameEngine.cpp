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

Response GameEngine::PostSolution(SolutionStep *solution) {
    Response resp;
    resp.isValid = false;
    if (!solution) {
        return resp;
    }
    this->selectedLen = 0;
    auto calculateResult = this->calculateSolution(solution);
    if (calculateResult.value / calculateResult.divider != 24 || calculateResult.value % calculateResult.divider != 0) {
        return resp;
    }
    for (int i = 0; i < SELECTED_MAX; i++) {
        this->numberMatrix[this->selectedBlocks[i].H][this->selectedBlocks[i].W] = 0;
    }
    resp.isValid = true;
    resp.blockTransfer = this->sortMatrix();
    return resp;
}

BlockTransfer* GameEngine::sortMatrix() {
    BlockTransfer *head = NULL, *curr = NULL;
    for (int h = 0; h < MATRIX_HEIGHT - 1; h++) {
        for (int w = 0; w < MATRIX_WIDTH; w++) {
            if (this->numberMatrix[h][w] == 0) {
                for (int ht = h + 1; ht < MATRIX_HEIGHT; ht++) {
                    if (this->numberMatrix[ht][w] != 0) {
                        this->numberMatrix[h][w] = this->numberMatrix[ht][w];
                        this->numberMatrix[ht][w] = 0;

                        // add transfert to chain
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
}

AccurateNumber GameEngine::calculateSolution(SolutionStep *solution) {
    AccurateNumber accurateNumber;
    accurateNumber.value = 0;
    accurateNumber.divider = 1;
    accurateNumber.wrong = false;
    if (solution == NULL) {
        return accurateNumber;
    }

    // get left accurate number
    AccurateNumber accurateNumberLeft;
    accurateNumber.value = 0;
    accurateNumber.divider = 1;
    accurateNumber.wrong = false;

    // check operator
    if (solution->Operator != '+' && solution->Operator != '-' && solution->Operator != '*' && solution->Operator != '/') {
        accurateNumber.wrong = true;
        return accurateNumber;
    }

    int leftW = solution->LocationLeft[0], leftH = solution->LocationLeft[1];
    if (solution->IsValueLeft && leftW >= 0 && leftW < MATRIX_WIDTH && leftH >= 0 && leftH < MATRIX_HEIGHT && \
    this->numberMatrix[leftH][leftW] > 0) {
        if (this->selectedLen == SELECTED_MAX) {
            accurateNumber.wrong = true;
            return accurateNumber;
        }
        // check left location
        for (int i = 0; i < this->selectedLen; i++) {
            if (this->selectedBlocks[i].H == leftH && this->selectedBlocks[i].W == leftW) {
                accurateNumber.wrong = true;
                return accurateNumber;
            }
        }
        this->selectedBlocks[this->selectedLen].H = leftH;
        this->selectedBlocks[this->selectedLen].W = leftW;
        this->selectedLen++;
        accurateNumberLeft.value = this->numberMatrix[leftH][leftW];
    } else if (!(solution->IsValueLeft) && solution != NULL) {
        accurateNumberLeft = this->calculateSolution(solution);
    } else {
        accurateNumberLeft.wrong = true;
    }
    if (accurateNumberLeft.wrong) {
        accurateNumber.wrong = true;
        return accurateNumber;
    }

    // get right accurate number
    AccurateNumber accurateNumberRight;
    accurateNumber.value = 0;
    accurateNumber.divider = 1;
    accurateNumber.wrong = false;

    int rightW = solution->LocationRight[0], rightH = solution->LocationRight[1];
    if (solution->IsValueRight && rightW >= 0 && rightW < MATRIX_WIDTH && rightH >= 0 && rightH < MATRIX_HEIGHT && \
    this->numberMatrix[rightH][rightW] > 0) {
        if (this->selectedLen == SELECTED_MAX) {
            accurateNumber.wrong = true;
            return accurateNumber;
        }
        // check right location
        for (int i = 0; i < this->selectedLen; i++) {
            if (this->selectedBlocks[i].H == rightH && this->selectedBlocks[i].W == rightW) {
                accurateNumber.wrong = true;
                return accurateNumber;
            }
        }
        this->selectedBlocks[this->selectedLen].H = rightH;
        this->selectedBlocks[this->selectedLen].W = rightW;
        this->selectedLen++;
        accurateNumberRight.value = this->numberMatrix[rightH][rightW];
    } else if (!(solution->IsValueRight) && solution != NULL) {
        accurateNumberRight = this->calculateSolution(solution);
    } else {
        accurateNumberRight.wrong = true;
    }
    if (accurateNumberRight.wrong) {
        accurateNumber.wrong = true;
        return accurateNumber;
    }

    // calculate result
    switch (solution->Operator) {
    case '+':
        accurateNumber.value = accurateNumberLeft.value * accurateNumberRight.divider + accurateNumberRight.value * accurateNumberLeft.divider;
        accurateNumber.divider = accurateNumberLeft.divider * accurateNumberRight.divider;
        break;
    case '-':
        accurateNumber.value = accurateNumberLeft.value * accurateNumberRight.divider - accurateNumberRight.value * accurateNumberLeft.divider;
        accurateNumber.divider = accurateNumberLeft.divider * accurateNumberRight.divider;
        break;
    case '*':
        accurateNumber.value = accurateNumberLeft.value * accurateNumberRight.value;
        accurateNumber.divider = accurateNumberLeft.divider * accurateNumberRight.divider;
        break;
    case '/':
        accurateNumber.value = accurateNumberLeft.value * accurateNumberRight.divider;
        accurateNumber.divider = accurateNumberLeft.divider * accurateNumberRight.value;
        break;
    default:
        accurateNumber.wrong = true;
    }
    return accurateNumber;
}