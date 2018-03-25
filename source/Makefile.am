AM_CPPFLAGS= $(all_includes)
lib_LTLIBRARIES=libacidcam.la
libacidcam_includedir= $(includedir)/acidcam
libacidcam_include_HEADERS=ac.h fractal.h
libacidcam_la_SOURCES=ac.cpp fractal.cpp
libacidcam_la_CXXFLAGS=-std=c++11 -O2 $(CV_INCLUDES)
libacidcam_la_LDFLAGS=
pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA= ../acidcam.pc
