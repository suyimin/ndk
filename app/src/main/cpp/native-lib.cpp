#include <jni.h>
#include <string>
#include <android/log.h>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_ndk_MainActivity_stringFromJNI(JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    __android_log_print(ANDROID_LOG_DEBUG, "zj", "%s", "Hello, World");
    return env->NewStringUTF(hello.c_str());
}
