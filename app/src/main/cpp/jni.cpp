/**
 * ©2022, SUZUKI PLAN
 * License: https://github.com/suzukiplan/tohovgs4-android/blob/master/LICENSE.txt
 */
#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include "vgsdec.h"
#include "vgsmml.h"
#include "vge.h"
#include "vgeint.h"

extern "C" JNIEXPORT jlong JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_createDecoder(JNIEnv *, jclass) {
    return (jlong) vgsdec_create_context();
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_releaseDecoder(JNIEnv *, jclass, jlong context) {
    if (context) {
        vgsdec_release_context((void *) context);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_load(JNIEnv *env, jclass, jlong context, jbyteArray mml_) {
    if (context) {
        jbyte *mml = env->GetByteArrayElements(mml_, nullptr);
        size_t size = (uint32_t) env->GetArrayLength(mml_);
        if (mml) {
            VgsMmlErrorInfo err{};
            VgsBgmData *data = vgsmml_compile_from_memory2(mml, size, &err);
            if (data) {
                vgsdec_load_bgm_from_memory((void *) context, data->data, data->size);
                vgsmml_free_bgm_data(data);
            }
            env->ReleaseByteArrayElements(mml_, mml, 0);
        }
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_decode(JNIEnv *env, jclass, jlong context, jbyteArray buf_) {
    if (context) {
        jbyte *buf = env->GetByteArrayElements(buf_, nullptr);
        size_t size = (uint32_t) env->GetArrayLength(buf_);
        if (buf) {
            vgsdec_execute((void *) context, buf, size);
            env->ReleaseByteArrayElements(buf_, buf, 0);
        }
    }
}

extern "C" JNIEXPORT jint JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_loopCount(JNIEnv *, jclass, jlong context) {
    if (context) {
        return vgsdec_get_value((void *) context, VGSDEC_REG_LOOP_COUNT);
    }
    return 0;
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_fadeout(JNIEnv *, jclass, jlong context) {
    if (context) {
        vgsdec_set_value((void *) context, VGSDEC_REG_FADEOUT, 100);
    }
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_isPlaying(JNIEnv *, jclass, jlong context) {
    if (context) {
        return vgsdec_get_value((void *) context, VGSDEC_REG_PLAYING) ? JNI_TRUE : JNI_FALSE;
    }
    return JNI_FALSE;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_getTimeLength(JNIEnv *, jclass, jlong context) {
    if (context) {
        return vgsdec_get_value((void *) context, VGSDEC_REG_TIME_LENGTH);
    } else {
        return 0;
    }
}

extern "C" JNIEXPORT jint JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_getTime(JNIEnv *, jclass, jlong context) {
    if (context) {
        return vgsdec_get_value((void *) context, VGSDEC_REG_TIME);
    } else {
        return 0;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_seek(JNIEnv *, jclass, jlong context, jint progress) {
    if (context) {
        vgsdec_set_value((void *) context, VGSDEC_REG_TIME, progress);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatCleanUp(JNIEnv *, jclass) {
    tohovgs_cleanUp();
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatAllocate(JNIEnv *, jclass, jint nTitle, jint nSong) {
    tohovgs_allocate(nTitle, nSong);
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatLoadGraphic(JNIEnv *env, jclass, jint n,
                                                      jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, nullptr);
    vge_gload(n & 0xFF, (const unsigned char *) data);
    env->ReleaseByteArrayElements(data_, data, 0);
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatLoadKanji(JNIEnv *env, jclass, jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, nullptr);
    size_t size = (uint32_t) env->GetArrayLength(data_);
    tohovgs_loadKanji(data, size);
    env->ReleaseByteArrayElements(data_, data, 0);
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatAddTitle(JNIEnv *env, jclass,
                                                   jint index,
                                                   jint id,
                                                   jint songNum,
                                                   jbyteArray title_,
                                                   jbyteArray copyright_) {
    jbyte *title = env->GetByteArrayElements(title_, nullptr);
    size_t titleSize = (uint32_t) env->GetArrayLength(title_);
    jbyte *copyright = env->GetByteArrayElements(copyright_, nullptr);
    size_t copyrightSize = (uint32_t) env->GetArrayLength(copyright_);
    tohovgs_setTitle(index, id, songNum, title, titleSize, copyright, copyrightSize);
    env->ReleaseByteArrayElements(copyright_, copyright, 0);
    env->ReleaseByteArrayElements(title_, title, 0);
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatAddSong(JNIEnv *env, jclass,
                                                  jint index,
                                                  jint id,
                                                  jint no,
                                                  jint loop,
                                                  jint col,
                                                  jbyteArray mmlPath_,
                                                  jbyteArray title_) {
    //__android_log_print(ANDROID_LOG_DEBUG, "TOHOVGS", "addSong:%04X-%d", id, no);
    jbyte *title = env->GetByteArrayElements(title_, nullptr);
    size_t titleSize = (uint32_t) env->GetArrayLength(title_);
    jbyte *mmlPath = env->GetByteArrayElements(mmlPath_, nullptr);
    size_t mmlPathSize = (uint32_t) env->GetArrayLength(mmlPath_);
    tohovgs_setSong(index, id, no, loop, col, mmlPath, mmlPathSize, title, titleSize);
    env->ReleaseByteArrayElements(mmlPath_, mmlPath, 0);
    env->ReleaseByteArrayElements(title_, title, 0);
}

extern "C" JNIEXPORT void JNICALL
Java_com_suzukiplan_tohovgs_api_JNI_compatTick(JNIEnv *env, jclass, jobject bitmap) {
    unsigned short *pixels;
    vge_tick();
    if (AndroidBitmap_lockPixels(env, bitmap, (void **) &pixels) < 0) return;
    int index = 0;
    for (int y = 0; y < 320; y++) {
        for (int x = 0; x < 240; x++) {
            pixels[index] = _vram.pal[_vram.sp[index]];
            index++;
        }
    }
    AndroidBitmap_unlockPixels(env, bitmap);
}
