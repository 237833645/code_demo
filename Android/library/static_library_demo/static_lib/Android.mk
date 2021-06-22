LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_SRC_FILES := static_lib.c
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := static_lib
include $(BUILD_STATIC_LIBRARY)
