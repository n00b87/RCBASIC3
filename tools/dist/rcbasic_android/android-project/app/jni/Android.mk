LOCAL_PATH:= $(call my-dir)
include $(call all-subdir-makefiles)
include $(call $(LOCAL_PATH)/SDL/src/hidapi/android/jni/Android.mk)
