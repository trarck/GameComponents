LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_common

LOCAL_MODULE_FILENAME := libgamecommon

LOCAL_SRC_FILES := \
Classes/Message/CCMessageHandler.cpp \
Classes/Message/CCMessage.cpp \
Classes/Message/CCMessageManager.cpp \
Classes/Components/Component.cpp \
Classes/Components/ComponentEntity.cpp \
Classes/Components/AttackComponent.cpp \
Classes/Components/AutoAttackComponent.cpp \
Classes/Components/ManualAttackComponent.cpp \
Classes/Components/AnimationComponent.cpp \
Classes/Components/SimpleMoveComponent.cpp \
Classes/Entities/GameEntity.cpp \
Classes/Entities/Monster.cpp \
Classes/Entities/Player.cpp  \
Classes/AppDelegate.cpp \
Classes/HelloWorldScene.cpp 

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)  $(LOCAL_PATH)/Classes  $(LOCAL_PATH)/Classes/Message  $(LOCAL_PATH)/Classes/Components  $(LOCAL_PATH)/Classes/Entities

LOCAL_EXPORT_LDLIBS := -llog\
                       -lz \
                       -lGLESv2

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/Classes  $(LOCAL_PATH)/Classes/Message  $(LOCAL_PATH)/Classes/Components  $(LOCAL_PATH)/Classes/Entities

include $(BUILD_STATIC_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)
