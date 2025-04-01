
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_OWNER := somc
LOCAL_PROPRIETARY_MODULE = true

SOMC_CFG_CHARGE_SERVICE := true

LOCAL_MODULE := charge_service
LOCAL_C_INCLUDES := \
        $(TARGET_OUT_HEADERS)/common/inc \
        vendor/semc/system/core/miscta/libmiscta/inc

LOCAL_CFLAGS := \
        -g -Wall \
        -lstringl -I$(LOCAL_PATH)

LOCAL_SRC_FILES += \
        charge-service.c \
        func/miscta_handler.c \
        func/charge_full.c \
        func/aging_mode_setter.c \
        func/lrc_mode.c \
        func/external_thermal_data.c \
        logger/charge-logging/miscta_batt_stat.c \
        logger/charge-logging/chg_insertion_removal.c \
        logger/battery-logging/battery_logging.c \
        data/uevent_processor.c \
        data/sysfs_accessor.c

LOCAL_SHARED_LIBRARIES := \
        libc \
        libcutils \
        libutils \
        libmiscta \
        liblog

ifeq ($(SONY_IDD_AVAILABLE), true)
    LOCAL_CFLAGS += -DUSE_IDD
    LOCAL_C_INCLUDES += \
        vendor/semc/system/idd/protobuf-c \
        vendor/semc/system/idd/api
    LOCAL_SRC_FILES += \
        logger/idd/idd_batt_degr2.c \
        logger/idd/idd_chg_insertion_removal.c \
        logger/idd/charging.pb-c.c
    LOCAL_SHARED_LIBRARIES += \
        libidd \
        libprotobuf-c-idd
else
    $(warning libidd is not available yet, so idd functions of charge-service are disabled.)
endif

ifneq ($(TARGET_BUILD_VARIANT),user)
    LOCAL_CFLAGS += -DBUILD_VARIANT_NOT_USER
endif

LOCAL_CFLAGS += -DSOMC_PLATFORM=\"$(SOMC_PLATFORM)\"

LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
