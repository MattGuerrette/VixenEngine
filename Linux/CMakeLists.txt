

cmake_minimum_required (VERSION 3.0)


project(VixenEngine)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Version info
set (VixenEngine_VERSION_MAJOR 0)
set (VixenEngine_VERSION_MINOR 1)
set (VixenEngine_VERSION_BUILD 1)

# Compiler flag
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -w -g")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#configure header file to pass
#CMake settings to source code
configure_file (
    "${PROJECT_SOURCE_DIR}/../include/vix_version.h.in"
    "${PROJECT_SOURCE_DIR}/../include/vix_version.h"
)

include_directories("${PROJECT_SOURCE_DIR}/../include"
                    "${PROJECT_SOURCE_DIR}/../include/vcore"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics/opengl"
                    "${PROJECT_SOURCE_DIR}/../include/vgame"
                    "${PROJECT_SOURCE_DIR}/../dependencies/x64/glm"
                    "${PROJECT_SOURCE_DIR}/../dependencies/x64/luaintf"
                    "/usr/include/lua5.2")

file(GLOB VCORE_SRC ../source/vcore/*.cpp)
file(GLOB VGRAPHICS_SRC ../source/vgraphics/*.cpp)
file(GLOB VGRAPHICS_GL_SRC ../source/vgraphics/opengl/*.cpp)
file(GLOB VGAME_SRC ../source/vgame/*.cpp)

add_definitions(-DLUAINTF_HEADERS_ONLY)
add_definitions(-DVIX_OPENGL_BUILD)

add_library(vcore SHARED ${VCORE_SRC})
add_library(vgraphics SHARED ${VGRAPHICS_SRC} ${VGRAPHICS_GL_SRC})
add_library(vgame SHARED ${VGAME_SRC})

target_link_libraries(vgraphics vcore GLEW GL archive freeimage)
target_link_libraries(vgame vcore vgraphics SDL2 lua5.2 tinyxml2 archive freeimage)

add_executable(vtest ${PROJECT_SOURCE_DIR}/../source/vtest/cmaketest.cpp)
target_link_libraries(vtest vcore vgraphics vgame SDL2 lua5.2 tinyxml2 archive freeimage)

#install

install (TARGETS vcore vgraphics vgame DESTINATION lib)
install (TARGETS vtest DESTINATION bin)
install (FILES vixen.config vixen.env DESTINATION bin)
install (DIRECTORY ../assets DESTINATION bin)
