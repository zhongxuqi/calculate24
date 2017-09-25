#include "SimpleAudioEngine.h"
#include "StarBox.h"
#include "../base/Colors.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace ui;
using namespace cocos2d::extension;

StarBox* StarBox::Instance = NULL;

StarBox::StarBox() : borderWidth(4.0) {
    StarBox::Instance = this;
    this->score = 0;
    this->linkHead = NULL;
}

StarBox::~StarBox() {
    StarBox::Instance = NULL;
}

bool StarBox::init() {
    if (!Layer::init()) {
        return false;
    }
    return true;
}

StarBox* StarBox::create(float width, float height) {
    auto starBox = StarBox::create();
    starBox->setContentSize(Size(width, height));
    starBox->setIgnoreAnchorPointForPosition(false);
    auto starBoxSize = starBox->getContentSize();

    // add edge
    auto edgeLimit = PhysicsBody::createEdgeBox(starBoxSize, PhysicsMaterial(0.1f, 1.0f, 0.0f), 10);
    edgeLimit->setDynamic(false);
    edgeLimit->setPositionOffset(Vec2(0, 0));
    starBox->addComponent(edgeLimit);

    // add background
    auto backGround = Scale9Sprite::create("res/StarBoxFrame.png", Rect(0, 0, 285, 385), Rect(100, 100, 85, 185));
    backGround->setContentSize(starBoxSize);
    backGround->setPosition(Point(0, 0));
    backGround->setAnchorPoint(Point(0, 0));
    starBox->addChild(backGround, 0);

    // add score label
    starBox->scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", starBoxSize.height / 4);
    starBox->scoreLabel->setAnchorPoint(Point(0.5, 0.5));
    starBox->scoreLabel->setPosition(Point(starBoxSize.width / 2, starBoxSize.height / 2));
    starBox->scoreLabel->setTextColor(Colors::White);
    starBox->addChild(starBox->scoreLabel, 1);

    return starBox;
}

void StarBox::AddScore() {
    this->score++;
    std::stringstream numberStr;
    numberStr << this->score;
    this->scoreLabel->setString(numberStr.str());
    auto starBoxSize = this->getContentSize();

    // add star
    auto sprite = Sprite::create("res/Star.png");
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(starBoxSize.width / 2, starBoxSize.height / 2));
    sprite->setScale(starBoxSize.height / 10 / sprite->getContentSize().height);
    this->addChild(sprite, 0);

    //apply physicsBody to the sprite
    auto linkItem = new PhysicsBodyLink{};
    linkItem->Body = PhysicsBody::createBox(sprite->getContentSize());
    linkItem->Body->setGravityEnable(false);
    linkItem->Body->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, RandomHelper::random_real(-1.0, 1.0) * 100));
    sprite->addComponent(linkItem->Body);

    linkItem->Next = this->linkHead;
    this->linkHead = linkItem;
}

void StarBox::SetForce(float forceX, float forceY) {
    auto currLink = this->linkHead;
    while (currLink!=NULL) {
        currLink->Body->resetForces();
        currLink->Body->applyForce(Vec2(-forceX * 1000, -forceY * 1000));
        currLink = currLink->Next;
    }
}