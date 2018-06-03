AM_CPPFLAGS= $(all_includes)
lib_LTLIBRARIES=libacidcam.la
libacidcam_includedir= $(includedir)/acidcam
libacidcam_include_HEADERS=ac.h fractal.h
libacidcam_la_SOURCES=ac.cpp fractal.cpp ac-func.cpp ac-alpha.cpp ac-obj.cpp ac-util.cpp ac-square.cpp ac-particle.cpp ac-grid.cpp
libacidcam_la_CXXFLAGS=-std=c++11 -O2 $(CV_INCLUDES)
libacidcam_la_LDFLAGS= -version-info 0:0:0
pkgconfigdir=$(libdir)/pkgconfig
pkgconfig_DATA= ../acidcam.pc
