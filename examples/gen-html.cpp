
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"ac.h"

void procList(std::string file, int start, std::vector<std::string> &names);
void genIndex(int start);

int main(int argc, char **argv) {
    ac::init();
    ac::setMaxAllocated(3000);
    
    if(argc == 1)
        genIndex(0);
    
    if(argc == 3)
        procList(argv[1], atoi(argv[2]), ac::draw_strings);
    
    return 0;
}

void procFilter(cv::VideoCapture &cap, std::string file, std::string fname) {
    cap.set(cv::CAP_PROP_POS_FRAMES, 0);
    
    std::fstream file_stream;
    std::string file_name, gfx_name;
    file_name = fname+".html";
    gfx_name = std::string("screens/") + fname+".jpg";
    file_stream.open(file_name, std::ios::out);
    if(!file_stream.is_open()) {
        std::cerr << "Error could not open file: " << file_name << "\n";
    }
    file_stream << "<!DOCTYPE html><head><title> Acid Cam Filter - " << fname << "</title></head>";
    file_stream << "<body><h1>" << fname << "</h1><br>Description: <br><br><a href=\"" << gfx_name << "\"><img src=\"" << gfx_name << "\"></a><br><br>";
    file_stream << "</body></html>";
    for(int i = 0; i < 160; ++i) {
        cv::Mat frame;
        cap >> frame;
        ac::CallFilter(fname, frame);
        if(i == 158) {
            cv::imwrite(gfx_name, frame);
            ac::release_all_objects();
            return;
        }
    }
}

void genIndex(int start) {
    std::fstream file;
    file.open("index.html", std::ios::out);
    if(!file.is_open()) {
        std::cerr << "Error could not open file.\n";
        exit(EXIT_FAILURE);
    }
    file << "<!DOCTYPE html><head><title>Acid Cam Index</title></head><body><h1>Index</h1><br><br>";

    std::vector<std::string> &names = ac::draw_strings;
    
    for(int i = 0; i < ac::draw_strings.size(); ++i) {
        if(names[i].find("Image") == std::string::npos && names[i].find("SubFilter") == std::string::npos && names[i].find("Video") == std::string::npos && names[i].find("Intertwine") == std::string::npos && names[i].find("Random") == std::string::npos && names[i].find("Buffer") == std::string::npos) {
            file << "<a href=\"" << ac::draw_strings[i] << ".html" << "\">" << ac::draw_strings[i] <<  "</a><br>\n";
        }
    }
    file << "</body><html>";
    std::cout << "generated index..\n";
    return;
}

void procList(std::string file, int start, std::vector<std::string> &names) {
    
    cv::VideoCapture cap(file);
    if(!cap.isOpened()) {
        std::cerr << "Error opening file: " << file << "\n";
    }
    
    for(int i = start; i < names.size(); ++i) {
        if(names[i].find("Image") == std::string::npos && names[i].find("SubFilter") == std::string::npos && names[i].find("Video") == std::string::npos && names[i].find("Intertwine") == std::string::npos && names[i].find("Rand") == std::string::npos && names[i].find("Buffer") == std::string::npos) {
            procFilter(cap, file, names[i]);
            std::cout << "[" << i << "/" << names.size() << "] - wrote: " << names[i] << "\n";
        }
    }
}
