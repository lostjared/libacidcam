AC_PREREQ([2.69])
AC_INIT(libacidcam, 2.3.5, lostjared@lostsidedead.com)
AC_CANONICAL_SYSTEM
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_INIT_AUTOMAKE
AC_PROG_LIBTOOL

PKG_CHECK_MODULES(OPENCV, opencv, found=1, found=0)


CV_INCLUDES=$OPENCV_CFLAGS
CV_LIBS=$OPENCV_LIBS



AC_SUBST(CV_INCLUDES)
AC_SUBST(CV_LIBS)


AC_OUTPUT(Makefile acidcam.pc source/Makefile)
