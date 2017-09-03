#ifndef __BG_MAIN_H__
#define __BG_MAIN_H__

#include "cocos2d.h"

class BgMain : public cocos2d::LayerColor {
public:
    static BgMain* create(float width, float height);
};

#endif