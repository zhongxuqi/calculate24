#include "SimpleAudioEngine.h"
#include "SingleGameScene.h"
#include "../components/BgGameDefault.h"
#include "../components/SolutionDialog.h"
#include "../components/SolutionBoard.h"
#include "../base/GameEngine.h"
#include "../utils/TimeUtils.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;

SingleGameScene* SingleGameScene::createWithPhysics() {
    SingleGameScene *ret = new (std::nothrow) SingleGameScene();
    if (ret && ret->initWithPhysics()) {
        ret->autorelease();
        return ret;
    } else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool SingleGameScene::initWithPhysics() {
    if (!Scene::initWithPhysics()) {
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

    // add level bar
    this->levelBar = LevelBar::create(visibleSize.width * 0.25, visibleSize.height / 18);
    this->levelBar->setAnchorPoint(Point(0, 1));
    this->levelBar->setPosition(origin.x + 20, origin.y + visibleSize.height - 20);
    this->addChild(this->levelBar, 0);

    // add target bar
    this->targetBar = TargetBar::create(visibleSize.width * 0.25, visibleSize.height / 18);
    this->targetBar->setAnchorPoint(Point(0, 1));
    this->targetBar->setPosition(origin.x + 20, origin.y + visibleSize.height * 17 / 18 - 40);
    this->addChild(this->targetBar, 0);

    // add judge btn
    this->btnGameJudge = BtnGameJudge::create(visibleSize.width * 0.25, visibleSize.height / 18);
    this->btnGameJudge->setAnchorPoint(Point(0, 1));
    this->btnGameJudge->setPosition(origin.x + 20, origin.y + visibleSize.height * 8 / 9 - 60);
    this->addChild(this->btnGameJudge, 0);
    this->btnGameJudge->SetOnClickListener([this]() {
        gameEngine->JudgeLevel();
    });

    // add starbox
    this->starBox = StarBox::create(visibleSize.width * 0.75 - 60, visibleSize.height / 6 + 40);
    this->starBox->setAnchorPoint(Point(1, 1));
    this->starBox->setPosition(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 20);
    this->addChild(this->starBox, 0);

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
            this->starBox->AddScore();
            this->btnGameJudge->SetPassState(gameEngine->GetScore()>=gameEngine->GetRoundTarget());
        }
    });

    // add number matrix
    this->numberMatrix = NumberMatrix::create(visibleSize.width - 40, visibleSize.height - visibleSize.height / 6 - 60);
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

    // start game
    gameEngine->SetOnStartListener([this]() {
        this->numberMatrix->StartGame();
        this->levelBar->SetLevel(gameEngine->GetLevel());
        this->targetBar->SetTarget(gameEngine->GetRoundTarget());
        this->dialog->setZOrder(-1);
        this->btnGameJudge->SetPassState(gameEngine->GetScore()>=gameEngine->GetRoundTarget());
    });
    gameEngine->StartGame();
    gameEngine->SetOnEndListener([this]() {
        Director::getInstance()->popScene();
    });

    return true;
}

void SingleGameScene::addStarBox() {

}

void SingleGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}