#ifndef __OPERATE_DIV_H__
#define __OPERATE_DIV_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"
#include "OperateBtn.h"

class OperateDiv : public OperateBtn {
protected:
    virtual bool init();

public:
    static OperateDiv* create(float operateSize);
    CREATE_FUNC(OperateDiv);
};

#endif