#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "../components/BgMain.h"
#include "../components/PersonalInfo.h"
#include "../components/ScoreBar.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 添加事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加背景
    auto LayerBgMain = BgMain::create(visibleSize.width, visibleSize.height);
    LayerBgMain->setPosition(origin);
    this->addChild(LayerBgMain, 0);

    // 添加个人信息
    auto personalInfo = PersonalInfo::create(visibleSize.width * 0.35, visibleSize.height / 18);
    auto personalInfoSize = personalInfo->GetRootLayer()->getContentSize();
    personalInfo->GetRootLayer()->setAnchorPoint(Point(0, 1));
    personalInfo->GetRootLayer()->setPosition(origin.x + 20, origin.y + visibleSize.height - 20);
    this->addChild(personalInfo->GetRootLayer(), 0);

    // 添加个人纪录
    auto scoreBar = ScoreBar::create(visibleSize.width * 0.25, visibleSize.height / 18);
    auto scoreBarSize = scoreBar->GetRootLayer()->getContentSize();
    scoreBar->GetRootLayer()->setAnchorPoint(Point(1, 1));
    scoreBar->GetRootLayer()->setPosition(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 20);
    this->addChild(scoreBar->GetRootLayer(), 0);
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}