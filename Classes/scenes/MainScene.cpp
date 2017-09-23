#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "../components/BgMain.h"
#include "../components/PersonalInfo.h"
#include "../components/BtnNormalMode.h"
#include "../components/BtnOnlineBattle.h"
#include "SingleGameScene.h"
#include "../utils/PreferenceUtils.h"
#include "../base/GameEngine.h"

USING_NS_CC;

MainScene* MainScene::Instance = NULL;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init() {
    if (!Scene::init()) {
        return false;
    }
    MainScene::Instance = this;

    // add event
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add background
    auto LayerBgMain = BgMain::create(visibleSize.width, visibleSize.height);
    LayerBgMain->setPosition(origin);
    this->addChild(LayerBgMain, 0);

    // add user info
    auto personalInfo = PersonalInfo::create(visibleSize.width * 0.4, visibleSize.height / 18);
    auto personalInfoSize = personalInfo->getContentSize();
    personalInfo->setAnchorPoint(Point(0, 1));
    personalInfo->setPosition(origin.x + 20, origin.y + visibleSize.height - 20);
    this->addChild(personalInfo, 0);

    // add user score
    this->scoreBar = ScoreBar::create(visibleSize.width * 0.25, visibleSize.height / 18);
    auto scoreBarSize = this->scoreBar->getContentSize();
    this->scoreBar->setAnchorPoint(Point(1, 1));
    this->scoreBar->setPosition(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 20);
    this->addChild(this->scoreBar, 0);
    this->UpdateScore();

    // add normal mode btn
    auto btnNormalMode = BtnNormalMode::create(visibleSize.width - 40, visibleSize.height * 0.3);
    auto btnNormalModeSize = btnNormalMode->getContentSize();
    btnNormalMode->setAnchorPoint(Point(0.5, 0));
    btnNormalMode->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.3 + 60);
    this->addChild(btnNormalMode, 0);
    btnNormalMode->SetOnClickListener([](Ref* pRef) {
        Director::getInstance()->pushScene(SingleGameScene::createWithPhysics());
    });

    // add online battle btn
    auto btnOnlineBattle = BtnOnlineBattle::create(visibleSize.width - 40, visibleSize.height * 0.3);
    auto btnOnlineBattleSize = btnOnlineBattle->getContentSize();
    btnOnlineBattle->setAnchorPoint(Point(0.5, 0));
    btnOnlineBattle->setPosition(origin.x + visibleSize.width / 2, origin.y + 30);
    this->addChild(btnOnlineBattle, 0);
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}

void MainScene::UpdateScore() {
    this->scoreBar->SetScore(PreferenceUtils::GetIntPref(TOP_SCORE));
}