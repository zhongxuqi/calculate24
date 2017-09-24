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
    static void SetStringPref(char *key, const char *value) {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "PutStringPref", "(Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring keyStr = methodInfo.env->NewStringUTF(key);
            jstring valueStr = methodInfo.env->NewStringUTF(value);
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, keyStr, valueStr);
        }
    }
    static std::string GetStringPref(char *key) {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "GetStringPref", "(Ljava/lang/String;)Ljava/lang/String;")) {
            jstring keyStr = methodInfo.env->NewStringUTF(key);
            jstring result = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, keyStr);
            return methodInfo.env->GetStringUTFChars(result, 0);
        }
    }
    static void SetBoolPref(char *key, bool value) {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "PutBoolPref", "(Ljava/lang/String;Z)V")) {
            jstring keyStr = methodInfo.env->NewStringUTF(key);
            auto valueBool = value?JNI_TRUE:JNI_FALSE;
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, keyStr, valueBool);
        }
    }
    static bool GetBoolPref(char *key) {
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "GetBoolPref", "(Ljava/lang/String;)Z")) {
            jstring keyStr = methodInfo.env->NewStringUTF(key);
            auto result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, keyStr);
            return result == JNI_TRUE?true:false;
        }
    }
};

#endif