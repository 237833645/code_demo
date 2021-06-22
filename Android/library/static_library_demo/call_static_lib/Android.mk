LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc/
LOCAL_SRC_FILES := call_static.c
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := call_static_demo

LOCAL_LDFLAGS := $(LOCAL_PATH)/lib/static_lib.a

include $(BUILD_EXECUTABLE)
