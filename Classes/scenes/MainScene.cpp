#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "../components/background/BgMain.h"

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

    // 添加背景
    auto LayerBgMain = BgMain::create(visibleSize.width, visibleSize.height);
    LayerBgMain->setPosition(origin);
    this->addChild(LayerBgMain, 0);
}