# libacidcam

Shared library with filters from Acid Cam v2.3.5

This library uses pkg-config and OpenCV. First install/compile OpenCV and pkg-config then

	$ ./autogen.sh && ./configure && make && make install

Then you should be able to use pkg-config in your project and include ac.h

if you are using autotools you can use this macro in your configure.ac

PKG_CHECK_MODULES(ACIDCAM, acidcam, found=1, found=0)

CV_INCLUDES=$ACIDCAM_CFLAGS

CV_LIBS=$ACIDCAM_LIBS


