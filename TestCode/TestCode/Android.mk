LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := testcode_static

LOCAL_MODULE_FILENAME := libtestcode

LOCAL_SRC_FILES := \
Audio/AudioManager.cpp \
Support/zip_support/ioapi.c \
Support/zip_support/unzip.c \
Commons/TCCommon.cpp \
Platform/JNI/JNIHelper.cpp \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/ \
                           $(LOCAL_PATH)/Audio \
                           $(LOCAL_PATH)/Commons \
                           $(LOCAL_PATH)/zlib \
                           $(LOCAL_PATH)/Support/zip_support \
                           $(LOCAL_PATH)/Platform \
						   $(LOCAL_PATH)/Platform/JNI/ \

LOCAL_EXPORT_LDLIBS := -llog\
                       -lz \
                       -lGLESv1_CM

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/Audio \
                    $(LOCAL_PATH)/Commons \
                    $(LOCAL_PATH)/zlib \
                    $(LOCAL_PATH)/Support/zip_support \
                    $(LOCAL_PATH)/Platform \
					$(LOCAL_PATH)/Platform/JNI/ \

LOCAL_LDLIBS := -lGLESv1_CM \
                -llog \
                -lz 
LOCAL_WHOLE_STATIC_LIBRARIES  := testcode_libpng_static
LOCAL_WHOLE_STATIC_LIBRARIES += openal_static


LOCAL_CFLAGS := -DUSE_FILE32API \
                -D_STLP_USE_NEWALLOC \

include $(BUILD_STATIC_LIBRARY)



###################################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := testcode_shared

LOCAL_MODULE_FILENAME := libtestcode

LOCAL_SRC_FILES := \
Audio/AudioManager.cpp \
Support/zip_support/ioapi.c \
Support/zip_support/unzip.c \
Commons/TCCommon.cpp \
Platform/JNI/JNIHelper.cpp \

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/ \
                           $(LOCAL_PATH)/Audio \
                           $(LOCAL_PATH)/Commons \
                           $(LOCAL_PATH)/zlib \
                           $(LOCAL_PATH)/Support/zip_support \
                           $(LOCAL_PATH)/Platform \
                           $(LOCAL_PATH)/Platform/JNI/ \

LOCAL_EXPORT_LDLIBS := -llog\
                       -lz \
                       -lGLESv1_CM

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/Audio \
                    $(LOCAL_PATH)/Commons \
                    $(LOCAL_PATH)/zlib \
                    $(LOCAL_PATH)/Support/zip_support \
                    $(LOCAL_PATH)/Platform \
                    $(LOCAL_PATH)/Platform/JNI/ \

LOCAL_LDLIBS := -lGLESv1_CM \
                -llog \
                -lz 
LOCAL_WHOLE_STATIC_LIBRARIES  := testcode_libpng_static
LOCAL_WHOLE_STATIC_LIBRARIES  += openal_static

LOCAL_CFLAGS := -DUSE_FILE32API \
                -D_STLP_USE_NEWALLOC \

include $(BUILD_SHARED_LIBRARY)

$(call import-module,libpng)
$(call import-module,libopenal)
