#ifndef __BG_MAIN_H__
#define __BG_MAIN_H__

#include "cocos2d.h"

class BgMain : public cocos2d::LayerColor {
protected:
    virtual bool init();

public:
    static BgMain* create(float width, float height);

    CREATE_FUNC(BgMain);
};

#endif