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
    this->starNum = 0;
    this->moonNum = 0;
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
    starBox->iconSize = (starBoxSize.height - 2 * BORDER_OFFSET) / 10;

    // add edge
    auto edgeLimit = PhysicsBody::createEdgeBox(starBoxSize, PhysicsMaterial(0.1f, 1.0f, 0.0f), 10);
    edgeLimit->setDynamic(false);
    edgeLimit->setPositionOffset(Vec2(0, 0));
    starBox->addComponent(edgeLimit);

    // add background
    auto backGround = Scale9Sprite::create("res/BgStarBox.png", Rect(0, 0, 94, 94), Rect(30, 30, 34, 34));
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

void StarBox::addSun(float width, float height) {
    auto starBoxSize = this->getContentSize();
    auto sprite = Sprite::create("res/ScoreSun.png");
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(width, height));
    sprite->setScale(this->iconSize / sprite->getContentSize().height);
    this->addChild(sprite, 0);
    
    //apply physicsBody to the sprite
    auto linkItem = new PhysicsBodyLink{};
    linkItem->Body = PhysicsBody::createBox(Size(this->iconSize, this->iconSize));
    linkItem->Body->setGravityEnable(false);
    linkItem->Body->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, RandomHelper::random_real(-1.0, 1.0) * 100));
    sprite->addComponent(linkItem->Body);

    linkItem->Next = this->linkHead;
    this->linkHead = linkItem;
}

void StarBox::addMoon(float width, float height) {
    if (this->moonNum >= LEVEL_UP_NUMBER) return;
    auto starBoxSize = this->getContentSize();
    auto sprite = Sprite::create("res/ScoreMoon.png");
    this->moons[this->moonNum++] = sprite;
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(width, height));
    sprite->setScale(this->iconSize / sprite->getContentSize().height);
    auto moonBody = PhysicsBody::createBox(Size(this->iconSize, this->iconSize));
    moonBody->setGravityEnable(false);
    moonBody->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, RandomHelper::random_real(-1.0, 1.0) * 100));
    sprite->addComponent(moonBody);
    this->addChild(sprite, 0);

    // merge moons
    if (this->moonNum >= LEVEL_UP_NUMBER) {
        this->moonNum = 0;
        auto targetMoon = this->moons[LEVEL_UP_NUMBER - 1];
        targetMoon->getPhysicsBody()->setCollisionBitmask(0x0);
        auto targetPosition = targetMoon->getPosition();
        for(int i = 0; i < LEVEL_UP_NUMBER; i++) {
            auto moon = this->moons[i];
            moon->getPhysicsBody()->setCollisionBitmask(0x0);
            moon->getPhysicsBody()->setVelocity(Vec2(0, 0));
            if (i < LEVEL_UP_NUMBER - 1) {
                auto callFunc = CallFunc::create([this, moon]() {
                    this->removeChild(moon);
                });
                moon->runAction(Sequence::create(MoveTo::create(this->duration, targetPosition), callFunc, NULL));
            } else {
                auto callFunc = CallFunc::create([this, moon, targetPosition]() {
                    this->removeChild(moon);
                    this->addSun(targetPosition.x, targetPosition.y);
                });
                moon->runAction(Sequence::create(MoveTo::create(this->duration, targetPosition), callFunc, NULL));
            }
        }
    }
}

void StarBox::addStar(float width, float height) {
    if (this->starNum >= LEVEL_UP_NUMBER) return;
    auto starBoxSize = this->getContentSize();
    auto sprite = Sprite::create("res/ScoreStar.png");
    this->stars[this->starNum++] = sprite;
    sprite->setAnchorPoint(Point(0.5, 0.5));
    sprite->setPosition(Point(width, height));
    sprite->setScale(this->iconSize / sprite->getContentSize().height);
    auto starBody = PhysicsBody::createBox(Size(this->iconSize, this->iconSize));
    starBody->setGravityEnable(false);
    starBody->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, RandomHelper::random_real(-1.0, 1.0) * 100));
    sprite->addComponent(starBody);
    this->addChild(sprite, 0);

    // merge stars
    if (this->starNum >= LEVEL_UP_NUMBER) {
        this->starNum = 0;
        auto targetStar = this->stars[LEVEL_UP_NUMBER - 1];
        targetStar->getPhysicsBody()->setCollisionBitmask(0x0);
        auto targetPosition = targetStar->getPosition();
        for(int i = 0; i < LEVEL_UP_NUMBER; i++) {
            auto star = this->stars[i];
            star->getPhysicsBody()->setCollisionBitmask(0x0);
            star->getPhysicsBody()->setVelocity(Vec2(0, 0));
            if (i < LEVEL_UP_NUMBER - 1) {
                auto callFunc = CallFunc::create([this, star]() {
                    this->removeChild(star);
                });
                star->runAction(Sequence::create(MoveTo::create(this->duration, targetPosition), callFunc, NULL));
            } else {
                auto callFunc = CallFunc::create([this, star, targetPosition]() {
                    this->removeChild(star);
                    this->addMoon(targetPosition.x, targetPosition.y);
                });
                star->runAction(Sequence::create(MoveTo::create(this->duration, targetPosition), callFunc, NULL));
            }
        }
    }
}

void StarBox::AddScore(float width, float height) {
    this->score++;
    std::stringstream numberStr;
    numberStr << this->score;
    this->scoreLabel->setString(numberStr.str());
    auto starBoxSize = this->getContentSize();

    if (width < BORDER_OFFSET) {
        width = BORDER_OFFSET;
    } else if (width > starBoxSize.width - BORDER_OFFSET) {
        width = starBoxSize.width - BORDER_OFFSET;
    }
    if (height < BORDER_OFFSET) {
        height = BORDER_OFFSET;
    } else if (height > starBoxSize.height - BORDER_OFFSET) {
        height = starBoxSize.height - BORDER_OFFSET;
    }

    CCLOG("starNum: %d moonNum: %d", this->starNum, this->moonNum);
    // add star
    this->addStar(width, height);
}

void StarBox::SetForce(float forceX, float forceY) {

    // add force to stars
    for (int i = 0; i < this->starNum; i++) {
        this->stars[i]->getPhysicsBody()->resetForces();
        this->stars[i]->getPhysicsBody()->applyForce(Vec2(-forceX * 100, -forceY * 100));
    }

    // add force to moons
    for (int i = 0; i < this->moonNum; i++) {
        this->moons[i]->getPhysicsBody()->resetForces();
        this->moons[i]->getPhysicsBody()->applyForce(Vec2(-forceX * 100, -forceY * 100));
    }

    // add force to suns
    auto currLink = this->linkHead;
    while (currLink!=NULL) {
        currLink->Body->resetForces();
        currLink->Body->applyForce(Vec2(-forceX * 100, -forceY * 100));
        currLink = currLink->Next;
    }
}

void StarBox::SetScore(int score) {
    this->score = score;
    std::stringstream numberStr;
    numberStr << this->score;
    this->scoreLabel->setString(numberStr.str());

    auto starBoxSize = this->getContentSize();

    float BORDER_OFFSET = 20;
    float width = starBoxSize.width - 2 * BORDER_OFFSET;
    float height = starBoxSize.height - 2 * BORDER_OFFSET;

    int cnt = 0;

    // add stars
    auto numberOfStar = this->score % LEVEL_UP_NUMBER;
    CCLOG("numberOfStar: %d", numberOfStar);
    for (int i = 0; i < numberOfStar; i++) {
        this->stars[i] = Sprite::create("res/ScoreStar.png");
        this->stars[i]->setAnchorPoint(Point(0.5, 0.5));
        this->stars[i]->setScale(this->iconSize / this->stars[i]->getContentSize().height);
        auto starSize = this->stars[i]->getContentSize();
        this->stars[i]->setPosition(Point(cnt / LEVEL_UP_NUMBER * this->iconSize + this->iconSize / 2 + BORDER_OFFSET, \
            cnt % LEVEL_UP_NUMBER * this->iconSize + this->iconSize / 2 + BORDER_OFFSET));
        auto starBody = PhysicsBody::createBox(Size(this->iconSize, this->iconSize));
        starBody->setGravityEnable(false);
        starBody->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, \
            RandomHelper::random_real(-1.0, 1.0) * 100));
        this->stars[i]->addComponent(starBody);
        this->addChild(this->stars[i], 0);
        cnt++;
    }
    this->starNum = numberOfStar;

    // add moons
    auto numberOfMoon = (this->score / LEVEL_UP_NUMBER) % LEVEL_UP_NUMBER;
    CCLOG("numberOfMoon: %d", numberOfMoon);
    for (int i = 0; i < numberOfMoon; i++) {
        this->moons[i] = Sprite::create("res/ScoreMoon.png");
        this->moons[i]->setAnchorPoint(Point(0.5, 0.5));
        this->moons[i]->setScale(this->iconSize / this->moons[i]->getContentSize().height);
        auto moonSize = this->moons[i]->getContentSize();
        this->moons[i]->setPosition(Point(cnt / LEVEL_UP_NUMBER * this->iconSize + this->iconSize / 2 + BORDER_OFFSET, \
            cnt % LEVEL_UP_NUMBER * this->iconSize + this->iconSize / 2 + BORDER_OFFSET));
        auto moonBody = PhysicsBody::createBox(Size(this->iconSize, this->iconSize));
        moonBody->setGravityEnable(false);
        moonBody->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, \
            RandomHelper::random_real(-1.0, 1.0) * 100));
        this->moons[i]->addComponent(moonBody);
        this->addChild(this->moons[i], 0);
        cnt++;
    }
    this->moonNum = numberOfMoon;

    // add suns
    auto numberOfSun = (this->score / LEVEL_UP_NUMBER) / LEVEL_UP_NUMBER;
    CCLOG("numberOfSun: %d", numberOfSun);
    for (int i = 0; i < numberOfSun; i++) {
        auto sprite = Sprite::create("res/ScoreSun.png");
        sprite->setAnchorPoint(Point(0.5, 0.5));
        sprite->setScale(this->iconSize / sprite->getContentSize().height);
        auto sunSize = sprite->getContentSize();
        sprite->setPosition(Point(cnt / LEVEL_UP_NUMBER * this->iconSize + this->iconSize / 2 + BORDER_OFFSET, \
            cnt % LEVEL_UP_NUMBER * this->iconSize + this->iconSize / 2 + BORDER_OFFSET));
        this->addChild(sprite, 0);

        //apply physicsBody to the sprite
        auto linkItem = new PhysicsBodyLink{};
        linkItem->Body = PhysicsBody::createBox(Size(this->iconSize, this->iconSize));
        linkItem->Body->setGravityEnable(false);
        linkItem->Body->setVelocity(Vec2(RandomHelper::random_real(-1.0, 1.0) * 100, RandomHelper::random_real(-1.0, 1.0) * 100));
        sprite->addComponent(linkItem->Body);

        linkItem->Next = this->linkHead;
        this->linkHead = linkItem;

        cnt++;
    }
}