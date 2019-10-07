// print out supported codec

#include<iostream>
#include"ac.h"

int main(int argc, char **argv) {
	cv::VideoWriter writer;
    writer.open("test.mp4",-1,30,cv::Size(320, 240), true);
    if(writer.isOpened()) {
        std::cout << "Opened file...\n";
    }
	return 0;
}
