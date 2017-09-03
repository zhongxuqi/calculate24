#ifndef __PERSONAL_INFO_H__
#define __PERSONAL_INFO_H__

#include "cocos2d.h"

class PersonalInfo : public cocos2d::Layer {
public:
    PersonalInfo();
    cocos2d::Layer* const ContentLayer;
    void SetHeadImage(cocos2d::Sprite* headImg);
    void SetUserName(cocos2d::Label* userName);

    static PersonalInfo* create(float width, float height);
};

#endif