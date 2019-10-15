#!/bin/bash

git clone https://github.com/lostjared/libacidcam.git
cd libacidcam
mkdir -p build
cd build
cmake .. -DENABLE_EXAMPLES=OFF
make -j4 
sudo make install
cd ../..
git clone https://github.com/lostjared/acidcam-cli.git
cd acidcam-cli
mkdir -p build
cd build
cmake ..
make -j4
sudo make install
cd ../..


