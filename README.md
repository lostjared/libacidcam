# libacidcam

Shared library with filters from Acid Cam v2.3.5

This library uses pkg-config and OpenCV. First install/compile OpenCV and pkg-config then

	$ ./autogen.sh && ./configure && make && make install

Then you should be able to use pkg-config in your project and include ac.h

	$ pkg-config acidcam --cflags --libs

Something like this in your Makefile

CXXFLAGS= `pkg-config acidcam --cfalgs`

LDADD= `pkg-config acidcam --libs`

all:

	$(CXX) $(CXXFLAGS) program.cpp -o test.program $(LDADD)

