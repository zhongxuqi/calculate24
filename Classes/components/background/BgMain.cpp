#include "SimpleAudioEngine.h"
#include "BgMain.h"
#include "../../base/Colors.h"

USING_NS_CC;

const float PROP_BLOCK_SIZE = 15.0;

cocos2d::Layer* BgMain::create(float width, float height) {
    auto layer = LayerColor::create(Color4B(50, 54, 66, 255));
    layer->setContentSize(CCSizeMake(width, height));
    
    auto block1 = LayerColor::create(Colors::NumberColors[0]);
    block1->setContentSize(CCSizeMake(width / PROP_BLOCK_SIZE, width / PROP_BLOCK_SIZE));
    block1->setPosition(width / 2, height / 2);
    layer->addChild(block1);

    return layer;
}