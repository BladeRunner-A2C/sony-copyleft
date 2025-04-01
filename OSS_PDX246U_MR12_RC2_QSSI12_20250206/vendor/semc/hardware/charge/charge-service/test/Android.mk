LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := charger_test_runner
LOCAL_CFLAGS := \
        -Ivendor/semc/hardware/charge/charge-service/ \
        -Ivendor/semc/hardware/charge/charge-service/data \
        -Ivendor/semc/hardware/charge/charge-service/test/suite

LOCAL_SRC_FILES += \
        charger_test_runner.c

LOCAL_CFLAGS += -DAGING_TEMP_TIME=900000 # 250H = 15000M = 900000S
LOCAL_C_INCLUDES += vendor/semc/system/core/miscta/libmiscta/inc

LOCAL_SHARED_LIBRARIES := \
        libc \
        libcutils \
        libutils \
        libmiscta \

LOCAL_MODULE_TAGS := optional userdebug
include $(BUILD_EXECUTABLE)
