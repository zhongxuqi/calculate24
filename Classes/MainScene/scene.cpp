#include "SimpleAudioEngine.h"
#include "scene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto layer = LayerColor::create(Color4B(0, 128, 128, 255));
    layer->setContentSize(CCSizeMake(120, 80));
    layer->setPosition(Point(300, 450));
    addChild(layer, 10);

    // 添加背景
    auto bgMain = Sprite::create("BgMain.png");
    bgMain->setScale(2.0);
    this->addChild(bgMain,0);
}