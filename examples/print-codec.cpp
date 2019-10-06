#include<iostream>
#include"ac.h"

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout << "Error requires one argumnet of video file.\n";
		exit(EXIT_FAILURE);
	}
	cv::VideoWriter writer;
    writer.open(argv[1],cv::VideoWriter::fourcc('h', 'e', 'v', '1') , 30, cv::Size(320, 240), true);
    if(writer.isOpened()) {
        std::cout << "Opened file...\n";
    }
    cv::Mat mat;
    mat = cv::imread("fred-cover.png");
    if(mat.empty()) {
        std::cerr << "Could not open file...\n";
        exit(EXIT_FAILURE);
    }
    cv::Mat out;
    cv::resize(mat, out, cv::Size(320, 240));
    for(int j = 0; j < 420; ++j)
        writer << out;
    
	return 0;
}
