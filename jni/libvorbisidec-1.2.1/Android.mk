LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := vorbis

VORBIS_LIBRARY_PATH := ../libvorbisidec-1.2.1

SUPPORT_OGG := true
OGG_LIBRARY_PATH := ../libogg-1.3.1

LOCAL_C_INCLUDES := $(LOCAL_PATH)

	ifeq ($(TARGET_ARCH_ABI),armeabi)
	LOCAL_CFLAGS += -D_ARM_ASSEM_ -DOC_ARM_ASM=1 -D_LOW_ACCURACY_ -O3 -mfpu=neon -mcpu=cortex-a8
    endif
    ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	LOCAL_CFLAGS += -D_ARM_ASSEM_ -DOC_ARM_ASM=1 -D_LOW_ACCURACY_ -O3 -mfpu=neon -mcpu=cortex-a8
    endif

LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(OGG_LIBRARY_PATH)/include $(LOCAL_PATH)/$(VORBIS_LIBRARY_PATH)
LOCAL_CFLAGS += -DOGG_MUSIC -DOGG_USE_TREMOR

# Add your application source files here...
LOCAL_SRC_FILES := \
	$(VORBIS_LIBRARY_PATH)/mdct.c \
	$(VORBIS_LIBRARY_PATH)/block.c \
	$(VORBIS_LIBRARY_PATH)/window.c \
	$(VORBIS_LIBRARY_PATH)/synthesis.c \
	$(VORBIS_LIBRARY_PATH)/info.c \
	$(VORBIS_LIBRARY_PATH)/floor1.c \
	$(VORBIS_LIBRARY_PATH)/floor0.c \
	$(VORBIS_LIBRARY_PATH)/vorbisfile.c \
	$(VORBIS_LIBRARY_PATH)/res012.c \
	$(VORBIS_LIBRARY_PATH)/mapping0.c \
	$(VORBIS_LIBRARY_PATH)/registry.c \
	$(VORBIS_LIBRARY_PATH)/codebook.c \
	$(VORBIS_LIBRARY_PATH)/sharedbook.c \
	$(OGG_LIBRARY_PATH)/src/framing.c \
	$(OGG_LIBRARY_PATH)/src/bitwise.c

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)
LOCAL_LDFLAGS := -Wl,--allow-multiple-definition
LOCAL_ARM_MODE := arm

#LOCAL_SHARED_LIBRARIES := ogg

include $(BUILD_SHARED_LIBRARY)
