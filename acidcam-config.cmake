#get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
#include(${SELF_DIR}/${CMAKE_BUILD_TYPE}/acidcam.cmake)


get_filename_component(ACIDCAM_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(ACIDCAM_INCLUDE_DIRS "@CONF_INCLUDE_DIRS@")
include("${ACIDCAM_CMAKE_DIR}/acidcam.cmake")

set(ACIDCAM_LIBRARIES ${CMAKE_INSTALL_PREFIX}/lib/acidcam)




