#include<iostream>
#include"ac.h"

int main(int argc, char **argv) {
	if(argc != 2) {
		std::cout << "Error requires one argumnet of video file.\n";
		exit(EXIT_FAILURE);
	}
	cv::VideoWriter writer;
    writer.open(argv[1], cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 30, cv::Size(320, 240), true);
    if(writer.isOpened()) {
        std::cout << "Opened file...\n";
    }
    
    
    
    
	return 0;
}
