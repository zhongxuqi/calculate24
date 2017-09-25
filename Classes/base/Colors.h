#ifndef __COLORS_H__
#define __COLORS_H__

#include "cocos2d.h"
#include "GameEngine.h"

class Colors {
public:
    static cocos2d::Color4B Transparent;
    static cocos2d::Color4B HalfTransparent;
    static cocos2d::Color4B White;
    static cocos2d::Color4B BgColor;
    static cocos2d::Color4B OutNumberColor;
    static cocos2d::Color4B *NumberColors;
    static cocos2d::Color4B Number24DefaultColor;
    static cocos2d::Color4B Number24FailColor;
    static cocos2d::Color4B Number24SuccessColor;
    static cocos2d::Color4B DangerColor;
    static cocos2d::Color4B SuccessColor;

    static cocos2d::Color4B GetColorsByNumber(AccurateNumber *accurateNumber);
};

#endif