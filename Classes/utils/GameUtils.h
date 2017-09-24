#ifndef __GAME_UTILS_H__
#define __GAME_UTILS_H__

#include "cocos2d.h"

class GameUtils {
public:
    static void AlertQuitGame() {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "AlertQuitGame", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
    }

    static void AlertEndGame() {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "AlertEndGame", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
    }

    static void AlertResumeGame() {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "AlertResumeGame", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
    }

    static void AlertQuitAPP() {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "AlertQuitAPP", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
    }
};

#endif