#ifndef __NUMBER_MATRIX_H__
#define __NUMBER_MATRIX_H__

#include "cocos2d.h"
#include "Base.h"
#include "NumberBlock.h"
#include "../base/GameEngine.h"

class NumberMatrix : public BaseComponent {
protected:
    NumberBlock* numberNodeMatrix[MATRIX_HEIGHT][MATRIX_WIDTH];

public:
    NumberMatrix();

    static NumberMatrix* create(float width, float height);
};

#endif