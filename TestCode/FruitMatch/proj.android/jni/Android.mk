LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := fruit_match

LOCAL_MODULE_FILENAME := libfruitmatch

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
$(LOCAL_PATH)/../../Classes/ \
$(LOCAL_PATH)/../../Classes/Enemy \
$(LOCAL_PATH)/../../Classes/Fruit \
$(LOCAL_PATH)/../../Classes/Map \
$(LOCAL_PATH)/../../Classes/Role \
$(LOCAL_PATH)/../../Classes/UI \
$(LOCAL_PATH)/../../Classes/Data \

LOCAL_SRC_FILES := AndroidMain.cpp \
../../Classes/Data/GameData.cpp \
../../Classes/Enemy/Enemy.cpp \
../../Classes/Fruit/Bullet.cpp \
../../Classes/Fruit/BulletFactory.cpp \
../../Classes/Fruit/Fruit.cpp \
../../Classes/Map/ConnectionEffect.cpp \
../../Classes/Map/FruitMap.cpp \
../../Classes/Map/Grass.cpp \
../../Classes/Map/MapData.cpp \
../../Classes/Map/MapDataManager.cpp \
../../Classes/Role/Role.cpp \
../../Classes/UI/GameOverDialog.cpp \
../../Classes/UI/LevelEntryButton.cpp \
../../Classes/UI/LevelMenu.cpp \
../../Classes/UI/PauseDialog.cpp \
../../Classes/UI/AnimationData.cpp \
../../Classes/GameMain.cpp \
../../Classes/TestAppDelegate.cpp \
		
LOCAL_SHARED_LIBRARIES := testcode_shared	


include $(BUILD_SHARED_LIBRARY)


$(call import-module,TestCode)