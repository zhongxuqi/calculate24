#include "GameEngine.h"
#include "Colors.h"
#include "../utils/TimeUtils.h"
#include "../utils/PreferenceUtils.h"

USING_NS_CC;

GameEngine* GameEngine::Instance = new GameEngine();

GameEngine::GameEngine() {
    
}

void GameEngine::initNumberMatrix() {
    for (int i=0;i<MATRIX_HEIGHT;i++) {
        for (int j=0;j<MATRIX_WIDTH;j++) {
            this->numberMatrix[i][j] = this->randomNumber();
        }
    }
}

int GameEngine::randomNumber() {
    return cocos2d::RandomHelper::random_int(1, NUMBER_MAX);
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
    this->score++;
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
                            head->IsNew = false;
                            head->OldLocation.H = ht;
                            head->OldLocation.W = w;
                            head->NewLocation.H = h;
                            head->NewLocation.W = w;
                            head->Next = NULL;
                            curr = head;
                        } else {
                            curr->Next = new BlockTransfer{};
                            curr->Next->IsNew = false;
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
    for (int h = 0; h < MATRIX_HEIGHT; h++) {
        for (int w = 0; w < MATRIX_WIDTH; w++) {
            if (this->numberMatrix[h][w] <= 0) {
                this->numberMatrix[h][w] = this->randomNumber();

                // add transfer to chain
                CCLOG("New (%d, %d) %d", h, w, this->numberMatrix[h][w]);
                if (head == NULL) {
                    head = new BlockTransfer{};
                    head->IsNew = true;
                    head->Number = new AccurateNumber{};
                    head->Number->value = this->numberMatrix[h][w];
                    head->Number->divider = 1;
                    head->OldLocation.H = h;
                    head->OldLocation.W = w;
                    head->NewLocation.H = h;
                    head->NewLocation.W = w;
                    head->Next = NULL;
                    curr = head;
                } else {
                    curr->Next = new BlockTransfer{};
                    curr->Next->IsNew = true;
                    curr->Next->Number = new AccurateNumber{};
                    curr->Next->Number->value = this->numberMatrix[h][w];
                    curr->Next->Number->divider = 1;
                    curr->Next->OldLocation.H = h;
                    curr->Next->OldLocation.W = w;
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

void GameEngine::StartGame() {
    this->initNumberMatrix();
    this->score = 0;
    auto listener = this->onStartListener;
    if (listener != NULL) {
        listener();
    }
}

void GameEngine::SetOnStartListener(std::function<void()> listener) {
    this->onStartListener = listener;
}

void GameEngine::SetOnEndListener(std::function<void()> listener) {
    this->onEndListener = listener;
}

void GameEngine::SaveGame() {
    PreferenceUtils::SetBoolPref(HAS_SAVE_GAME, true);
    PreferenceUtils::SetIntPref(GAME_SCORE, this->score);
    std::stringstream numberStr;
    for (int h=0;h<MATRIX_HEIGHT;h++) {
        for (int w=0;w<MATRIX_WIDTH;w++) {
            numberStr << this->numberMatrix[h][w] << " ";
        }
    }
    PreferenceUtils::SetStringPref(GAME_MATRIX, numberStr.str().c_str());
}

int getNextNumber(std::string str, int &currIndex) {
    int ret = 0;
    for (; currIndex < str.length(); currIndex++) {
        if (str[currIndex] >= '0' && str[currIndex] <= '9') {
            break;
        }
    }
    while (currIndex < str.length() && str[currIndex] >= '0' && str[currIndex] <= '9') {
        ret = ret * 10 + (str[currIndex] - '0');
        currIndex++;
    }
    return ret;
}

void GameEngine::RestoreGame() {
    if (!PreferenceUtils::GetBoolPref(HAS_SAVE_GAME)) {
        return;
    }
    CCLOG("GameEngine::RestoreGame Start");
    this->score = PreferenceUtils::GetIntPref(GAME_SCORE);
    auto matrixStr = PreferenceUtils::GetStringPref(GAME_MATRIX);
    int currIndex = 0;
    for (int h=0;h<MATRIX_HEIGHT;h++) {
        for (int w=0;w<MATRIX_WIDTH;w++) {
            this->numberMatrix[h][w] = getNextNumber(matrixStr, currIndex);
        }
    }
    auto listener = this->onStartListener;
    if (listener != NULL) {
        listener();
    }
    CCLOG("GameEngine::RestoreGame End");
}

 bool GameEngine::HasSaveGame() {
     return PreferenceUtils::GetBoolPref(HAS_SAVE_GAME);
 }