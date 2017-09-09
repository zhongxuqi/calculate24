#ifndef __OPERATE_PLUS_H__
#define __OPERATE_PLUS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "NumberBlock.h"
#include "OperateBtn.h"

class OperatePlus : public OperateBtn {
protected:
    virtual bool init();

public:
    static OperatePlus* create(float operateSize);
    CREATE_FUNC(OperatePlus);
};

#endif