#include <string.h>
#include <jni.h>
#include <stdint.h>
#include "hqxcommon.h"
#include "hqx.h"

#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

JNIEXPORT void JNICALL
Java_org_ebookdroid_common_bitmaps_RawBitmap_nativeHq4x(JNIEnv* env, jclass classObject, jintArray srcArray,
                                                          jintArray dstArray, jint width, jint height)
{

    jint* src;
    jint* dst;

    src = (*env)->GetIntArrayElements(env, srcArray, 0);
    dst = (*env)->GetIntArrayElements(env, dstArray, 0);

    hq4x_32(src, dst, width, height);

    (*env)->ReleaseIntArrayElements(env, srcArray, src, 0);
    (*env)->ReleaseIntArrayElements(env, dstArray, dst, 0);
}

JNIEXPORT void JNICALL
 Java_org_ebookdroid_common_bitmaps_RawBitmap_nativeHq3x(JNIEnv* env, jclass classObject, jintArray srcArray,
                                                          jintArray dstArray, jint width, jint height)
{

    jint* src;
    jint* dst;

    src = (*env)->GetIntArrayElements(env, srcArray, 0);
    dst = (*env)->GetIntArrayElements(env, dstArray, 0);

    hq3x_32(src, dst, width, height);

    (*env)->ReleaseIntArrayElements(env, srcArray, src, 0);
    (*env)->ReleaseIntArrayElements(env, dstArray, dst, 0);
}

JNIEXPORT void JNICALL
 Java_org_ebookdroid_common_bitmaps_RawBitmap_nativeHq2x(JNIEnv* env, jclass classObject, jintArray srcArray,
                                                          jintArray dstArray, jint width, jint height)
{

    jint* src;
    jint* dst;

    src = (*env)->GetIntArrayElements(env, srcArray, 0);
    dst = (*env)->GetIntArrayElements(env, dstArray, 0);

    hq2x_32(src, dst, width, height);

    (*env)->ReleaseIntArrayElements(env, srcArray, src, 0);
    (*env)->ReleaseIntArrayElements(env, dstArray, dst, 0);
}


JNIEXPORT void JNICALL
 Java_org_ebookdroid_common_bitmaps_RawBitmap_nativeInvert(JNIEnv* env, jclass classObject, jintArray srcArray,
                                                          jint width, jint height)
{
    jint* src;
	int i;

    src = (*env)->GetIntArrayElements(env, srcArray, 0);

    for (i = 0; i < width * height; i++) {
    	src[i] ^= 0x00FFFFFF;
    }

    (*env)->ReleaseIntArrayElements(env, srcArray, src, 0);
}

JNIEXPORT void JNICALL
 Java_org_ebookdroid_common_bitmaps_RawBitmap_nativeContrast(JNIEnv* env, jclass classObject, jintArray srcArray,
                                                          jint width, jint height, jint contrast)
{
    jint* src;
    int i, a;
    unsigned char buf[256];
    int midBright = 0;
    unsigned char* src1;

    src = (*env)->GetIntArrayElements(env, srcArray, 0);

	src1 = (unsigned char*)src;

    for (i = 0; i < width * height * 4; i += 4) {
        midBright += src1[i+2] * 77 + src1[i + 1] * 150 + src1[i] * 29;
    }
    midBright /= (256 * width * height);

    for (i = 0; i < 256; i++) {
        a = (((i - midBright) * contrast) / 256) + midBright;
        if (a < 0) {
            buf[i] = 0;
        } else if (a > 255) {
            buf[i] = 255;
        } else {
            buf[i] = a;
        }
    }

    for (i = 0; i < width * height * 4; i+=4) {
        src1[i] = buf[src1[i]];
        src1[i+1] = buf[src1[i+1]];
        src1[i+2] = buf[src1[i+2]];
    }

    (*env)->ReleaseIntArrayElements(env, srcArray, src, 0);
}

JNIEXPORT void JNICALL
 Java_org_ebookdroid_common_bitmaps_RawBitmap_nativeExposure(JNIEnv* env, jclass classObject, jintArray srcArray,
                                                          jint width, jint height, jint exp)
{
    jint* src;
    int i, a;
    unsigned char* src1;

    src = (*env)->GetIntArrayElements(env, srcArray, 0);

    src1 = (unsigned char*)src;

    for (i = 0; i < width * height * 4; i += 4) {
        src1[i] = MIN(MAX(src1[i] + exp * 11 / 100, 0), 255);
        src1[i+1] = MIN(MAX(src1[i+1] + exp * 59 / 100, 0), 255);
        src1[i+2] = MIN(MAX(src1[i+2] + exp * 30 / 100, 0), 255);
    }

    (*env)->ReleaseIntArrayElements(env, srcArray, src, 0);
}
