#ifndef __SCORE_BAR_H__
#define __SCORE_BAR_H__

#include "cocos2d.h"

class ScoreBar: public cocos2d::Layer {
protected:
    virtual bool init();
    int score;
    cocos2d::Label *scoreLabel;

public:
    static ScoreBar* create(float width, float height);
    CREATE_FUNC(ScoreBar);
    ScoreBar();
    cocos2d::Layer* const ContentLayer;
    void SetScore(int score);
    int GetScore();
};

#endif