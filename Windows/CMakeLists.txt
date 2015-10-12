
if(WIN32)
cmake_minimum_required (VERSION 3.1)
else()
cmake_minimum_required (VERSION 3.0)
endif()

project(VixenEngine)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Version info
set (VixenEngine_VERSION_MAJOR 0)
set (VixenEngine_VERSION_MINOR 1)
set (VixenEngine_VERSION_BUILD 1)

#configure header file to pass
#CMake settings to source code
configure_file (
    "${PROJECT_SOURCE_DIR}/../include/vix_version.h.in"
    "${PROJECT_SOURCE_DIR}/../include/vix_version.h"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/vcore")
add_subdirectory("${PROJECT_SOURCE_DIR}/vgraphics")
add_subdirectory("${PROJECT_SOURCE_DIR}/vgame")
add_subdirectory("${PROJECT_SOURCE_DIR}/vtest")
