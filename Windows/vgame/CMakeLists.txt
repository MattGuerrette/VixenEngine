
include_directories("${PROJECT_SOURCE_DIR}/../include"
                    "${PROJECT_SOURCE_DIR}/../include/vcore"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../include/vgame"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/Assimp/include"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/FreeImage"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/SDL2/include"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/lua/include"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/luaintf/"
                    "${PROJECT_SOURCE_DIR}/../dependencies/x64/lua/include")

file(GLOB VGAME_INC ../../include/vgame/*.h)
file(GLOB VGAME_SRC ../../source/vgame/*.cpp)

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()


add_definitions(-DLUAINTF_HEADERS_ONLY)
add_definitions(-DVIX_DIRECTX_BUILD)
add_definitions(-DVIX_NOEXTERN_LUA)
add_definitions(-D_UNICODE)

link_directories(../../dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/ 
                 ../../dependencies/x64/Assimp/ 
				 ../../dependencies/x64/FreeImage/
				 ../../dependencies/x64/SDL2/
				 ../../dependencies/x64/lua/)

add_library(vgame SHARED ${VGAME_INC} ${VGAME_SRC})

target_compile_definitions(vgame PRIVATE VIX_NONCLIENT_BUILD)

target_link_libraries(vgame vcore vgraphics SDL2 lua tinyxml2 Assimp Freeimage)