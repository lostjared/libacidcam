// How to use Blend with Source by Seting a source frame
// add CXXFLAG  -I/usr/local/include/acidcam

#include "ac.h"


int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error erequires one argument, the index of capture device.\n";
        exit(EXIT_FAILURE);
    }
    cv::VideoCapture cap(atoi(argv[1]));
    if(!cap.isOpened()) {
        std::cerr << "Error could not open capture device!\n";
        exit(EXIT_FAILURE);
    }
    
    cv::namedWindow("Example4");
    
    while(1) {
        cv::Mat frame;
        if(cap.read(frame)) {
            ac::setSourceFrame(frame);
            ac::ColorCollection(frame);
            ac::MedianBlendMultiThread(frame);
            ac::BlendWithSource75(frame);
            cv::imshow("Example4", frame);
        } else
            break;
        int key = cv::waitKey(50);
        if(key == 27 || key == 'q')
              break;
    }
    
    return 0;
}
