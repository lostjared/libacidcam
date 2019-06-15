/* Test If Basic Filters are working. */

#include<iostream>
#include"ac.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Requires testing Image to be passed as argument.\n";
        exit(EXIT_FAILURE);
    }
    cv::Mat test_image = cv::imread(argv[1]);
    if(test_image.empty()) {
        std::cerr << "Error image could not be loaded.\n";
        exit(EXIT_FAILURE);
    }
    // setup test image
    cv::Mat test_image_sized;
    cv::resize(test_image, test_image_sized, cv::Size(640, 480));
    // initialize libacidcam
    ac::fill_filter_map();
    // print out library version
    std::cout << "Library Version: " << ac::getVersion() << "\n";
    for(unsigned int i = 0; i < ac::solo_filter.size(); ++i) {
        std::cout << "Testing Filter: " << ac::solo_filter[i] << "\n";
        for(int j = 0; j < 10; ++j) {
            cv::Mat test_image_copy = test_image_sized.clone();
            ac::CallFilter(ac::solo_filter[i], test_image_copy);
        }
        std::cout << "Passed...\n";
    }
    std::cout << "Passed " << ac::solo_filter.size() << " Basic Filter Tests...\n";
	return 0;
}
