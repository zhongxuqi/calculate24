#ifndef __BASE_COMPONENT_H__
#define __BASE_COMPONENT_H__

#include "cocos2d.h"

class BaseComponent {
protected:
    BaseComponent();
    cocos2d::Layer* const RootLayer;

public:
    cocos2d::Layer* GetRootLayer();
};

#endif