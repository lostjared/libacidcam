
#include "ac.h"

void ac::FrameSep(cv::Mat &frame) {
    static constexpr int MAX = 16;
    static ac::MatrixCollection<MAX> collection;
    collection.shiftFrames(frame);
    static int off = 0;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            cv::Mat &f = collection.frames[off];
            cv::Vec3b pix = f.at<cv::Vec3b>(z, i);
            pixel = pix;
        }
        if(((z%240)==0) && ++off > MAX-1)
            off = 0;
    }
}

void ac::FrameSep2(cv::Mat &frame) {
    static constexpr int MAX = 16;
    static ac::MatrixCollection<MAX> collection;
    
    if(collection.empty()) {
        collection.shiftFrames(frame);
        srand(static_cast<unsigned int>(time(0)));
    } else if(rand()%5==0)
        collection.shiftFrames(frame);
    static bool on = false;
    static int off = 0;
    for(int z = 0; z < frame.rows; ++z) {
        for(int i = 0; i < frame.cols; ++i) {
            if(on == false) break;
            cv::Vec3b &pixel = frame.at<cv::Vec3b>(z, i);
            cv::Mat &f = collection.frames[off];
            cv::Vec3b pix = f.at<cv::Vec3b>(z, i);
            pixel = pix;
        }
        if(((z%240)==0) && ++off > MAX-1) {
            off = 0;
            static int cnt = 0;
            static int wait = rand()%10;
            ++cnt;
            if(cnt > wait) {
                on = !on;
                cnt = 0;
                wait = rand()%10;
            }
        }
    }
}

void ac::StutterFilter(cv::Mat  &frame) {
    static cv::Mat stored;
    static cv::Size stored_size;
    
    if(stored_size != frame.size()) {
        srand(static_cast<int>(time(0)));
        stored = frame.clone();
        stored_size = frame.size();
    } else {
        if(stored.empty())
            stored = frame.clone();

        static bool on = true;
        if(on == true) {
            if((rand()%15)==0) {
                stored = frame.clone();
                on = !on;
            }
            frame = stored.clone();
        } else {
            if((rand()%10) == 0)
                on = !on;
        }
    }
}




void ac::DefStutter(cv::Mat  &frame) {
    static ac::MatrixCollection<8> collection;
    if(collection.empty())
        srand(static_cast<unsigned int>(time(0)));
    collection.shiftFrames(frame);
    cv::Mat frame_copy = frame.clone();
    StutterFilter(frame_copy);
    int num_pixels = rand()%((frame.rows * frame.cols)/320);
    for(int q = 0; q < num_pixels; ++q) {
       int pixel_size = 16+(rand()%64);
       
       int off_x = rand()%(frame.cols-pixel_size-1);
       int off_y = rand()%(frame.rows-pixel_size-1);
       int offset = rand()%(collection.size()-1);
       
       for(int y = off_y; y < off_y + pixel_size; ++y) {
           for(int x = off_x; x < off_x + pixel_size; ++x) {
               cv::Mat &m = collection.frames[offset];
               cv::Vec3b &pix = m.at<cv::Vec3b>(y, x);
               cv::Vec3b &pix_copy = frame_copy.at<cv::Vec3b>(y, x);
               cv::Vec3b &pixel = frame.at<cv::Vec3b>(y, x);
               for(int j = 0; j < 3; ++j) {
                   if(pixel[j] != pix[j]) {
                        pixel[j] = static_cast<unsigned char>((0.5 * pixel[j]) + (0.5 * pix_copy[j]));
                    }
               }
           }
       }
   }
}
