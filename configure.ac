
AC_PREREQ([2.69])
AC_INIT(libacidcam, 1.0.1, lostjared@lostsidedead.com)
AC_CONFIG_HEADERS(config.h)
AC_CANONICAL_SYSTEM
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_INIT_AUTOMAKE
AC_PROG_LIBTOOL

PKG_CHECK_MODULES(OPENCV, opencv4, found=1, found=0)

if test $found = 0; then
PKG_CHECK_MODULES(OPENCV, opencv, found=1, found=0)
fi

if test $found = 0; then
AC_MSG_ERROR(Error could not find OpenCV pkg-config file is it installed?)
else
echo "OpenCV Found!"
fi


CV_INCLUDES=$OPENCV_CFLAGS
CV_LIBS=$OPENCV_LIBS

AC_SUBST(CV_INCLUDES)
AC_SUBST(CV_LIBS)


AC_OUTPUT(Makefile acidcam.pc source/Makefile)
