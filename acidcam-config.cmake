# This file is for backward compatibility
# Modern CMake projects should use acidcamConfig.cmake through find_package(acidcam CONFIG)
#
# Usage in CMakeLists.txt:
#   find_package(acidcam CONFIG REQUIRED)
#   target_link_libraries(your_target PRIVATE acidcam::acidcam)

get_filename_component(ACIDCAM_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
include("${ACIDCAM_CMAKE_DIR}/Config.cmake.in" OPTIONAL)

# For backward compatibility, also try the built config if available
if(DEFINED CMAKE_PREFIX_PATH AND NOT TARGET acidcam::acidcam)
    get_filename_component(ACIDCAM_INSTALL_DIR "${ACIDCAM_CMAKE_DIR}" DIRECTORY)
    if(EXISTS "${ACIDCAM_INSTALL_DIR}/cmake/acidcam/acidcamConfig.cmake")
        include("${ACIDCAM_INSTALL_DIR}/cmake/acidcam/acidcamConfig.cmake")
    endif()
endif()



