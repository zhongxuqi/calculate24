#ifndef __COLORS_H__
#define __COLORS_H__

#include "cocos2d.h"

class Colors {
public:
    static cocos2d::Color4B Transparent;
    static cocos2d::Color4B White;
    static cocos2d::Color4B BgColor;
    static cocos2d::Color4B OutNumberColor;
    static cocos2d::Color4B NumberColors[];
    static cocos2d::Color4B GetColorsByNumber(int);
};

#endif