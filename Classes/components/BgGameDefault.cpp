#include "SimpleAudioEngine.h"
#include "BgGameDefault.h"
#include "../base/Colors.h"

USING_NS_CC;

cocos2d::Layer* BgGameDefault::create(float width, float height) {
    auto layer = LayerColor::create(Colors::BgColor);
    layer->setContentSize(CCSizeMake(width, height));
    return layer;
}