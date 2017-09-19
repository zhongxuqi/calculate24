#include "SimpleAudioEngine.h"
#include "GameDialog.h"
#include "../base/Colors.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace ui;
using namespace cocos2d::extension;

GameDialog::GameDialog() : contentLayer(Layer::create()), borderWidth(4) {

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
    auto contentSize = gameDialog->contentLayer->getContentSize();

    // add background
    auto backGround = DrawNode::create();
    gameDialog->points = new Vec2[4]{
        Vec2(0, 0),
        Vec2(contentSize.width, 0),
        Vec2(contentSize.width, contentSize.height * 3 / 4 - 10),
        Vec2(0, contentSize.height * 3 / 4 - 10),
    };
    backGround->drawPolygon(gameDialog->points, 4, Color4F(Colors::Transparent), gameDialog->borderWidth, Color4F(Colors::White));
    backGround->setPosition(Point(0, contentSize.height / 4 + 10));
    backGround->setAnchorPoint(Point(0, 0));
    gameDialog->contentLayer->addChild(backGround, 0);

    gameDialog->addStars();

    gameDialog->addBackButton();
    gameDialog->addRestartButton();

    return gameDialog;
}

void GameDialog::addStars() {
    auto contentSize = this->contentLayer->getContentSize();
    auto edgeLimit = PhysicsBody::createEdgePolygon(this->points, 4, PhysicsMaterial(0.1f, 1.0f, 0.0f), 1);
    edgeLimit->setDynamic(false);
    edgeLimit->setPositionOffset(Vec2(-contentSize.width/2, contentSize.height / 4 + 10 - contentSize.height / 2));
    this->contentLayer->addComponent(edgeLimit);

    auto dialogSize = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setGravityEnable(true);

    //create a sprite
    auto sprite = Sprite::create("res/Star.png");
    sprite->setPosition(Point(dialogSize.width / 2, dialogSize.height / 2));
    this->addChild(sprite);

    //apply physicsBody to the sprite
    sprite->addComponent(physicsBody);
    sprite->getPhysicsBody()->setCategoryBitmask(0x02);
    sprite->getPhysicsBody()->setCollisionBitmask(0x01);
}

void GameDialog::addBackButton() {
    auto contentSize = this->contentLayer->getContentSize();
    auto button = BtnGameQuit::create(contentSize.width / 2 - 10, contentSize.height / 4 - 10);
    button->setAnchorPoint(Point(0, 0));
    button->setPosition(Point(0, 0));
    this->contentLayer->addChild(button);
}

void GameDialog::addRestartButton() {
    auto contentSize = this->contentLayer->getContentSize();
    auto button = BtnGameResume::create(contentSize.width / 2 - 10, contentSize.height / 4 - 10);
    button->setAnchorPoint(Point(1, 0));
    button->setPosition(Point(contentSize.width, 0));
    this->contentLayer->addChild(button);
}

void GameDialog::SetScore(int score) {
    std::stringstream numberStr;
    numberStr << "Score: " << score;
    numberStr.str();
}