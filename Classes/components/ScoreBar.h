#ifndef __SCORE_BAR_H__
#define __SCORE_BAR_H__

#include "cocos2d.h"

class ScoreBar: public cocos2d::Layer {
public:
    ScoreBar();
    cocos2d::Layer* const ContentLayer;
    void SetScore(cocos2d::Label* score);

    static ScoreBar* create(float width, float height);
};

#endif