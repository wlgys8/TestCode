LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := testcode_libfreetype_static
LOCAL_MODULE_FILENAME := freetype
LOCAL_SRC_FILES := lib/libfreetype.dll.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
