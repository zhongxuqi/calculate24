#ifndef __BG_GAME_DEFAULT_H__
#define __BG_GAME_DEFAULT_H__

#include "cocos2d.h"

class BgGameDefault : public cocos2d::LayerColor {
protected:
    virtual bool init();

public:
    static BgGameDefault* create(float width, float height);
    CREATE_FUNC(BgGameDefault);
};

#endif