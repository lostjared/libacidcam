// example use 'a' and 's' key to move up and down between filters
// for include path
// pkg-config acidcam --cflags
#include"ac.h"

int main(int argc, char **argv) {
    int dev_index = 0;
   
    if(argc >= 2)
        dev_index = atoi(argv[1]);

    ac::init();
    
    int filter_index = 0;
    
    if(dev_index < 0) {
        std::cerr << "Camera Index has to be greater than or equal to 0\n";
        exit(EXIT_FAILURE);
    }

    cv::VideoCapture cap(dev_index);
    if(!cap.isOpened()) {
        std::cerr << "Error could not open device...\n";
        exit(EXIT_FAILURE);
    }
    cv::Mat frame;
    cv::namedWindow("Example5");
    while(1) {
        if(cap.read(frame)) {
            ac::CallFilter(filter_index, frame);
            cv::imshow("Example5", frame);
        } else
            break;
        int key = cv::waitKey(50);
        switch(key) {
            case 27:
                exit(EXIT_SUCCESS);
                break;
            case 'a':
                if(filter_index < ac::getFilterCount())
                    ++filter_index;
                break;
            case 's':
                if(filter_index > 0)
                    --filter_index;
                break;
        }
    }
    return 0;
}
