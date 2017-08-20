#include "SimpleAudioEngine.h"
#include "scene.h"
#include "../base/Screen.h"

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

    auto screen = Screen::GetInstance();
    CCLOG("Screen width %f height %f", screen->VisibleSize.width, screen->VisibleSize.height);

    // 添加背景
    auto bgMain = Sprite::create("BgMain.png");
    bgMain->setScale(2.0);
    this->addChild(bgMain,0);
}