#include<iostream>
#include"ac.h"


int main(int argc, char **argv) {

	ac::init();

	if(argc != 2) {
		std::cerr << "Error requires file argument..\n";
		exit(EXIT_FAILURE);
	}
	cv::VideoCapture cap(argv[1]);
	if(!cap.isOpened()) {
		std::cerr << "Error capture device not opened..\n";
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < ac::getFilterCount(); ++i) {

		if(ac::draw_strings[i].find("Shuffle") != std::string::npos || ac::draw_strings[i].find("Rand") != std::string::npos || ac::draw_strings[i].find("Frame") != std::string::npos)
			continue;

		cv::Mat frame;
		if(cap.read(frame)) {
			std::cout << "calling.. " << ac::draw_strings[i] << "\n";
			ac::CallFilter(i, frame);
			std::cout << "call complete [" << ac::draw_strings[i] << "]\n";
		} else { 
			std::cout << "end of file..\n";
			exit(EXIT_SUCCESS);
		}
	}
	return 0;
}
