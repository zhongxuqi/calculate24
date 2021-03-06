#ifndef __OPERATE_MULT_H__
#define __OPERATE_MULT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"
#include "OperateBtn.h"

class OperateMult : public OperateBtn {
protected:
    virtual bool init();

public:
    static OperateMult* create(float operateSize);
    CREATE_FUNC(OperateMult);
};

#endif