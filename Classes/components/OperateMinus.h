#ifndef __OPERATE_MINUS_H__
#define __OPERATE_MINUS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"
#include "OperateBtn.h"

class OperateMinus : public OperateBtn {
protected:
    virtual bool init();

public:
    static OperateMinus* create(float operateSize);
    CREATE_FUNC(OperateMinus);
};

#endif