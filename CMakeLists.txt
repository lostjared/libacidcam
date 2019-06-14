
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(libacidcam LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build configuration is: ${CMAKE_BUILD_TYPE}")
message(STATUS "is the C++ compiler loaded? ${CMAKE_CXX_COMPILER_LOADED}")

if(CMAKE_CXX_COMPILER_LOADED)
	message(STATUS "The C++ Compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
	message(STATUS "The C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQURIED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
list(APPEND COMPILER_FLAGS "-Wall" "-pedantic" "-ansi" "-Ofast")
else()
message(STATUS "Debug Mode")
list(APPEND COMPILER_FLAGS "-Wall" "-pedantic" "-ansi")
endif()

list(APPEND source_files 
${CMAKE_SOURCE_DIR}/source/ac-alpha.cpp
${CMAKE_SOURCE_DIR}/source/ac-basic.cpp
${CMAKE_SOURCE_DIR}/source/ac-box.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter1.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter10.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter11.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter12.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter13.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter14.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter15.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter16.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter17.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter18.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter19.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter2.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter20.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter21.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter22.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter23.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter3.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter4.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter5.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter6.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter7.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter8.cpp
${CMAKE_SOURCE_DIR}/source/ac-filter9.cpp
${CMAKE_SOURCE_DIR}/source/ac-filtercat.cpp
${CMAKE_SOURCE_DIR}/source/ac-filtercat.h
${CMAKE_SOURCE_DIR}/source/ac-grid.cpp
${CMAKE_SOURCE_DIR}/source/ac-image.cpp
${CMAKE_SOURCE_DIR}/source/ac-obj.cpp
${CMAKE_SOURCE_DIR}/source/ac-particle.cpp
${CMAKE_SOURCE_DIR}/source/ac-square.cpp
${CMAKE_SOURCE_DIR}/source/ac-util.cpp
${CMAKE_SOURCE_DIR}/source/ac.h
${CMAKE_SOURCE_DIR}/source/fractal.cpp
${CMAKE_SOURCE_DIR}/source/fractal.h
)

list(APPEND install_headers ${CMAKE_SOURCE_DIR}/source/ac.h ${CMAKE_SOURCE_DIR}/source/fractal.h)
find_package(OpenCV REQUIRED)
include_directories({CMAKE_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})
add_library(acidcam ${source_files})
target_link_libraries(acidcam ${OpenCV_LIBS})
install(TARGETS acidcam  DESTINATION lib)
install(FILES ${install_headers} DESTINATION include/acidcam)
