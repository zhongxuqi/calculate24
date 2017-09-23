#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "../scenes/SingleGameScene.h"

extern "C" {
    void Java_org_cocos2dx_cpp_AppActivity_QuitGame(JNIEnv *env, jobject thiz) {
        CCLOG("===>>> Java_org_cocos2dx_cpp_AppActivity_QuitGame");
        auto singleGameScene = SingleGameScene::Instance;
        if (singleGameScene != NULL) {
            singleGameScene->QuitGame();
        }
    }

    void Java_org_cocos2dx_cpp_AppActivity_EndGame(JNIEnv *env, jobject thiz) {
        CCLOG("===>>> Java_org_cocos2dx_cpp_AppActivity_EndGame");
        auto singleGameScene = SingleGameScene::Instance;
        if (singleGameScene != NULL) {
            singleGameScene->EndGame();
        }
    }
}