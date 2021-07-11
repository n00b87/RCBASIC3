LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_IMAGE_PATH := ../SDL2_image
SDL_MIXER_PATH := ../SDL2_mixer
SDL_TTF_PATH := ../SDL2_ttf
SDL_NET_PATH := ../SDL2_net
SDL_GFX_PATH := ../SDL2_gfx
THEORA_PATH := ../theora

VORBIS_LIBRARY_PATH := ../libvorbis64
THEORAPLAY_PATH := ../src/theoraplay

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
VORBIS_LIBRARY_PATH := ../libvorbisidec-1.2.1
THEORAPLAY_PATH := ../src/theoraplay_tremor
endif

LOCAL_CFLAGS := -I$(LOCAL_PATH)/$(THEORAPLAY_PATH) -DRC_ANDROID_BUILD

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
					$(LOCAL_PATH)/$(SDL_IMAGE_PATH) \
					$(LOCAL_PATH)/$(SDL_MIXER_PATH) \
					$(LOCAL_PATH)/$(SDL_TTF_PATH) \
					$(LOCAL_PATH)/$(SDL_NET_PATH) \
					$(LOCAL_PATH)/$(SDL_GFX_PATH) \
					$(LOCAL_PATH)/$(THEORA_PATH) \
					$(LOCAL_PATH)/$(VORBIS_LIBRARY_PATH)/include \
					$(LOCAL_PATH)/$(THEORAPLAY_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := main.cpp $(THEORAPLAY_PATH)/theoraplay.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf SDL2_net SDL2_gfx

RC_TH_LOCAL_SHARED_LIBRARIES := ogg_shared vorbis64 theora

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
RC_TH_LOCAL_SHARED_LIBRARIES := ogg_shared tremor theora
LOCAL_CFLAGS += -DRC_USE_TREMOR -O2
endif

LOCAL_SHARED_LIBRARIES += $(RC_TH_LOCAL_SHARED_LIBRARIES)

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
