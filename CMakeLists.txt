cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(libacidcam 
    VERSION 2.0.0
    DESCRIPTION "Acid Cam Filters for OpenCV"
    LANGUAGES CXX
)

set(ACIDCAM_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set(ACIDCAM_MINOR_VERSION ${PROJECT_VERSION_MINOR})
set(ACIDCAM_VERSION ${PROJECT_VERSION})
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "=== libacidcam ${PROJECT_VERSION} Build Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(ACIDCAM_ENABLE_TESTS "Build test programs" ON)
option(ACIDCAM_ENABLE_EXAMPLES "Build examples" ON)
option(ACIDCAM_INSTALL "Generate install target" ON)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs highgui PATHS /usr/local NO_DEFAULT_PATH)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found. Please install OpenCV 3.0+ with development headers.")
endif()
if(OpenCV_VERSION VERSION_LESS "3.0.0")
    message(FATAL_ERROR "OpenCV version ${OpenCV_VERSION} found, but version 3.0.0 or higher is required.")
endif()

message(STATUS "Found OpenCV: ${OpenCV_VERSION}")
message(STATUS "  OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "  OpenCV libraries: ${OpenCV_LIBS}")

include(CheckIncludeFileCXX)
set(CMAKE_REQUIRED_INCLUDES ${OpenCV_INCLUDE_DIRS})
check_include_file_cxx("opencv2/opencv.hpp" HAVE_OPENCV_HPP)
check_include_file_cxx("opencv2/core.hpp" HAVE_OPENCV_CORE_HPP)
check_include_file_cxx("opencv2/imgproc.hpp" HAVE_OPENCV_IMGPROC_HPP)
check_include_file_cxx("opencv2/imgcodecs.hpp" HAVE_OPENCV_IMGCODECS_HPP)
check_include_file_cxx("opencv2/highgui.hpp" HAVE_OPENCV_HIGHGUI_HPP)
if(NOT HAVE_OPENCV_CORE_HPP)
    message(FATAL_ERROR "Required header opencv2/core.hpp not found. Install OpenCV development packages.")
endif()
if(NOT HAVE_OPENCV_IMGPROC_HPP)
    message(FATAL_ERROR "Required header opencv2/imgproc.hpp not found. Install OpenCV development packages.")
endif()
if(NOT HAVE_OPENCV_IMGCODECS_HPP)
    message(FATAL_ERROR "Required header opencv2/imgcodecs.hpp not found. Install OpenCV development packages.")
endif()
if(NOT HAVE_OPENCV_HIGHGUI_HPP)
    message(FATAL_ERROR "Required header opencv2/highgui.hpp not found. Install OpenCV development packages.")
endif()

message(STATUS "All required OpenCV headers found")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if(NOT Threads_FOUND)
    message(FATAL_ERROR "Threading library not found.")
endif()
message(STATUS "Found Threads: ${CMAKE_THREAD_LIBS_INIT}")

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    message(STATUS "Found PkgConfig: pkg-config file will be generated")
else()
    message(STATUS "PkgConfig not found: pkg-config file will not be generated")
endif()

include(CheckIncludeFileCXX)
check_include_file_cxx("iostream" HAVE_IOSTREAM)
check_include_file_cxx("fstream" HAVE_FSTREAM)
check_include_file_cxx("vector" HAVE_VECTOR)
check_include_file_cxx("string" HAVE_STRING)
check_include_file_cxx("algorithm" HAVE_ALGORITHM)
check_include_file_cxx("random" HAVE_RANDOM)
check_include_file_cxx("thread" HAVE_THREAD)
check_include_file_cxx("mutex" HAVE_MUTEX)

if(NOT HAVE_IOSTREAM OR NOT HAVE_FSTREAM OR NOT HAVE_VECTOR OR NOT HAVE_STRING)
    message(FATAL_ERROR "Required C++ standard library headers not found. Check your compiler installation.")
endif()
if(NOT HAVE_THREAD OR NOT HAVE_MUTEX)
    message(WARNING "C++11 threading headers not found. Some features may not work correctly.")
endif()

include(GNUInstallDirs)
set(include_dest "${CMAKE_INSTALL_INCLUDEDIR}/acidcam")
set(main_lib_dest "${CMAKE_INSTALL_LIBDIR}")
set(ACIDCAM_PRIVATE_COMPILE_OPTIONS "")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        list(APPEND ACIDCAM_PRIVATE_COMPILE_OPTIONS -O2 -DNO_SCREEN_GRAB -DDONT_TEST_BOUNDS)
    else()
        list(APPEND ACIDCAM_PRIVATE_COMPILE_OPTIONS -g -DNO_SCREEN_GRAB -Wall -Wextra)
    endif()
elseif(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        list(APPEND ACIDCAM_PRIVATE_COMPILE_OPTIONS /O2 /DNO_SCREEN_GRAB /DDONT_TEST_BOUNDS)
    else()
        list(APPEND ACIDCAM_PRIVATE_COMPILE_OPTIONS /Od /DNO_SCREEN_GRAB /W4)
    endif()
endif()

set(ACIDCAM_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/source/ac-alpha.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-basic.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-box.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter1.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter2.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter3.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter4.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter5.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter6.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter7.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter8.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter9.cpp
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
    ${CMAKE_SOURCE_DIR}/source/ac-filter20.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter21.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter22.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter23.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter24.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter25.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter26.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter27.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter28.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter29.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter30.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter31.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter32.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter33.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter34.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter35.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter36.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter37.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter38.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter39.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter40.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter41.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter42.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter43.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter44.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter45.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter46.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter47.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter48.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter49.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter50.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filter-new.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-filtercat.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-grid.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-image.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-obj.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-particle.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-square.cpp
    ${CMAKE_SOURCE_DIR}/source/ac-util.cpp
    ${CMAKE_SOURCE_DIR}/source/fractal.cpp
)

set(ACIDCAM_HEADER_FILES
    ${CMAKE_SOURCE_DIR}/source/ac.h
    ${CMAKE_SOURCE_DIR}/source/fractal.h
    ${CMAKE_SOURCE_DIR}/source/ac-filtercat.h
)

foreach(src_file ${ACIDCAM_SOURCE_FILES})
    if(NOT EXISTS "${src_file}")
        message(FATAL_ERROR "Source file not found: ${src_file}")
    endif()
endforeach()

foreach(hdr_file ${ACIDCAM_HEADER_FILES})
    if(NOT EXISTS "${hdr_file}")
        message(FATAL_ERROR "Header file not found: ${hdr_file}")
    endif()
endforeach()

message(STATUS "Found ${CMAKE_CXX_COMPILER_ID} source files and headers")

add_library(acidcam ${ACIDCAM_HEADER_FILES} ${ACIDCAM_SOURCE_FILES})
add_library(acidcam::acidcam ALIAS acidcam)

target_include_directories(acidcam
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${include_dest}>
    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(acidcam 
    PUBLIC 
        ${OpenCV_LIBS}
    PRIVATE 
        Threads::Threads
)

target_compile_options(acidcam PRIVATE ${ACIDCAM_PRIVATE_COMPILE_OPTIONS})

set_target_properties(acidcam PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME acidcam
    OUTPUT_NAME acidcam
)

if(PkgConfig_FOUND AND ACIDCAM_INSTALL)
    set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
    set(PRIVATE_LIBS "-lacidcam")
    configure_file(
        ${CMAKE_SOURCE_DIR}/acidcam.pc.in 
        ${CMAKE_CURRENT_BINARY_DIR}/acidcam.pc 
        @ONLY
    )
endif()

if(ACIDCAM_INSTALL)
    include(CMakePackageConfigHelpers)
    
    install(TARGETS acidcam
        EXPORT acidcamTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(FILES ${ACIDCAM_HEADER_FILES} DESTINATION "${include_dest}")
    
    if(PkgConfig_FOUND)
        install(FILES ${CMAKE_CURRENT_BINARY_DIR}/acidcam.pc 
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
        )
    endif()

    install(EXPORT acidcamTargets
        FILE acidcamTargets.cmake
        NAMESPACE acidcam::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/acidcam
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    configure_package_config_file(
        ${CMAKE_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/acidcam
        PATH_VARS include_dest main_lib_dest
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/acidcam
    )
endif()

if(ACIDCAM_ENABLE_TESTS)
    set(ACIDCAM_TEST_FILES
        ${CMAKE_SOURCE_DIR}/tests/test-filters.cpp
        ${CMAKE_SOURCE_DIR}/tests/test-image-filters.cpp
        ${CMAKE_SOURCE_DIR}/tests/test-subfilter.cpp
        ${CMAKE_SOURCE_DIR}/tests/test-filter-ex.cpp
    )
    
    set(TESTS_AVAILABLE TRUE)
    foreach(test_file ${ACIDCAM_TEST_FILES})
        if(NOT EXISTS "${test_file}")
            message(WARNING "Test file not found: ${test_file}")
            set(TESTS_AVAILABLE FALSE)
        endif()
    endforeach()
    
    if(TESTS_AVAILABLE)
        enable_testing()
        
        add_executable(test-filter1 ${CMAKE_SOURCE_DIR}/tests/test-filters.cpp)
        target_link_libraries(test-filter1 PRIVATE acidcam Threads::Threads)
        target_compile_options(test-filter1 PRIVATE ${ACIDCAM_PRIVATE_COMPILE_OPTIONS})
        add_test(NAME test-filters COMMAND $<TARGET_FILE:test-filter1>)
        
        add_executable(test-image ${CMAKE_SOURCE_DIR}/tests/test-image-filters.cpp)
        target_link_libraries(test-image PRIVATE acidcam Threads::Threads)
        target_compile_options(test-image PRIVATE ${ACIDCAM_PRIVATE_COMPILE_OPTIONS})
        add_test(NAME test-image-filters COMMAND $<TARGET_FILE:test-image>)
        
        add_executable(test-subfilter ${CMAKE_SOURCE_DIR}/tests/test-subfilter.cpp)
        target_link_libraries(test-subfilter PRIVATE acidcam Threads::Threads)
        target_compile_options(test-subfilter PRIVATE ${ACIDCAM_PRIVATE_COMPILE_OPTIONS})
        add_test(NAME test-subfilter COMMAND $<TARGET_FILE:test-subfilter>)
        
        add_executable(test-filter-ex ${CMAKE_SOURCE_DIR}/tests/test-filter-ex.cpp)
        target_link_libraries(test-filter-ex PRIVATE acidcam Threads::Threads)
        target_compile_options(test-filter-ex PRIVATE ${ACIDCAM_PRIVATE_COMPILE_OPTIONS})
        
        message(STATUS "Tests enabled")
    else()
        message(STATUS "Tests disabled: test source files not found")
    endif()
endif()

message(STATUS "")
message(STATUS "=== libacidcam Configuration Summary ===")
message(STATUS "Version:           ${PROJECT_VERSION}")
message(STATUS "Build type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "Shared libs:       ${BUILD_SHARED_LIBS}")
message(STATUS "Install prefix:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "OpenCV version:    ${OpenCV_VERSION}")
message(STATUS "Tests enabled:     ${ACIDCAM_ENABLE_TESTS}")
message(STATUS "Install enabled:   ${ACIDCAM_INSTALL}")
message(STATUS "")
