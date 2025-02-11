cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(libacidcam LANGUAGES CXX)
set(ACIDCAM_MAJOR_VERSION 2)
set(ACIDCAM_MINOR_VERSION 0)
set(ACIDCAM_VERSION ${ACIDCAM_MAJOR_VERSION}.${ACIDCAM_MINOR_VERSION})

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
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(include_dest "${CMAKE_INSTALL_PREFIX}/include/acidcam")
set(main_lib_dest "${CMAKE_INSTALL_PREFIX}/lib")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND COMPILER_FLAGS "-O2" "-DNO_SCREEN_GRAB" "-DDONT_TEST_BOUNDS")
else()
    message(STATUS "Debug Mode")
    list(APPEND COMPILER_FLAGS "-g" "-DNO_SCREEN_GRAB")
endif()

list(APPEND source_files 
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

list(APPEND header ${CMAKE_SOURCE_DIR}/source/ac.h ${CMAKE_SOURCE_DIR}/source/fractal.h ${CMAKE_SOURCE_DIR}/source/ac-filtercat.h)
find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

if(${OpenCV_VERSION} LESS 3.0)
    message(FATAL_ERROR "Requires OpenCV 3 or greater")
endif()

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build Shared Libraries")

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS})
add_library(acidcam ${header} ${source_files})
target_link_libraries(acidcam ${OpenCV_LIBS} Threads::Threads)
target_compile_options(acidcam PRIVATE ${COMPILER_FLAGS})

set(ENABLE_TESTS ON CACHE BOOL "Compile Testing Program")
set(ENABLE_EXAMPLES ON CACHE BOOL "Compile Examples")

set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")
set(PRIVATE_LIBS "-lacidcam")
configure_file(${CMAKE_SOURCE_DIR}/acidcam.pc.in ${CMAKE_CURRENT_BINARY_DIR}/acidcam.pc @ONLY)

install(TARGETS acidcam
    EXPORT acidcamTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES ${header} DESTINATION "${include_dest}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/acidcam.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)

install(EXPORT acidcamTargets
    FILE acidcamTargets.cmake
    NAMESPACE acidcam::
    DESTINATION lib/cmake/acidcam
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfigVersion.cmake"
    VERSION ${ACIDCAM_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfig.cmake"
    INSTALL_DESTINATION lib/cmake/acidcam
    PATH_VARS include_dest main_lib_dest
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/acidcamConfigVersion.cmake"
    DESTINATION lib/cmake/acidcam
)

target_include_directories(acidcam PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${include_dest}>
)

#add_subdirectory("examples")

if(ENABLE_TESTS)
    add_executable(test-filter1 ${CMAKE_SOURCE_DIR}/tests/test-filters.cpp)
    target_link_libraries(test-filter1 acidcam Threads::Threads)
    target_compile_options(test-filter1 PRIVATE ${COMPILER_FLAGS})
    add_executable(test-image ${CMAKE_SOURCE_DIR}/tests/test-image-filters.cpp)
    target_link_libraries(test-image acidcam Threads::Threads)
    target_compile_options(test-image PRIVATE ${COMPILER_FLAGS})
    add_executable(test-subfilter ${CMAKE_SOURCE_DIR}/tests/test-subfilter.cpp)
    target_link_libraries(test-subfilter acidcam Threads::Threads)
    target_compile_options(test-subfilter PRIVATE ${COMPILER_FLAGS})
    add_executable(test-filter-ex ${CMAKE_SOURCE_DIR}/tests/test-filter-ex.cpp)
    target_link_libraries(test-filter-ex acidcam Threads::Threads)
    target_compile_options(test-filter-ex PRIVATE ${COMPILER_FLAGS})
endif()

if(ENABLE_TESTS)
    enable_testing()
    add_test(NAME test1 COMMAND $<TARGET_FILE:test-filter1>)
    add_test(NAME test2 COMMAND $<TARGET_FILE:test-image>)
    add_test(NAME test3 COMMAND $<TARGET_FILE:test-subfilter>)
endif()
