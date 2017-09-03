#ifndef __SINGLE_GAME_SCENE_H__
#define __SINGLE_GAME_SCENE_H__

#include "cocos2d.h"
#include "../components/NumberMatrix.h"

class SingleGameScene : public cocos2d::Scene {
protected:
    NumberMatrix* numberMatrix;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SingleGameScene);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif