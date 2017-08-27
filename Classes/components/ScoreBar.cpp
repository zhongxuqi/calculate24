#include "SimpleAudioEngine.h"
#include "ScoreBar.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

ScoreBar::ScoreBar(): ContentLayer(LayerColor::create()) {
    
}

void ScoreBar::SetScore(Label* score) {
    auto contentSize = this->ContentLayer->getContentSize();
    score->setAnchorPoint(Point(1, 0.5));
    score->setPosition(Point(contentSize.width - 20, contentSize.height * 0.5));
    this->ContentLayer->addChild(score, 0);
}

ScoreBar* ScoreBar::create(float width, float height) {
    auto scoreBar = new ScoreBar();
    scoreBar->RootLayer->setContentSize(Size(width, height));
    scoreBar->RootLayer->ignoreAnchorPointForPosition(false);

    // add star image
    auto starImg = Sprite::create("star.png");
    starImg->setAnchorPoint(Point(0, 0.5));
    starImg->setScale(height/starImg->getContentSize().height);
    starImg->setPosition(Point(0, height/2));
    scoreBar->RootLayer->addChild(starImg, 1);

    // add content layer
    scoreBar->ContentLayer->setContentSize(Size(width - starImg->getContentSize().width * height/starImg->getContentSize().height / 2, height * 0.7));
    scoreBar->ContentLayer->ignoreAnchorPointForPosition(false);
    auto bgScoreBar = Scale9Sprite::create("BgScoreBar.png", Rect(0, 0, 39, 28), Rect(6, 6, 27, 16));
    bgScoreBar->setContentSize(scoreBar->ContentLayer->getContentSize());
    bgScoreBar->setAnchorPoint(Point(0, 0));
    scoreBar->ContentLayer->addChild(bgScoreBar, 0);
    scoreBar->ContentLayer->setAnchorPoint(Point(1, 0.5));
    scoreBar->ContentLayer->setPosition(Point(width, height /2));
    scoreBar->RootLayer->addChild(scoreBar->ContentLayer, 0);

    scoreBar->SetScore(Label::createWithTTF("100", "default_font.ttf", 30));
    return scoreBar;
}