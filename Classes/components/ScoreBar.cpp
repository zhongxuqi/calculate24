#include "SimpleAudioEngine.h"
#include "ScoreBar.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

ScoreBar::ScoreBar(): ContentLayer(LayerColor::create()) {
    
}

bool ScoreBar::init() {
    if (!Layer::init()) {
        return false;
    }
    this->score = 0;
    return true;
}

void ScoreBar::SetScore(int score) {
    this->score = score;
    std::stringstream numberStr;
    numberStr << this->score;
    this->scoreLabel->setString(numberStr.str());
}

int ScoreBar::GetScore() {
    return this->score;
}

ScoreBar* ScoreBar::create(float width, float height) {
    auto scoreBar = ScoreBar::create();
    scoreBar->setContentSize(Size(width, height));
    scoreBar->setIgnoreAnchorPointForPosition(false);

    // add star image
    auto starImg = Sprite::create("res/Star.png");
    starImg->setAnchorPoint(Point(0, 0.5));
    starImg->setScale(height/starImg->getContentSize().height);
    starImg->setPosition(Point(0, height/2));
    scoreBar->addChild(starImg, 1);

    // add content layer
    scoreBar->ContentLayer->setContentSize(Size(width - starImg->getContentSize().width * height/starImg->getContentSize().height / 2, height * 0.7));
    scoreBar->ContentLayer->setIgnoreAnchorPointForPosition(false);
    auto bgScoreBar = Scale9Sprite::create("res/BgScoreBar.png", Rect(0, 0, 39, 28), Rect(6, 6, 27, 16));
    bgScoreBar->setContentSize(scoreBar->ContentLayer->getContentSize());
    bgScoreBar->setAnchorPoint(Point(0, 0));
    scoreBar->ContentLayer->addChild(bgScoreBar, 0);
    scoreBar->ContentLayer->setAnchorPoint(Point(1, 0.5));
    scoreBar->ContentLayer->setPosition(Point(width, height /2));
    scoreBar->addChild(scoreBar->ContentLayer, 0);

    // add score text
    scoreBar->scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", height / 2);
    scoreBar->scoreLabel->setAnchorPoint(Point(1, 0.5));
    auto contentSize = scoreBar->ContentLayer->getContentSize();
    scoreBar->scoreLabel->setPosition(Point(contentSize.width - 20, contentSize.height * 0.5));
    scoreBar->ContentLayer->addChild(scoreBar->scoreLabel, 0);

    return scoreBar;
}