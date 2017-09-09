#include "SimpleAudioEngine.h"
#include "OperateBtn.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace ui;

void OperateBtn::SetOnClickListener(std::function<void(Ref*)> clickListener) {
    if (this->button != NULL) {
        this->button->addClickEventListener(clickListener);
    }
}

Ref *OperateBtn::GetRef() {
    return this->button;
}

char OperateBtn::GetOperator() {
    return this->operatorTxt;
}