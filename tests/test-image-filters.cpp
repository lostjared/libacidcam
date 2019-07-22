/* Test If Basic Filters are working. */

#include<iostream>
#include"ac.h"

void buildFilters(std::vector<std::string> &current) {
    for(int i = 0; i < ac::getFilterCount(); ++i) {
        std::string name = ac::draw_strings[i];
        if(name.find("Image") != std::string::npos && name.find("1080") == std::string::npos && name.find("720") == std::string::npos)
            current.push_back(name);
    }
}

int main(int argc, char **argv) {
    cv::Mat test_image;
    test_image.create(cv::Size(640, 480), CV_8UC3);
    for(int z = 0; z < test_image.rows; ++z) {
        for(int i = 0; i < test_image.cols; ++i) {
            cv::Vec3b &pixel = test_image.at<cv::Vec3b>(z, i);
            pixel = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        }
    }
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
    // setup variables
    ac::orig_frame = test_image_sized.clone();
    blend_image = test_image_sized.clone();
    blend_set = true;
    // create vector of filters
    std::vector<std::string> image_filters;
    // populate vector with image filters
    buildFilters(image_filters);
    for(unsigned int i = 0; i < image_filters.size(); ++i) {
        std::cout << "Testing Filter: " << image_filters[i] << "\n";
        for(int j = 0; j < 10; ++j) {
            cv::Mat test_image_copy = test_image_sized.clone();
            ac::CallFilter(image_filters[i], test_image_copy);
        }
        std::cout << "Passed Test...\n";
        ac::release_all_objects();
        std::cout << "Cleared Frames...\n";
    }
    std::cout << "Passed " << image_filters.size() << " Image Filter Tests...\n";
	return 0;
}
