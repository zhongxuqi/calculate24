#include "SimpleAudioEngine.h"
#include "SingleGameScene.h"
#include "../components/BgGameDefault.h"
#include "../components/SolutionDialog.h"
#include "../components/SolutionBoard.h"
#include "../base/GameEngine.h"
#include "../utils/TimeUtils.h"
#include "../utils/PreferenceUtils.h"
#include "../utils/GameUtils.h"
#include "MainScene.h"

USING_NS_CC;

GameEngine* const gameEngine = GameEngine::Instance;
SingleGameScene* SingleGameScene::Instance = NULL;

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
    
    SingleGameScene::Instance = this;
    this->isSoluting = false;

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

    // add action star
    this->actionStar = Sprite::create("res/Star.png");
    this->actionStar->setAnchorPoint(Point(0.5, 0.5));
    this->actionStar->setScale(visibleSize.height / 60 / this->actionStar->getContentSize().height);
    this->actionStar->setVisible(false);
    this->addChild(this->actionStar, 1);

    // add starbox
    this->starBox = StarBox::create(visibleSize.width - 40, visibleSize.height / 6 + 40);
    this->starBox->setAnchorPoint(Point(0, 1));
    this->starBox->setPosition(origin.x + 20, origin.y + visibleSize.height - 20);
    this->addChild(this->starBox, 0);

    // add dialog
    this->dialog = SolutionDialog::create(visibleSize.width - 40, visibleSize.width - 40);
    this->dialog->setAnchorPoint(Point(0.5, 0.5));
    this->dialog->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(this->dialog, -1);
    this->dialog->setZOrder(-1);
    this->dialog->SetOnFinishListener([this](InputStep* inputSteps[3]) {
        if (this->numberMatrix->PushSolution(inputSteps)) {
            this->isSoluting = false;
            this->dialog->setZOrder(-1);
            this->numberMatrix->setTouchable(true);

            auto starBoxSize = this->starBox->getContentSize();
            float width = starBoxSize.width * RandomHelper::random_real(0.0, 1.0);
            float height = starBoxSize.height * RandomHelper::random_real(0.0, 1.0);

            // add star to star box
            auto callFunc = CallFunc::create([this, width, height]() {
                this->starBox->AddScore(width, height);
                this->actionStar->setVisible(false);
            });
            auto targetPosition = Point(this->starBox->getPosition().x + width, this->starBox->getPosition().y - starBoxSize.height + height);
            auto touchPoint = this->numberMatrix->GetTouchPoint();
            this->actionStar->setVisible(true);
            this->actionStar->setPosition(Point(touchPoint.x, touchPoint.y));
            this->actionStar->runAction(Sequence::create(MoveTo::create(this->duration, targetPosition), callFunc, NULL));

            // update top score
            if (gameEngine->GetScore() > PreferenceUtils::GetIntPref(TOP_SCORE)) {
                gameEngine->SaveGame();
                PreferenceUtils::SetIntPref(TOP_SCORE, gameEngine->GetScore());
            }
        }
    });
    this->dialog->SetOnCloseListener([this](Ref* pRef) {
        this->isSoluting = false;
        this->dialog->setZOrder(-1);
        this->numberMatrix->setTouchable(true);
        this->numberMatrix->CancelSelectBlock();
    });

    // add number matrix
    this->numberMatrix = NumberMatrix::create(visibleSize.width - 40, visibleSize.height - visibleSize.height / 6 - 60);
    this->numberMatrix->setAnchorPoint(Point(0.5, 0));
    this->numberMatrix->setPosition(visibleSize.width / 2, 20);
    this->numberMatrix->setTouchable(true);
    this->numberMatrix->SetOnSelectListener([this](AccurateNumber *accurateNumber[4]) {
        this->isSoluting = true;
        this->dialog->setZOrder(1);
        this->dialog->SetNumbers(accurateNumber);
        this->numberMatrix->setTouchable(false);
    });
    this->addChild(this->numberMatrix, 0);

    // start game
    gameEngine->SetOnStartListener([this]() {
        CCLOG("gameEngine->SetOnStartListener start");
        this->isSoluting = false;
        this->numberMatrix->StartGame();
        this->dialog->setZOrder(-1);
        auto starBoxSize = this->starBox->getContentSize();
        for (int i=0; i<gameEngine->GetScore(); i++) {
            this->starBox->AddScore(starBoxSize.width * RandomHelper::random_real(0.0, 1.0), \
                starBoxSize.height * RandomHelper::random_real(0.0, 1.0));
        }
        CCLOG("gameEngine->SetOnStartListener end");
    });
    gameEngine->SetOnEndListener([this]() {
        this->QuitGame();
    });
    this->numberMatrix->setVisible(false);
    if (gameEngine->HasSaveGame()) {
        GameUtils::AlertResumeGame();
    } else {
        this->numberMatrix->setVisible(true);
        gameEngine->StartGame();
    }

    return true;
}

void SingleGameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        GameUtils::AlertQuitGame();
    }
}

void SingleGameScene::QuitGame() {
    gameEngine->SaveGame();
    Director::getInstance()->popScene();
    MainScene::Instance->UpdateScore();
    SingleGameScene::Instance = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
}

void SingleGameScene::NewGame() {
    this->numberMatrix->setVisible(true);
    gameEngine->StartGame();
}

void SingleGameScene::ResumeGame() {
    this->numberMatrix->setVisible(true);
    gameEngine->RestoreGame();
}