#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "../scenes/MainScene.h"
#include "../scenes/SingleGameScene.h"

extern "C" {
    void Java_org_cocos2dx_cpp_AppActivity_QuitGame(JNIEnv *env, jobject thiz) {
        auto singleGameScene = SingleGameScene::Instance;
        if (singleGameScene != NULL) {
            singleGameScene->QuitGame();
        }
    }

    void Java_org_cocos2dx_cpp_AppActivity_NewGame(JNIEnv *env, jobject thiz) {
        auto singleGameScene = SingleGameScene::Instance;
        if (singleGameScene != NULL) {
            singleGameScene->NewGame();
        }
    }

    void Java_org_cocos2dx_cpp_AppActivity_ResumeGame(JNIEnv *env, jobject thiz) {
        auto singleGameScene = SingleGameScene::Instance;
        if (singleGameScene != NULL) {
            singleGameScene->ResumeGame();
        }
    }

    void Java_org_cocos2dx_cpp_AppActivity_QuitAPP(JNIEnv *env, jobject thiz) {
        auto mainScene = MainScene::Instance;
        if (mainScene != NULL) {
            mainScene->QuitAPP();
        }
    }
}