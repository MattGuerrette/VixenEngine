

include_directories("${PROJECT_SOURCE_DIR}/../include"
                    "${PROJECT_SOURCE_DIR}/../include/vcore"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../include/vgame"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/Assimp/include"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/FreeImage"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/SDL2/include"
                    "${PROJECT_SOURCE_DIR}/../dependencies/x64/lua/include")

message(STATUS ${CMAKE_GENERATOR_PLATFORM})

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
	set(PLATFORM_TOOLSET "VS2013")
else()
	set(PLATFORM_TOOLSET "VS2015")
endif()
					
					
add_definitions(-D_UNICODE)

link_directories(../../dependencies/x64/tinyxml2/${PLATFORM_TOOLSET}/Debug/ 
                 ../../dependencies/x64/Assimp/ 
				 ../../dependencies/x64/FreeImage/
				 ../../dependencies/x64/SDL2/
				 ../../dependencies/x64/lua/)

add_executable(vtest ${PROJECT_SOURCE_DIR}/../source/vtest/main.cpp)

target_compile_definitions(vtest PRIVATE VIX_DIRECTX_BUILD)

add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vixen.env $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/vixen.config $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   $(SolutionDir)vcore/$(Configuration)/vcore.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   $(SolutionDir)vgraphics/$(Configuration)/vgraphics.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   $(SolutionDir)vgame/$(Configuration)/vgame.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/../dependencies/$(Platform)/Assimp/assimp.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/../dependencies/$(Platform)/tinyxml2/${PLATFORM_TOOLSET}/$(Configuration)/tinyxml2.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/../dependencies/$(Platform)/lua/lua.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/../dependencies/$(Platform)/FreeImage/FreeImage.dll $<TARGET_FILE_DIR:vtest>)
add_custom_command(TARGET vtest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/../dependencies/$(Platform)/SDL2/SDL2.dll $<TARGET_FILE_DIR:vtest>)

target_link_libraries(vtest vcore vgraphics vgame SDL2 lua tinyxml2 Assimp Freeimage)


