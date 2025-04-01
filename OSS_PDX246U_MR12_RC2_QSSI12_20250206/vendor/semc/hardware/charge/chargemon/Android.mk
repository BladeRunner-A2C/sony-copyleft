LOCAL_PATH := $(call my-dir)

ifeq ($(PRODUCT_AAPT_PREF_CONFIG), hdpi)
    CHARGER_IMAGE_SRC_PATH := $(LOCAL_PATH)/hdpi
else ifeq ($(PRODUCT_AAPT_PREF_CONFIG), xhdpi)
    CHARGER_IMAGE_SRC_PATH := $(LOCAL_PATH)/hdpi
else
    CHARGER_IMAGE_SRC_PATH := $(LOCAL_PATH)/xxhdpi
endif

PATH_IMAGE_DATA := /vendor/charge/chargemon/data

# Crate directory for chargemon icon.
$(shell mkdir -p $(PRODUCT_OUT)$(PATH_IMAGE_DATA)/msg)
$(shell mkdir -p $(PRODUCT_OUT)$(PATH_IMAGE_DATA)/num)
$(shell mkdir -p $(PRODUCT_OUT)$(PATH_IMAGE_DATA)/scale)

# Copy chargemon icon to /vendor/charge/chargemon/data.
$(shell cp -r $(CHARGER_IMAGE_SRC_PATH)/msg $(PRODUCT_OUT)$(PATH_IMAGE_DATA))
$(shell cp -r $(CHARGER_IMAGE_SRC_PATH)/num $(PRODUCT_OUT)$(PATH_IMAGE_DATA))
$(shell cp -r $(CHARGER_IMAGE_SRC_PATH)/scale $(PRODUCT_OUT)$(PATH_IMAGE_DATA))


include $(CLEAR_VARS)
ifeq ($(ANDROID_O_OR_LATER),true)
LOCAL_MODULE_OWNER := somc
LOCAL_PROPRIETARY_MODULE := true
endif #ANDROID_O_OR_LATER

LOCAL_SRC_FILES := \
    src/main.c \
    src/utils.c \
    src/hw.c \
    src/display.c \
    src/png.c \
    src/graphics.c \
    src/record_timestamp.c \

LOCAL_CFLAGS := -g -Wall -v -Wextra -Werror

LOCAL_CFLAGS += -DPATH_IMAGE_DATA=\"$(PATH_IMAGE_DATA)\"

LOCAL_C_INCLUDES += external/libpng
LOCAL_C_INCLUDES += external/zlib

ifneq ($(MISCTA_INC_PATH),)
LOCAL_C_INCLUDES += $(MISCTA_INC_PATH)
else
LOCAL_C_INCLUDES += vendor/semc/system/core/miscta/libmiscta/inc
endif

LOCAL_STATIC_LIBRARIES := \
	libpng

LOCAL_SHARED_LIBRARIES := \
        libz \
        libmiscta \
        libcutils \
        libdrm

ifeq ($(CFG_SOMC_THERMAL),yes)
LOCAL_C_INCLUDES += vendor/semc/hardware/thermal
LOCAL_CFLAGS += -DCFG_SOMC_THERMAL
LOCAL_SHARED_LIBRARIES += libsomc_thermal
endif

LOCAL_MODULE := chargemon
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
