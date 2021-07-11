LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := theora

SUPPORT_OGG := true


OGG_LIBRARY_PATH :=
THEORA_LIBRARY_PATH := ../theora

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
OGG_LIBRARY_PATH := ../libogg-1.3.1
endif

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
OGG_LIBRARY_PATH := ../libogg-1.3.1
endif

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(OGG_LIBRARY_PATH)/include $(LOCAL_PATH)/$(THEORA_LIBRARY_PATH) $(LOCAL_PATH)/$(THEORA_LIBRARY_PATH)/lib/arm

LOCAL_SHARED_LIBRARIES := ogg_shared

    ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    # These arm optimizations do not work with the modern android toolchain
	#LOCAL_CFLAGS := -D_ARM_ASSEM_ -DOC_ARM_ASM=1 -D_LOW_ACCURACY_ -O3 -mfpu=neon -mcpu=cortex-a8
	LOCAL_CFLAGS := -D_LOW_ACCURACY_ -O3 -mfpu=neon -mcpu=cortex-a8
	LOCAL_SRC_FILES := 
	#LOCAL_SRC_FILES := \
	#	$(THEORA_LIBRARY_PATH)/lib/arm/armfrag.s \
	#	$(THEORA_LIBRARY_PATH)/lib/arm/armidct.s \
	#	$(THEORA_LIBRARY_PATH)/lib/arm/armloop.s \
	#	$(THEORA_LIBRARY_PATH)/lib/arm/armstate.c \
	#	$(THEORA_LIBRARY_PATH)/lib/arm/armcpu.c \
	#	$(THEORA_LIBRARY_PATH)/lib/arm/armbits.s
	LOCAL_CFLAGS += -DOGG_MUSIC -DOGG_USE_TREMOR -DOGG_HEADER="<ivorbisfile.h>"
	endif
    
    ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
	LOCAL_CFLAGS := -D_LOW_ACCURACY_ -O2
	#LOCAL_CFLAGS += -DOGG_MUSIC -DOGG_USE_TREMOR -DOGG_HEADER="<ivorbisfile.h>"
	LOCAL_SRC_FILES :=
    endif
    
    LOCAL_SRC_FILES += \
        $(THEORA_LIBRARY_PATH)/lib/analyze.c \
		$(THEORA_LIBRARY_PATH)/lib/apiwrapper.c \
		$(THEORA_LIBRARY_PATH)/lib/bitpack.c \
		$(THEORA_LIBRARY_PATH)/lib/collect.c \
		$(THEORA_LIBRARY_PATH)/lib/decapiwrapper.c \
		$(THEORA_LIBRARY_PATH)/lib/decinfo.c \
		$(THEORA_LIBRARY_PATH)/lib/decode.c \
		$(THEORA_LIBRARY_PATH)/lib/dequant.c \
		$(THEORA_LIBRARY_PATH)/lib/encapiwrapper.c \
		$(THEORA_LIBRARY_PATH)/lib/encfrag.c \
		$(THEORA_LIBRARY_PATH)/lib/encinfo.c \
		$(THEORA_LIBRARY_PATH)/lib/encode.c \
		$(THEORA_LIBRARY_PATH)/lib/arm/armenc.c \
		$(THEORA_LIBRARY_PATH)/lib/encoder_disabled.c \
		$(THEORA_LIBRARY_PATH)/lib/enquant.c \
		$(THEORA_LIBRARY_PATH)/lib/fdct.c \
		$(THEORA_LIBRARY_PATH)/lib/fragment.c \
		$(THEORA_LIBRARY_PATH)/lib/huffdec.c \
		$(THEORA_LIBRARY_PATH)/lib/huffenc.c \
		$(THEORA_LIBRARY_PATH)/lib/idct.c \
		$(THEORA_LIBRARY_PATH)/lib/info.c \
		$(THEORA_LIBRARY_PATH)/lib/internal.c \
		$(THEORA_LIBRARY_PATH)/lib/mathops.c \
		$(THEORA_LIBRARY_PATH)/lib/mcenc.c \
		$(THEORA_LIBRARY_PATH)/lib/quant.c \
		$(THEORA_LIBRARY_PATH)/lib/rate.c \
		$(THEORA_LIBRARY_PATH)/lib/state.c \
		$(THEORA_LIBRARY_PATH)/lib/tokenize.c
		#$(THEORA_LIBRARY_PATH)/lib/arm_llvm/armcpu.c \
		#$(THEORA_LIBRARY_PATH)/lib/arm_llvm/armenc.c \
		#$(THEORA_LIBRARY_PATH)/lib/arm_llvm/armstate.c

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)
LOCAL_LDFLAGS := -Wl,--allow-multiple-definition
LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)
