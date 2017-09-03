#include "SimpleAudioEngine.h"
#include "SingleGameScene.h"
#include "../components/BgGameDefault.h"
#include "../components/ScoreBar.h"
#include "../components/TimeBar.h"

USING_NS_CC;

Scene* SingleGameScene::createScene() {
    return SingleGameScene::create();
}

bool SingleGameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // add event
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SingleGameScene::onKeyReleased, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add background
    auto LayerBgGameDefault = BgGameDefault::create(visibleSize.width, visibleSize.height);
    LayerBgGameDefault->setPosition(origin);
    this->addChild(LayerBgGameDefault, 0);

    // add user score
    auto scoreBar = ScoreBar::create(visibleSize.width * 0.25, visibleSize.height / 18);
    auto scoreBarSize = scoreBar->GetRootNode()->getContentSize();
    scoreBar->GetRootNode()->setAnchorPoint(Point(0, 1));
    scoreBar->GetRootNode()->setPosition(origin.x + 20, origin.y + visibleSize.height - 20);
    this->addChild(scoreBar->GetRootNode(), 0);

    // add time bar
    auto timeBar = TimeBar::create(visibleSize.width - scoreBarSize.width - 60, visibleSize.height / 18);
    auto timeBarSize = timeBar->GetRootNode()->getContentSize();
    timeBar->GetRootNode()->setAnchorPoint(Point(1, 1));
    timeBar->GetRootNode()->setPosition(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 20);
    this->addChild(timeBar->GetRootNode(), 0);

    // add number matrix
    this->numberMatrix = NumberMatrix::create(visibleSize.width - 40, visibleSize.height * 0.7);
    this->numberMatrix->GetRootNode()->setAnchorPoint(Point(0.5, 0));
    this->numberMatrix->GetRootNode()->setPosition(visibleSize.width / 2, 40);
    this->addChild(this->numberMatrix->GetRootNode(), 0);

    return true;
}

void SingleGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}