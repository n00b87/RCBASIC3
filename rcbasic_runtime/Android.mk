LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
VORBIS_LIBRARY_PATH := ../libvorbisidec-1.2.1
THEORAPLAY_PATH :=

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
VORBIS_LIBRARY_PATH := ../libvorbis64
THEORAPLAY_PATH := ../src/theoraplay
endif

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
VORBIS_LIBRARY_PATH := ../libvorbisidec-1.2.1
THEORAPLAY_PATH := ../src/theoraplay_tremor
endif

LOCAL_CFLAGS := -I$(LOCAL_PATH)/$(THEORAPLAY_PATH) -DRC_ANDROID_BUILD

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../SDL2_image/include $(LOCAL_PATH)/../SDL2_ttf/include $(LOCAL_PATH)/../SDL2_mixer/include $(LOCAL_PATH)/../SDL2_net/include $(LOCAL_PATH)/../SDL2_gfx $(LOCAL_PATH)/../theora $(LOCAL_PATH)/$(VORBIS_LIBRARY_PATH)/include $(LOCAL_PATH)/$(THEORAPLAY_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp \
	$(THEORAPLAY_PATH)/theoraplay.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf SDL2_mixer SDL2_net SDL2_gfx

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SHARED_LIBRARIES += ogg vorbis64 theora
#LOCAL_CFLAGS += -DRC_USE_TREMOR
endif

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_SHARED_LIBRARIES += ogg vorbis theora
LOCAL_CFLAGS += -DRC_USE_TREMOR
endif

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
