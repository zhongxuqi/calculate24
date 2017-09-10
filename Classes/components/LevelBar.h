#ifndef __LEVEL_BAR_H__
#define __LEVEL_BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LevelBar : public cocos2d::Layer {
protected:
    virtual bool init();
    int level;
    cocos2d::Label *levelLabel;

public:
    static LevelBar* create(float width, float height);
    CREATE_FUNC(LevelBar);
    LevelBar();
    cocos2d::Layer* const ContentLayer;
    void SetLevel(int level);
    int GetLevel();
};

#endif