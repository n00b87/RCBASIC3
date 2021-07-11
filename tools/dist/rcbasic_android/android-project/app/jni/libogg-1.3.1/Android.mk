LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ogg_shared

OGG_LIBRARY_PATH := ../libogg-1.3.1

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_CFLAGS := -Wall -D_LOW_ACCURACY_ -O2

	ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
	LOCAL_CFLAGS := -Wall -D_LOW_ACCURACY_ -O2
    endif
    ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	LOCAL_CFLAGS := -D_LOW_ACCURACY_ -O3 -mfpu=neon -mcpu=cortex-a8
    endif

# Add your application source files here...
LOCAL_SRC_FILES := \
	$(OGG_LIBRARY_PATH)/src/framing.c \
	$(OGG_LIBRARY_PATH)/src/bitwise.c

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)
LOCAL_LDFLAGS := -Wl,--allow-multiple-definition
LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)
