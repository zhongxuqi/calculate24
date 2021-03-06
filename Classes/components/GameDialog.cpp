#include "SimpleAudioEngine.h"
#include "GameDialog.h"
#include "../base/Colors.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace ui;
using namespace cocos2d::extension;

GameDialog* GameDialog::Instance = NULL;

GameDialog::GameDialog() : contentLayer(Layer::create()), borderWidth(4) {
    GameDialog::Instance = this;
    this->score = 0;
}

bool GameDialog::init() {
    if (!LayerColor::initWithColor(Colors::HalfTransparent)) {
        return false;
    }
    return true;
}

GameDialog* GameDialog::create(float width, float height) {
    auto gameDialog = GameDialog::create();
    gameDialog->setContentSize(Size(width, height));
    gameDialog->setIgnoreAnchorPointForPosition(false);

    gameDialog->contentLayer->setContentSize(Size(0.6 * width, height / 4));
    gameDialog->contentLayer->setIgnoreAnchorPointForPosition(false);
    gameDialog->contentLayer->setAnchorPoint(Point(0.5, 0.5));
    gameDialog->contentLayer->setPosition(Point(width / 2, height / 2));
    gameDialog->addChild(gameDialog->contentLayer, 0);

    gameDialog->addStarBox();
    gameDialog->addQuitButton();
    gameDialog->addRestartButton();

    return gameDialog;
}

void GameDialog::addStarBox() {
    auto contentSize = this->contentLayer->getContentSize();
    this->starBox = Layer::create();
    this->starBox->setContentSize(Size(contentSize.width, contentSize.height * 3 / 4 - 10));
    this->starBox->setIgnoreAnchorPointForPosition(false);
    this->starBox->setAnchorPoint(Point(0, 0));
    this->starBox->setPosition(Point(0, contentSize.height / 4 + 10));
    this->contentLayer->addChild(this->starBox, 0);
    auto starBoxSize = this->starBox->getContentSize();

    auto points = new Vec2[4]{
        Vec2(0, 0),
        Vec2(starBoxSize.width, 0),
        Vec2(starBoxSize.width, starBoxSize.height),
        Vec2(0, starBoxSize.height),
    };
    auto edgeLimit = PhysicsBody::createEdgePolygon(points, 4, PhysicsMaterial(0.1f, 1.0f, 0.0f), 1);
    edgeLimit->setDynamic(false);
    edgeLimit->setPositionOffset(Vec2(- starBoxSize.width / 2, - starBoxSize.height / 2));
    this->starBox->addComponent(edgeLimit);

    // add background
    auto backGround = DrawNode::create();
    backGround->drawPolygon(points, 4, Color4F(Colors::Transparent), this->borderWidth, Color4F(Colors::White));
    backGround->setPosition(this->starBox->getPosition());
    backGround->setAnchorPoint(Point(0, 0));
    this->contentLayer->addChild(backGround, 0);

    // add score lable
    this->scoreLabel = Label::createWithTTF("", "fonts/arial.ttf", contentSize.height / 4);
    this->scoreLabel->setAnchorPoint(Point(0.5, 0.5));
    this->scoreLabel->setPosition(Point(contentSize.width / 2, this->starBox->getPosition().y + starBoxSize.height / 2));
    this->scoreLabel->setTextColor(Colors::White);
    this->contentLayer->addChild(this->scoreLabel, 0);
}

void GameDialog::addQuitButton() {
    auto contentSize = this->contentLayer->getContentSize();
    auto button = BtnGameQuit::create(contentSize.width / 2 - 10, contentSize.height / 4 - 10);
    button->setAnchorPoint(Point(0, 0));
    button->setPosition(Point(0, 0));
    this->contentLayer->addChild(button, 0);
    button->SetOnClickListener([this]() {
        auto listener = this->quitListener;
        if (listener != NULL) {
            listener();
        }
    });
}

void GameDialog::addRestartButton() {
    auto contentSize = this->contentLayer->getContentSize();
    auto button = BtnGameRestart::create(contentSize.width / 2 - 10, contentSize.height / 4 - 10);
    button->setAnchorPoint(Point(1, 0));
    button->setPosition(Point(contentSize.width, 0));
    this->contentLayer->addChild(button, 0);
    button->SetOnClickListener([this]() {
        auto listener = this->restartListener;
        if (listener != NULL) {
            listener();
        }
    });
}

void GameDialog::SetScore(int score) {
    std::stringstream numberStr;
    numberStr << score;
    this->scoreLabel->setString(numberStr.str());

    auto starBoxSize = this->starBox->getContentSize();
    this->starBox->removeAllChildren();
    this->physicsBodies = new PhysicsBody*[score];
    for (int i=0; i<score; i++) {
    
        //create a sprite
        auto sprite = Sprite::create("res/Star.png");
        sprite->setAnchorPoint(Point(0.5, 0.5));
        sprite->setPosition(Point(starBoxSize.width * 0.2 + RandomHelper::random_real(0.0, 0.6) * starBoxSize.width, starBoxSize.height / 2));
        sprite->setScale(starBoxSize.height / 10 / sprite->getContentSize().height);
        this->starBox->addChild(sprite, 0);
        this->starSize = sprite->getContentSize();
    
        //apply physicsBody to the sprite
        this->physicsBodies[i] = PhysicsBody::createBox(this->starSize, PhysicsMaterial(0.1f, 1.0f, 0.0f));
        this->physicsBodies[i]->setGravityEnable(false);
        this->physicsBodies[i]->setVelocity(Vec2(RandomHelper::random_real(0.0, 1.0) * 100, RandomHelper::random_real(0.0, 1.0) * 100));
        sprite->addComponent(this->physicsBodies[i]);
    }
    this->score = score;
}

void GameDialog::SetForce(float forceX, float forceY) {
    auto score = this->score;
    auto physicsBodies = this->physicsBodies;
    for (int i=0; i<score; i++) {
        if (physicsBodies[i] != NULL) {
            physicsBodies[i]->applyForce(Vec2(-forceX * 1000, -forceY * 1000));
        }
    }
}

void GameDialog::SetQuitListener(std::function<void()> listener) {
    this->quitListener = listener;
}

void GameDialog::SetRestartListener(std::function<void()> listener) {
    this->restartListener = listener;
}