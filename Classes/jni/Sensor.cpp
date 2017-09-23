#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "../components/StarBox.h"

extern "C" {
    void Java_org_cocos2dx_cpp_AppActivity_PushSensorInfo(JNIEnv *env, jobject thiz, jfloat forceX, jfloat forceY) {
        CCLOG("===>>> forceX: %f, forceY: %f", forceX, forceY);
        if (StarBox::Instance != nullptr) {
            StarBox::Instance->SetForce(forceX, forceY);
        }
    }
}