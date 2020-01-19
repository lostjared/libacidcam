
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include"com_lostsidedead_acidcam_AcidCam_Filter.h"
#include<vector>
#include "ac.h"
using namespace cv;


JNIEXPORT void JNICALL Java_com_lostsidedead_acidcam_AcidCam_1Filter_Filter
(JNIEnv *env, jobject pObject, jint filter, jlong frame) {
    Mat& mRgb = *(Mat*)frame;
    static int init = 0;
    if(init == 0) {
        ac::init();
        init = 1;
        ac::setMaxAllocated(200);
    }
    cv::Mat out;
    cv::cvtColor(mRgb,out,COLOR_RGBA2BGR);
    ac::CallFilter(filter,out);
    cv::cvtColor(out,mRgb,COLOR_BGR2RGBA);
}

JNIEXPORT void JNICALL Java_com_lostsidedead_acidcam_AcidCam_1Filter_clear_1frames
(JNIEnv *, jobject) {
    ac::release_frames = true;
}

void custom_filter(cv::Mat &frame) {

}
