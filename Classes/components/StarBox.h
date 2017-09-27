#ifndef __STAR_BOX_H__
#define __STAR_BOX_H__

#include "cocos2d.h"

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

public:
    StarBox();
    ~StarBox();
    static StarBox* create(float width, float height);
    CREATE_FUNC(StarBox);
    static StarBox* Instance;
    void AddScore(float width, float height);
    void SetForce(float forceX, float forceY);
};

#endif