# libacidcam

Be sure to recompile, install and relink any applications that use this library.

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


