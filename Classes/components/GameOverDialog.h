#ifndef __GAME_OVER_DIALOG_H__
#define __GAME_OVER_DIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../base/GameEngine.h"

class GameOverDialog : public cocos2d::LayerColor {
protected:
    virtual bool init();

public:
    static GameOverDialog* create(float width, float height);
    CREATE_FUNC(GameOverDialog);
};

#endif