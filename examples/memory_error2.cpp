
#include"ac.h"

namespace ac {
    void TestFilterSubFilter(cv::Mat &frame);
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error requires image file path...\n";
        exit(EXIT_FAILURE);
    }
    ac::init();
    blend_image = cv::imread(argv[1]);
    if(blend_image.empty()) {
        std::cerr << "Requires one path of valid image file...\n";
        exit(EXIT_FAILURE);
    }
    blend_set = true;
    cv::VideoCapture cap(0);
    if(!cap.isOpened()) {
        std::cerr << "Error could not open capture...\n";
        exit(EXIT_FAILURE);
    }
    cv::namedWindow("Test Window");
    while(1) {
        cv::Mat frame;
        cap >> frame;
        if(!frame.empty()) {
            ac::pushSubFilter(ac::getFilterByName("MedianBlend"));
            ac::TestFilterSubFilter(frame);
            ac::popSubFilter();
        }
        cv::imshow("Test Window", frame);
        
        int key = cv::waitKey(10);
        if(key == 'Q' || key == 'q' || key == 27)
            exit(EXIT_SUCCESS);
    }
    return EXIT_SUCCESS;
}

void ac::TestFilterSubFilter(cv::Mat &frame) {
    if(blend_set == false || subfilter == -1 || draw_strings[subfilter] == "ImageSquareShrinkSubFilter")
        return;
    static int frame_offset_z = 1, frame_offset_i = 1;
    static int dir = 1;
    static int speed = 32;
    static double alpha = 1.0;
    static int dir1 = 1;
    cv::Mat reimage;
    ac_resize(blend_image, reimage, cv::Size(frame_offset_i, frame_offset_z));
    CallFilter(subfilter, reimage);
    for(int z = (frame.rows-1)-frame_offset_z, off_y = 0; z >= frame_offset_z; --z, ++off_y) {
        for(int i = (frame.cols-1)-frame_offset_i, off_x = 0; i >= frame_offset_i; --i, ++off_x) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            // error memory
            cv::Vec3b pix = reimage.at<cv::Vec3b>(off_y, off_x);
            for(int j = 0; j < 3; ++j) {
                pixel[j] = static_cast<unsigned char>((pixel[j] * 0.5) + (pix[j] * 0.5));
            }
        }
    }
    if(dir == 1) {
        frame_offset_z += speed;
        frame_offset_i += speed;
        if(frame_offset_z > ((frame.rows/2)-1) || frame_offset_i > ((frame.cols/2)-1)) {
            dir = 0;
        }
    } else {
        frame_offset_z -= speed;
        frame_offset_i -= speed;
        if(frame_offset_z <= 1 || frame_offset_i <= 1) {
            dir = 1;
        }
    }
    AlphaMovementMaxMin(alpha, dir1, 0.01, 1.0, 0.3);
}

