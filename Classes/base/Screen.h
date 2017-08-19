#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "cocos2d.h"

class Screen {
protected:
    Screen() {

    }
    static Screen *instance;

public:
    cocos2d::Size FrameSize;

    static Screen* GetInstance();
};

#endif