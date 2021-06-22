LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_SRC_FILES := dynamic_lib.c
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := dynamic_lib
include $(BUILD_SHARED_LIBRARY)
