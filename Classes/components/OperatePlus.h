#ifndef __OPERATE_PLUS_H__
#define __OPERATE_PLUS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"

class OperatePlus : public cocos2d::Layer {
protected:
    virtual bool init();

public:
    static OperatePlus* create(float operateSize);
    CREATE_FUNC(OperatePlus);
};

#endif