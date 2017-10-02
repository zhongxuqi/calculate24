#ifndef __STAR_BOX_H__
#define __STAR_BOX_H__

#include "cocos2d.h"

const int LEVEL_UP_NUMBER = 10;
const float BORDER_OFFSET = 10;

struct PhysicsBodyLink {
    cocos2d::PhysicsBody *Body;
    PhysicsBodyLink *Next;
};

class StarBox : public cocos2d::Layer {
protected:
    const float borderWidth;
    virtual bool init();
    cocos2d::Label *scoreLabel;
    int score;
    PhysicsBodyLink *linkHead;
    cocos2d::Sprite *stars[LEVEL_UP_NUMBER];
    int starNum;
    cocos2d::Sprite *moons[LEVEL_UP_NUMBER];
    int moonNum;
    const float duration = 0.2;
    void addStar(float width, float height);
    void addMoon(float width, float height);
    void addSun(float width, float height);
    float borderOffset;
    float iconSize;

public:
    StarBox();
    ~StarBox();
    static StarBox* create(float width, float height);
    CREATE_FUNC(StarBox);
    static StarBox* Instance;
    void AddScore(float width, float height);
    void SetForce(float forceX, float forceY);
    void SetScore(int score);
};

#endif