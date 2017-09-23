#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "../components/ScoreBar.h"

class MainScene : public cocos2d::Scene {
protected:
    ScoreBar *scoreBar;

public:
    static cocos2d::Scene* createScene();
    static MainScene *Instance;

    virtual bool init();
    
    // a selector callback
    // void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void UpdateScore();
};

#endif