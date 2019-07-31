#include<iostream>
#include<string>
#include"ac.h"

namespace ac {
    void XorZeroImage(cv::Mat &frame, cv::Mat &blend_image) {
        static MatrixCollection<8> collection;
        collection.shiftFrames(frame);
        cv::Mat reimage;
        ac_resize(blend_image,reimage, frame.size());
        auto callback = [&](cv::Mat *frame, int offset, int cols, int size) {
            for(int z = offset; z <  offset+size; ++z) {
                for(int i = 0; i < cols; ++i) {
                    cv::Vec3b &pixel = frame->at<cv::Vec3b>(z, i);
                    cv::Vec3b pix = collection.frames[7].at<cv::Vec3b>(i,z);
                    cv::Vec3b color = reimage.at<cv::Vec3b>(i,z);
                    for(int j = 0; j < 3; ++j) {
                        pixel[j] = pixel[j]^pix[j];
                        if(pixel[j] == 0)
                            pixel[j] = color[j];
                    }
                }
            }
        };
        UseMultipleThreads(frame, getThreadCount(), callback);
        AddInvert(frame);
    }
}

int main(int argc, char **argv) {
    if(argc != 4) {
        std::cerr << "Error: requires 3 arguments...\n" << argv[0] << " inputfile imagefile outputfile\n";
        exit(EXIT_FAILURE);
    }
    cv::Mat reimage = cv::imread(argv[2]);
    if(reimage.empty()) {
        std::cerr << "Error could not re image file...\n";
        exit(EXIT_FAILURE);
    }
    cv::VideoCapture cap(argv[1]);
    if(!cap.isOpened()) {
        std::cerr << "Error could not open file: " << argv[1] << "\n";
    }
    ac::fps = cap.get(cv::CAP_PROP_FPS);
    int aw = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int ah = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cv::VideoWriter writer;
    bool opened = writer.open(argv[3],cv::VideoWriter::fourcc('m','p','4','v'),ac::fps, cv::Size(aw, ah), true);
    if(opened == false) {
        std::cerr << "Could not open output file...\n";
    }
    std::cout << "Press Q to quit program\n";
    cv::namedWindow("Test");
    while(1) {
        cv::Mat frame;
        cap >> frame;
        ac::XorZeroImage(frame, reimage);
        writer.write(frame);
        cv::imshow("Test", frame);
        int key = cv::waitKey(25);
        if(key == 28 || key == 'q' || key == 'Q')
            break;
    }
    return 0;
}
