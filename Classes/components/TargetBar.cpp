#include "SimpleAudioEngine.h"
#include "TargetBar.h"
#include "cocos-ext.h"
#include "../base/Colors.h"

USING_NS_CC;
using namespace cocos2d::extension;

TargetBar::TargetBar(): ContentLayer(LayerColor::create()) {
    
}

bool TargetBar::init() {
    if (!Layer::init()) {
        return false;
    }
    this->target = 1;
    return true;
}

void TargetBar::SetTarget(int target) {
    this->target = target;
    std::stringstream targetStr;
    targetStr << this->target;
    this->targetLabel->setString(targetStr.str());
}

int TargetBar::GetTarget() {
    return this->target;
}

TargetBar* TargetBar::create(float width, float height) {
    auto targetBar = TargetBar::create();
    targetBar->setContentSize(Size(width, height));
    targetBar->setIgnoreAnchorPointForPosition(false);

    // add level image
    auto targetImg = Sprite::create("res/IconTarget.png");
    targetImg->setAnchorPoint(Point(0, 0.5));
    targetImg->setScale(height/targetImg->getContentSize().height);
    targetImg->setPosition(Point(0, height/2));
    targetBar->addChild(targetImg, 1);

    // add content layer
    targetBar->ContentLayer->setContentSize(Size(width - targetImg->getContentSize().width * height/targetImg->getContentSize().height / 2, height * 0.7));
    targetBar->ContentLayer->setIgnoreAnchorPointForPosition(false);
    auto bgTargetBar = Scale9Sprite::create("res/BgScoreBar.png", Rect(0, 0, 39, 28), Rect(6, 6, 27, 16));
    bgTargetBar->setContentSize(targetBar->ContentLayer->getContentSize());
    bgTargetBar->setAnchorPoint(Point(0, 0));
    targetBar->ContentLayer->addChild(bgTargetBar, 0);
    targetBar->ContentLayer->setAnchorPoint(Point(1, 0.5));
    targetBar->ContentLayer->setPosition(Point(width, height /2));
    targetBar->addChild(targetBar->ContentLayer, 0);

    // add target text
    targetBar->targetLabel = Label::createWithTTF("0", "fonts/arial.ttf", height / 2);
    targetBar->targetLabel->setAnchorPoint(Point(1, 0.5));
    auto contentSize = targetBar->ContentLayer->getContentSize();
    targetBar->targetLabel->setPosition(Point(contentSize.width - 20, contentSize.height * 0.5));
    targetBar->targetLabel->setTextColor(Colors::White);
    targetBar->ContentLayer->addChild(targetBar->targetLabel, 0);

    return targetBar;
}