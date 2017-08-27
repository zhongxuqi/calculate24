#include "SimpleAudioEngine.h"
#include "PersonalInfo.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

PersonalInfo::PersonalInfo(): ContentLayer(LayerColor::create()) {
    
}

void PersonalInfo::SetHeadImage(Sprite* headImg) {
    auto rootSize = this->GetRootLayer()->getContentSize();
    headImg->setScale(rootSize.height / headImg->getContentSize().height);
    headImg->setAnchorPoint(Point(0.5, 0.5));
    headImg->setPosition(rootSize.height * 0.5, rootSize.height * 0.5);
    this->GetRootLayer()->addChild(headImg, 0);
}

void PersonalInfo::SetUserName(Label* userName) {
    auto contentSize = this->ContentLayer->getContentSize();
    userName->setAnchorPoint(Point(1, 0.5));
    userName->setPosition(contentSize.width - 20, contentSize.height * 0.5);
    this->ContentLayer->addChild(userName, 0);
}

PersonalInfo* PersonalInfo::create(float width, float height) {
    auto personalInfo = new PersonalInfo();
    personalInfo->RootLayer->setContentSize(Size(width, height));
    personalInfo->RootLayer->ignoreAnchorPointForPosition(false);

    // add content layer
    personalInfo->ContentLayer->setContentSize(Size(width - height / 2, height * 0.8));
    personalInfo->ContentLayer->ignoreAnchorPointForPosition(false);
    auto bgPersonalInfo = Scale9Sprite::create("BgPersonalInfo.png", Rect(0, 0, 39, 28), Rect(6, 6, 27, 16));
    bgPersonalInfo->setContentSize(personalInfo->ContentLayer->getContentSize());
    bgPersonalInfo->setAnchorPoint(Point(0, 0));
    personalInfo->ContentLayer->addChild(bgPersonalInfo, 0);
    personalInfo->ContentLayer->setAnchorPoint(Point(1, 0.5));
    personalInfo->ContentLayer->setPosition(Point(width, height /2));
    personalInfo->RootLayer->addChild(personalInfo->ContentLayer, 0);

    personalInfo->SetHeadImage(Sprite::create("default_head_image.png"));
    personalInfo->SetUserName(Label::createWithTTF("User Name", "default_font.ttf", 30));
    return personalInfo;
}