/* Test If Basic Filters are working. */

#include<iostream>
#include"ac.h"

int main(int argc, char **argv) {
    cv::Mat test_image;
    
    test_image.create(cv::Size(1280, 720), CV_8UC3);
    for(int z = 0; z < test_image.rows; ++z) {
        for(int i = 0; i < test_image.cols; ++i) {
            cv::Vec3b &pixel = test_image.at<cv::Vec3b>(z, i);
            pixel = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        }
    }
    
    if(argc == 2)
        test_image = cv::imread(argv[1]);
    
    if(test_image.empty()) {
        std::cerr << "Error image could not be loaded.\n";
        exit(EXIT_FAILURE);
    }
    // setup test image
    cv::Mat test_image_sized;
    cv::resize(test_image, test_image_sized, cv::Size(640, 480));
    // initialize libacidcam
    ac::fill_filter_map();
    ac::setMaxAllocated(1500);
    // print out library version
    std::cout << "Library Version: " << ac::getVersion() << "\n";
    for(unsigned int i = 0; i < ac::solo_filter.size()-2; ++i) {
        std::cout << "[" << i << "/" << ac::solo_filter.size() << "] - Testing Filter: " << ac::solo_filter[i] << "\n";
        for(int j = 0; j < 30; ++j) {
            cv::Mat test_image_copy = test_image_sized.clone();
            ac::CallFilter(ac::solo_filter[i], test_image_copy);
            if(j == 29) {
                //std::ostringstream stream;
                //stream << "./images/" << ac::solo_filter[i] << ".png";
                //cv::imwrite(stream.str(), test_image_copy);
            }
        }
        std::cout << "Passed...\n";
        ac::release_all_objects();
        std::cout << "Cleared Frames...\n";
    }
    std::cout << "Passed " << ac::solo_filter.size() << " Basic Filter Tests...\n";
    return 0;
}
