#ifndef __BASE_COMPONENT_H__
#define __BASE_COMPONENT_H__

#include "cocos2d.h"

class BaseComponent {
protected:
    BaseComponent(cocos2d::Node* node);
    cocos2d::Node* const RootNode;

public:
    cocos2d::Node* GetRootNode();
};

#endif