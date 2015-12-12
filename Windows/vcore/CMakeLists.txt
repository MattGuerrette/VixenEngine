
include_directories("${PROJECT_SOURCE_DIR}/../include"
                    "${PROJECT_SOURCE_DIR}/../include/vcore"
                    "${PROJECT_SOURCE_DIR}/../dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/inih")
					
file(GLOB VCORE_INC ../../include/vcore/*.h)
file(GLOB VCORE_SRC ../../source/vcore/*.cpp ${PROJECT_SOURCE_DIR}/../dependencies/x64/inih/*.c)


if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()

add_definitions(-D_UNICODE)

link_directories(../../dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/)

add_library(vcore SHARED ${VCORE_INC} ${VCORE_SRC})

target_compile_definitions(vcore PRIVATE VIX_NONCLIENT_BUILD)


target_link_libraries(vcore tinyxml2)