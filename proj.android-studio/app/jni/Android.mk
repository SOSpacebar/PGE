LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path, $(LOCAL_PATH))

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
$(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
$(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
$(LOCAL_PATH)/../../../Classes/Asteroid.cpp \
$(LOCAL_PATH)/../../../Classes/AudioManager.cpp \
$(LOCAL_PATH)/../../../Classes/Buildings.cpp \
$(LOCAL_PATH)/../../../Classes/Bullet.cpp \
$(LOCAL_PATH)/../../../Classes/Character.cpp \
$(LOCAL_PATH)/../../../Classes/Constants.cpp \
$(LOCAL_PATH)/../../../Classes/GameObject.cpp \
$(LOCAL_PATH)/../../../Classes/GameStats.cpp \
$(LOCAL_PATH)/../../../Classes/Humans.cpp \
$(LOCAL_PATH)/../../../Classes/LoadingScene.cpp \
$(LOCAL_PATH)/../../../Classes/LoseMenu.cpp \
$(LOCAL_PATH)/../../../Classes/MainMenu.cpp \
$(LOCAL_PATH)/../../../Classes/SceneManager.cpp \
$(LOCAL_PATH)/../../../Classes/Settings.cpp \
$(LOCAL_PATH)/../../../Classes/UpgradeMenu.cpp \
$(LOCAL_PATH)/../../../Classes/Wave.cpp \
$(LOCAL_PATH)/../../../Classes/WaveSpawner.cpp \
$(LOCAL_PATH)/../../../Classes/WinMenu.cpp

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED \
-DSDKBOX_COCOS_CREATOR
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_WHOLE_STATIC_LIBRARIES += PluginFacebook
LOCAL_WHOLE_STATIC_LIBRARIES += sdkbox

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginfacebook)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
