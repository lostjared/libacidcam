
// add CXXFLAG  -I/usr/local/includ/acidcam

#include"ac.h"
#include<iostream>
#include<string>

int main(int argc, char **argv) {
    ac::init(); // init libacidcam
    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        std::cerr << "Error opening webcam...\n";
        exit(EXIT_FAILURE);
    }
    cv::namedWindow("Example1");
    // program loop
    while(1){
        cv::Mat frame;
        if(cap.read(frame)) {
            ac::MedianBlendMultiThread(frame);
            cv::imshow("Example1", frame);
        }
        int key;
        key = cv::waitKey(50);
        if(key == 27) {
            exit(EXIT_SUCCESS);
        }
    }
    return 0;
}
