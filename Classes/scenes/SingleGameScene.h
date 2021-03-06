#ifndef __SINGLE_GAME_SCENE_H__
#define __SINGLE_GAME_SCENE_H__

#include "cocos2d.h"
#include "../components/NumberMatrix.h"
#include "../components/SolutionDialog.h"
#include "../components/GameDialog.h"
#include "../components/ScoreBar.h"
#include "../components/TimeBar.h"
#include "../components/LevelBar.h"
#include "../components/TargetBar.h"
#include "../components/BtnGameJudge.h"
#include "../components/StarBox.h"

class SingleGameScene : public cocos2d::Scene {
protected:
    NumberMatrix* numberMatrix;
    SolutionDialog* dialog;
    StarBox *starBox;
    void updateCustom(float dt);
    cocos2d::Sprite *actionStar;
    const float duration = 1.0;
    bool isSoluting;

public:
    virtual bool initWithPhysics();
    static SingleGameScene* Instance;

    // implement the "static create()" method manually
    static SingleGameScene *createWithPhysics(); 
    CREATE_FUNC(SingleGameScene);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void QuitGame();
    void EndGame();
    void NewGame();
    void ResumeGame();
};

#endif