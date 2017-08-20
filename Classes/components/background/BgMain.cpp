#include "SimpleAudioEngine.h"
#include "BgMain.h"
#include "../../base/Colors.h"

USING_NS_CC;

const float PROP_BLOCK_SIZE = 15.0;

cocos2d::Layer* BgMain::create(float width, float height) {
    auto layer = LayerColor::create(Color4B(50, 54, 66, 255));
    layer->setContentSize(CCSizeMake(width, height));
    
    for (int i=0;i<14;i++) {
        auto color = Colors::NumberColors[i];
        color.a = 80;
        auto block = LayerColor::create(color);
        block->setContentSize(CCSizeMake(width / PROP_BLOCK_SIZE, width / PROP_BLOCK_SIZE));
        block->setPosition(width * RandomHelper::random_real(0.0, 1.0), height * RandomHelper::random_real(0.0, 1.0));
        block->setRotation(360 * RandomHelper::random_real(0.0, 1.0));
        block->setAnchorPoint(Vec2(0.5, 0.5));
        layer->addChild(block);
        auto rotateAction = RepeatForever::create(RotateBy::create(4, 360));
        block->runAction(rotateAction);
    }

    return layer;
}