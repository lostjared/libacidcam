# libacidcam

To watch all the creations I have created with this project checkout my YouTube playlist: https://www.youtube.com/playlist?list=PLUgo--lX2kmr6ikfz0hPlez1-jbGAYuTZ

This version shares some code with Acid Cam v2 OSX, so sometimes when I update the parts that are shared show up in both projects. libacidcam uses C++/OpenCV and Autotools, and this macOS program uses Objective-C++/Cocoa/OpenCV and Xcode

When upgrading to new versions of Acid Cam Qt, acidcam-cli or any other project that uses libacidcam:

Please be sure to recompile, install and relink any applications.

Shared library with filters from Acid Cam

With this library you can use the same filters in your own OpenCV applications.

This library uses pkg-config and OpenCV. First install/compile OpenCV and pkg-config. You will also need Autoconf,Automake,Libtool.
	
	$ ./autogen.sh && ./configure && make && sudo make install

If you are running on Linux you will need to use this command so it can find the library

	$ sudo ldconfig

Then you should be able to use pkg-config in your project and include ac.h

if you are using autotools you can use this macro in your configure.ac

be sure to recompile this library and relink programs current version is 0:0:0

PKG_CHECK_MODULES(ACIDCAM, acidcam, found=1, found=0)

AC_INCLUDES=$ACIDCAM_CFLAGS

AC_LIBS=$ACIDCAM_LIBS

AC_SUBST(AC_INCLUDES)

AC_SUBST(AC_LIBS)


