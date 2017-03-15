//
// Created by 赖振奇 on 2017/3/3.
//
#include <jni.h>
#include <rc4.h>

#define ENCODER_UTIL_METHOD(METHOD_NAME) \
    Java_me_olivine_encoder_EncoderUtil_##METHOD_NAME

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jbyteArray JNICALL
ENCODER_UTIL_METHOD(nativeCrypt)(JNIEnv *env, jclass type, jbyteArray src);

extern const char key[];

JNIEXPORT jbyteArray JNICALL
ENCODER_UTIL_METHOD(nativeCrypt)(JNIEnv *env, jclass type, jbyteArray srcArray) {
    jbyte *src = env->GetByteArrayElements(srcArray, 0);
    jsize length = env->GetArrayLength(srcArray);

    rc4_init(key);
    RC4Data rc4Data = rc4_crypt((const uint8_t *) src, (size_t) length);
    jbyteArray result = env->NewByteArray(length);
    env->SetByteArrayRegion(result, 0, rc4Data.length, (const jbyte *) rc4Data.data);

    release_rc4data(&rc4Data);
    rc4_release();
    env->ReleaseByteArrayElements(srcArray, src, 0);

    return result;
}

#ifdef __cplusplus
}
#endif