LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifdef OPENCV_ANDROID_SDK
  ifneq ("","$(wildcard $(OPENCV_ANDROID_SDK)/OpenCV.mk)")
    include ${OPENCV_ANDROID_SDK}/OpenCV.mk
  else
    include ${OPENCV_ANDROID_SDK}/sdk/native/jni/OpenCV.mk
  endif
else
 # full path is here because I cannot seem to get it to work with realative path
# include /Volumes/LostSideDrive/Android/workspace/OpenCV-android-sdk/sdk/native/jni/OpenCV.mk
# this is the LINE YOU NEED TO REPLACE with PATH to OpenCV on your System
include /Users/jared/Source/newestac2/android/OpenCV-android-sdk/sdk/native/jni/OpenCV.mk
endif

LOCAL_MODULE    := acidcam
LOCAL_SRC_FILES := AcidCam.cpp ../../source/fractal.cpp ../../source/ac-alpha.cpp ../../source/ac-obj.cpp ../../source/ac-util.cpp ../../source/ac-square.cpp ../../source/ac-particle.cpp ../../source/ac-grid.cpp ../../source/ac-basic.cpp ../../source/ac-filter1.cpp  ../../source/ac-filter2.cpp ../../source/ac-filter3.cpp ../../source/ac-filter4.cpp ../../source/ac-filter5.cpp ../../source/ac-filter6.cpp ../../source/ac-filter7.cpp ../../source/ac-filter8.cpp ../../source/ac-filter9.cpp ../../source/ac-filter10.cpp ../../source/ac-filter11.cpp ../../source/ac-image.cpp ../../source/ac-box.cpp ../../source/ac-filter12.cpp ../../source/ac-filter13.cpp ../../source/ac-filter14.cpp ../../source/ac-filter15.cpp  ../../source/ac-filter16.cpp ../../source/ac-filter17.cpp ../../source/ac-filter18.cpp ../../source/ac-filter19.cpp ../../source/ac-filter20.cpp ../../source/ac-filter21.cpp ../../source/ac-filter22.cpp ../../source/ac-filter23.cpp ../../source/ac-filter24.cpp ../../source/ac-filter25.cpp ../../source/ac-filter26.cpp ../../source/ac-filter27.cpp ../../source/ac-filter28.cpp ../../source/ac-filter29.cpp ../../source/ac-filter30.cpp ../../source/ac-filter31.cpp ../../source/ac-filter32.cpp ../../source/ac-filter33.cpp ../../source/ac-filter34.cpp ../../source/ac-filter35.cpp ../../source/ac-filter36.cpp ../../source/ac-filter37.cpp ../../source/ac-filter38.cpp ../../source/ac-filter39.cpp ../../source/ac-filter40.cpp ../../source/ac-filter41.cpp ../../source/ac-filter42.cpp ../../source/ac-filter43.cpp ../../source/ac-filter44.cpp ../../source/ac-filter45.cpp ../../source/ac-filter46.cpp ../../source/ac-filter47.cpp ../../source/ac-filter48.cpp ../../source/ac-filter49.cpp ../../source/ac-filtercat.cpp
LOCAL_LDLIBS +=  -llog -ldl

include $(BUILD_SHARED_LIBRARY)
