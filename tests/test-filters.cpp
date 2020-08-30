/* Test If Basic Filters are working. */

#include<iostream>
#include<fstream>
#include"ac.h"
#include<chrono>

int main(int argc, char **argv) {
    cv::Mat test_image;
    
    test_image.create(cv::Size(1280, 720), CV_8UC3);
    for(int z = 0; z < test_image.rows; ++z) {
        for(int i = 0; i < test_image.cols; ++i) {
            cv::Vec3b &pixel = test_image.at<cv::Vec3b>(z, i);
            pixel = cv::Vec3b(rand()%255, rand()%255, rand()%255);
        }
    }
    
    int wait_val = 0;
    
    if(argc >= 2)
        test_image = cv::imread(argv[1]);
    if(argc >= 3)
        wait_val = atoi(argv[2]);
    
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
    std::fstream file;
    file.open("output.txt", std::ios::out);
    if(!file.is_open()) {
        std::cerr << "Error couldn't open file\n";
        exit(0);
    }
    // print out library version
    std::cout << "Library Version: " << ac::getVersion() << "\n";
    for(unsigned int i = 0; i < ac::solo_filter.size()-2; ++i) {
        std::cout << "[" << i << "/" << ac::solo_filter.size() << "] - Testing Filter: " << ac::solo_filter[i] << "\n";
        bool add = true;
        
        for(int j = 0; j < 30; ++j) {
            cv::Mat test_image_copy = test_image_sized.clone();
            std::chrono::time_point<std::chrono::system_clock> now =
            std::chrono::system_clock::now();
            ac::CallFilter(ac::solo_filter[i], test_image_copy);
            if(j == 29) {
                //std::ostringstream stream;
                //stream << "./images/" << ac::solo_filter[i] << ".png";
                //cv::imwrite(stream.str(), test_image_copy);
            }
            
            std::chrono::time_point<std::chrono::system_clock> nowx =
            std::chrono::system_clock::now();
            auto m = std::chrono::duration_cast<std::chrono::milliseconds>(nowx-now).count();
            if(wait_val == 0 || m < wait_val) {
                add = true;
            }
            else {
                add = false;
                std::cout << "to slow..\n";
                break;
            }
        }
        
        std::cout << "Passed...\n";
        if(add == true) {
            std::cout << "This one is Fast enough\n";
            file << ac::solo_filter[i] << "\n";
        } else {
            std::cout << "This one is not fast enough\n";
        }
        ac::release_all_objects();
        std::cout << "Cleared Frames...\n";
    }
    std::cout << "Passed " << ac::solo_filter.size() << " Basic Filter Tests...\n";
    return 0;
}
