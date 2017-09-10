#include "SimpleAudioEngine.h"
#include "LevelBar.h"
#include "cocos-ext.h"
#include "../base/Colors.h"

USING_NS_CC;
using namespace cocos2d::extension;

LevelBar::LevelBar(): ContentLayer(LayerColor::create()) {
    
}

bool LevelBar::init() {
    if (!Layer::init()) {
        return false;
    }
    this->level = 1;
    return true;
}

void LevelBar::SetLevel(int level) {
    this->level = level;
    std::stringstream levelStr;
    levelStr << this->level;
    this->levelLabel->setString(levelStr.str());
}

int LevelBar::GetLevel() {
    return this->level;
}

LevelBar* LevelBar::create(float width, float height) {
    auto levelBar = LevelBar::create();
    levelBar->setContentSize(Size(width, height));
    levelBar->setIgnoreAnchorPointForPosition(false);

    // add level image
    auto levelImg = Sprite::create("res/IconLevel.png");
    levelImg->setAnchorPoint(Point(0, 0.5));
    levelImg->setScale(height/levelImg->getContentSize().height);
    levelImg->setPosition(Point(0, height/2));
    levelBar->addChild(levelImg, 1);

    // add content layer
    levelBar->ContentLayer->setContentSize(Size(width - levelImg->getContentSize().width * height/levelImg->getContentSize().height / 2, height * 0.7));
    levelBar->ContentLayer->setIgnoreAnchorPointForPosition(false);
    auto bgLevelBar = Scale9Sprite::create("res/BgLevel.png", Rect(0, 0, 200, 68), Rect(50, 20, 100, 28));
    bgLevelBar->setContentSize(levelBar->ContentLayer->getContentSize());
    bgLevelBar->setAnchorPoint(Point(0, 0));
    levelBar->ContentLayer->addChild(bgLevelBar, 0);
    levelBar->ContentLayer->setAnchorPoint(Point(1, 0.5));
    levelBar->ContentLayer->setPosition(Point(width, height /2));
    levelBar->addChild(levelBar->ContentLayer, 0);

    // add score text
    levelBar->levelLabel = Label::createWithTTF("0", "fonts/arial.ttf", height / 2);
    levelBar->levelLabel->setAnchorPoint(Point(1, 0.5));
    auto contentSize = levelBar->ContentLayer->getContentSize();
    levelBar->levelLabel->setPosition(Point(contentSize.width - 20, contentSize.height * 0.5));
    levelBar->levelLabel->setTextColor(Colors::BgColor);
    levelBar->ContentLayer->addChild(levelBar->levelLabel, 0);

    return levelBar;
}