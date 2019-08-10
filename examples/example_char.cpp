#include "ac.h"
#include<sstream>
#include<string>
#include<cstdlib>

void charFrame(int &index, std::string &text, cv::Mat &frame);

int main(int argc, char **argv) {
    if(argc != 4) {
        std::cerr << "Error invalid arguments, should be\nexample_char video_in.mov video_out.mov text.txt\n";
    }
    std::fstream file;
    file.open(argv[3], std::ios::in);
    if(!file.is_open()) {
        std::cerr << "Error could not open file: " << argv[3] << "\n";
        exit(EXIT_FAILURE);
    }
    std::stringstream stream;
    stream << file.rdbuf();
    std::string value = stream.str();
    cv::VideoCapture cap(argv[1]);
    if(!cap.isOpened()) {
        std::cerr << "Error could not open file: " << argv[1] << "\n";
        exit(EXIT_FAILURE);
    }
    ac::fps = cap.get(cv::CAP_PROP_FPS);
    int aw = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int ah = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cv::VideoWriter writer;
    bool opened = writer.open(argv[2],cv::VideoWriter::fourcc('m','p','4','v'),ac::fps, cv::Size(aw, ah), true);
    if(opened == false) {
        std::cerr << "Could not open output file...\n";
    }
    std::cout << "Press Q to quit program\n";
    cv::namedWindow("CharExample");
    int index = 0;
    while(1) {
        cv::Mat frame;
        if(cap.read(frame)) {
            charFrame(index, value, frame);
            writer.write(frame);
            if(!frame.empty())
                cv::imshow("CharExample", frame);
            int key = cv::waitKey(25);
            if(key == 28 || key == 'q' || key == 'Q')
                break;
        }
        else
            break;
    }
    return 0;
}

void charFrame(int &index, std::string &text, cv::Mat &frame) {
    if(text.length() == 0 || text.length() <= 2) {
        std::cerr << "Text string is empty.\n";
        exit(EXIT_FAILURE);
        return;
    }
    if(index+2 >= text.length()-1) {
        index = 0;
    }
    char array[3];
    array[0] = text[index];
    array[1] = text[index+1];
    array[2] = text[index+2];
    index += 3;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            for(int j = 0; j < 3; ++j) {
                pixel[j] = static_cast<unsigned char>(0.25 * (pixel[j]^array[j]) + (0.25 * array[j]) + (pixel[j] * 0.5));
            }
        }
    }
    ac::MedianBlendMultiThread(frame);
}
