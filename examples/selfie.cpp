#include"ac.h"
#include<cstdlib>
#include<string>
#include<sstream>

int main(int argc, char **argv) {
    ac::init();
    if(argc != 3) {
        std::cerr << "Error invalid arguments...\n";
        exit(EXIT_FAILURE);
    }
    
    int dev = atoi(argv[1]);
    std::string prefix = argv[2];
    
    cv::VideoCapture capture(dev);
    if(!capture.isOpened()) {
        std::cerr << "Exit.. no opened..\n";
        exit(EXIT_FAILURE);
    }
    
    cv::namedWindow("Selfie");
    
    bool active = true;
    
    int filter_index = 0;
    bool snapshot = false;
    
    while(active) {
        cv::Mat frame;
        if(capture.read(frame)) {
            ac::CallFilter(filter_index, frame);
            if(snapshot == true) {
                static int count = 0;
                ++count;
                std::ostringstream stream;
                stream << prefix << "." << filter_index<< "."<<count << ".png";
                snapshot = false;
                cv::imwrite(stream.str(), frame);
            }
            cv::imshow("Selfie", frame);
            
        } else
            break;
        
        int key = cv::waitKey(15);
        switch(key) {
            case 'q':
                active = false;
                break;
            case 'z':
                if(filter_index > 0)
                    --filter_index;
                break;
            case 'x':
                if(filter_index < ac::getFilterCount())
                ++filter_index;
                break;
            case 's':
                snapshot = true;
                break;
        }
        
    }
    return 0;
}
