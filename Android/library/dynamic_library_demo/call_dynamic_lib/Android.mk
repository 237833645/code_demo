LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc/
LOCAL_SRC_FILES := call_dynamic.c
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := call_dynamic_demo

# LOCAL_LDFLAGS := $(LOCAL_PATH)/lib/dynamic_lib.so
LOCAL_SHARED_LIBRARIES := dynamic_lib.so

include $(BUILD_EXECUTABLE)
