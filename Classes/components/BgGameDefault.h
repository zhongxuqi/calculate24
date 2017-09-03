#ifndef __BG_GAME_DEFAULT_H__
#define __BG_GAME_DEFAULT_H__

#include "cocos2d.h"

class BgGameDefault : public cocos2d::LayerColor {
public:
    static BgGameDefault* create(float width, float height);
};

#endif