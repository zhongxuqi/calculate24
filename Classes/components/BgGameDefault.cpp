#include "SimpleAudioEngine.h"
#include "BgGameDefault.h"
#include "../base/Colors.h"

USING_NS_CC;

bool BgGameDefault::init() {
    if (!LayerColor::init()) {
        return false;
    }
    return true;
}

BgGameDefault* BgGameDefault::create(float width, float height) {
    auto bgGameDefault = BgGameDefault::create();
    bgGameDefault->initWithColor(Colors::BgColor);
    bgGameDefault->setContentSize(Size(width, height));
    return bgGameDefault;
}