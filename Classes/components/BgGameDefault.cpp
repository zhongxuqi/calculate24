#include "SimpleAudioEngine.h"
#include "BgGameDefault.h"
#include "../base/Colors.h"

USING_NS_CC;

BgGameDefault* BgGameDefault::create(float width, float height) {
    auto bgGameDefault = new BgGameDefault();
    bgGameDefault->initWithColor(Colors::BgColor);
    bgGameDefault->setContentSize(CCSizeMake(width, height));
    return bgGameDefault;
}