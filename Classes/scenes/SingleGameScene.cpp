#include "SimpleAudioEngine.h"
#include "SingleGameScene.h"
#include "../components/BgGameDefault.h"
#include "../components/SolutionDialog.h"
#include "../components/SolutionBoard.h"
#include "../base/GameEngine.h"
#include "../utils/TimeUtils.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;

Scene* SingleGameScene::createScene() {
    return SingleGameScene::create();
}

bool SingleGameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    gameEngine->StartGame();

    // setup schedule
    schedule(schedule_selector(SingleGameScene::updateCustom), 0.1f, kRepeatForever, 0);

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
    this->scoreBar = ScoreBar::create(visibleSize.width * 0.25, visibleSize.height / 18);
    auto scoreBarSize = this->scoreBar->getContentSize();
    this->scoreBar->setAnchorPoint(Point(0, 1));
    this->scoreBar->setPosition(origin.x + 20, origin.y + visibleSize.height - 20);
    this->addChild(this->scoreBar, 0);

    // add time bar
    this->timeBar = TimeBar::create(visibleSize.width - scoreBarSize.width - 60, visibleSize.height / 18);
    auto timeBarSize = this->timeBar->getContentSize();
    this->timeBar->setAnchorPoint(Point(1, 1));
    this->timeBar->setPosition(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 20);
    this->addChild(this->timeBar, 0);

    // add dialog
    this->dialog = SolutionDialog::create(visibleSize.width - 40, visibleSize.width - 40);
    this->dialog->setAnchorPoint(Point(0.5, 0.5));
    this->dialog->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(this->dialog, -1);
    this->dialog->setZOrder(-1);
    this->dialog->SetOnFinishListener([this](InputStep* inputSteps[3]) {
        if (this->numberMatrix->PushSolution(inputSteps)) {
            this->dialog->setZOrder(-1);
            this->numberMatrix->setTouchable(true);
            this->scoreBar->SetScore(this->scoreBar->GetScore() + 1);
        }
    });

    // add number matrix
    this->numberMatrix = NumberMatrix::create(visibleSize.width - 40, visibleSize.height * 0.7);
    this->numberMatrix->setAnchorPoint(Point(0.5, 0));
    this->numberMatrix->setPosition(visibleSize.width / 2, 20);
    this->numberMatrix->setTouchable(true);
    this->numberMatrix->SetOnSelectListener([this](AccurateNumber *accurateNumber[4]) {
        this->dialog->setZOrder(1);
        this->dialog->SetNumbers(accurateNumber);
        this->numberMatrix->setTouchable(false);

        // add close listener
        this->dialog->SetOnCloseListener([this](Ref* pRef) {
            this->dialog->setZOrder(-1);
            this->numberMatrix->setTouchable(true);
            this->numberMatrix->CancelSelectBlock();
        });
    });
    this->addChild(this->numberMatrix, 0);

    return true;
}

void SingleGameScene::updateCustom(float dt) {
    gameEngine->TimeTick();
    auto startTime = gameEngine->GetStartTime();
    auto currTime = TimeUtils::getCurrentTime();
    if (currTime - startTime > ROUND_TIME) {
        this->timeBar->SetPercent(0);
    } else if (currTime < startTime) {
        this->timeBar->SetPercent(100);
    } else {
        this->timeBar->SetPercent(100.0 * (ROUND_TIME + startTime - currTime) / ROUND_TIME);
    }
}

void SingleGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}