#ifndef __PREFERENCE_UTILS_H__
#define __PREFERENCE_UTILS_H__

#include "cocos2d.h"

class PreferenceUtils {
public:
    static void SetIntPref(char *key, int value) {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "PutIntPref", "(Ljava/lang/String;I)V")) {
            jstring keyStr = methodInfo.env->NewStringUTF(key);
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, keyStr, value);
        }
    }
    static int GetIntPref(char *key) {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "GetIntPref", "(Ljava/lang/String;)I")) {
            jstring keyStr = methodInfo.env->NewStringUTF(key);
            return methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, keyStr, 0);
        }
        return 0;
    }
};

#endif