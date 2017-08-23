#include "SimpleAudioEngine.h"
#include "PersonalInfo.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

PersonalInfo::PersonalInfo(): ContentLayer(LayerColor::create()) {
    
}

void PersonalInfo::SetHeadImage(Sprite* headImg) {
    auto contentSize = this->ContentLayer->getContentSize();
    auto headImgSize = Size(contentSize.height * 0.7, contentSize.height * 0.7);
    headImg->setContentSize(headImgSize);
    headImg->setAnchorPoint(Point(0, 0));
    headImg->setPosition(20, contentSize.height * 0.15);
    this->ContentLayer->addChild(headImg, 0);
}

PersonalInfo* PersonalInfo::create(float width, float height) {
    auto personalInfo = new PersonalInfo();
    personalInfo->ContentLayer->setContentSize(Size(width, height));
    auto bgPersonalInfo = Scale9Sprite::create("BgPersonalInfo.png", Rect(0, 0, 39, 28), Rect(6, 6, 27, 16));
    bgPersonalInfo->setContentSize(Size(width, height));
    bgPersonalInfo->setAnchorPoint(Point(0, 0));
    personalInfo->ContentLayer->addChild(bgPersonalInfo, 0);
    personalInfo->SetHeadImage(Sprite::create("default_head_image.png"));
    return personalInfo;
}