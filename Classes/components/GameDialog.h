#ifndef __GAME_DIALOG_H__
#define __GAME_DIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../base/GameEngine.h"
#include "BtnGameQuit.h"
#include "BtnGameResume.h"

class GameDialog : public cocos2d::LayerColor {
protected:
    virtual bool init();
    cocos2d::Label *gameLabel;
    cocos2d::Layer* const contentLayer;
    void addBackButton();
    const float borderWidth;
    void addRestartButton();
    void addStarBox();
    cocos2d::Layer *starBox;
    cocos2d::Label *scoreLabel;

public:
    GameDialog();
    static GameDialog* create(float width, float height);
    CREATE_FUNC(GameDialog);
    void SetScore(int score);
    static GameDialog* Instance;
};

#endif