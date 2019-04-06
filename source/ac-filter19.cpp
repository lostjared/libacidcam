/*
 * Software written by Jared Bruni https://github.com/lostjared
 
 This software is dedicated to all the people that experience mental illness.
 
 Website: http://lostsidedead.com
 YouTube: http://youtube.com/LostSideDead
 Instagram: http://instagram.com/lostsidedead
 Twitter: http://twitter.com/jaredbruni
 Facebook: http://facebook.com/LostSideDead0x
 
 You can use this program free of charge and redistrubute it online as long
 as you do not charge anything for this program. This program is meant to be
 100% free.
 
 BSD 2-Clause License
 
 Copyright (c) 2019, Jared Bruni
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 */

#include "ac.h"

// Use as a subfilter for Smooth
void ac::ImageRandomValues(cv::Mat &frame) {
    if(blend_set == false)
        return;
    cv::Mat reimage;
    int r_x = rand()%(frame.cols-1);
    int r_y = rand()%(frame.rows-1);
    if(r_x < 10)
        r_x = 10;
    if(r_y < 10)
        r_y = 10;
    cv::Size size_val(r_x, r_y);
    cv::resize(blend_image, reimage, size_val);
    copyMat(frame, reimage);
}

void ac::AlphaBlendTrails(cv::Mat &frame) {
    static MatrixCollection<32> collection;
    collection.shiftFrames(frame);
    cv::Mat copy1 = frame.clone(), copy2 = frame.clone();
    for(int i = 0; i < 16;  ++i += 2) {
        cv::Mat &cp = collection.frames[i];
        AlphaBlendDouble(copy1, cp, copy2, 0.6, 0.4);
        copy1 = copy2.clone();
    }
    AlphaBlend(frame, copy1, copy2,0.5);
    frame = copy2.clone();
}

void ac::VideoStretchHorizontal(cv::Mat &frame) {
    static int x = 0, dir = 2;
    static const int speed = 20;
    if(x < frame.cols-1)
        x = frame.cols;
    if(dir == 1) {
        x += speed;
        if(x > (frame.cols*3))
            dir = 0;
    } else if(dir == 0) {
        x -= speed;
        if(x < frame.cols-1)
            dir = 1;
    } else if(dir == 2) {
        x = frame.cols;
        dir = 1;
    }
    cv::Mat copy1;
    cv::resize(frame, copy1, cv::Size(x, frame.rows));
    copyMatSize(frame, copy1, 0, 0);
}

void ac::VideoStretchVertical(cv::Mat &frame) {
    static int y = 0, dir = 2;
    static const int speed = 20;
    if(y < frame.rows-1)
        y = frame.rows;
    if(dir == 1) {
        y += speed;
        if(y > (frame.rows*3))
            dir = 0;
    } else if(dir == 0) {
        y -= speed;
        if(y < frame.rows-1)
            dir = 1;
    } else if(dir == 2) {
        y = frame.rows;
        dir = 1;
    }
    cv::Mat copy1;
    cv::resize(frame, copy1, cv::Size(frame.cols, y));
    copyMatSize(frame, copy1, 0, 0);
}
