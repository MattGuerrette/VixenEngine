

include_directories("${PROJECT_SOURCE_DIR}/../include"
                    "${PROJECT_SOURCE_DIR}/../include/vcore"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics"
                    "${PROJECT_SOURCE_DIR}/../include/vgraphics/directx"
					"${PROJECT_SOURCE_DIR}/../include/vgame"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/tinyxml2"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/inih"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/Assimp/include"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/FreeImage"
					"${PROJECT_SOURCE_DIR}/../dependencies/x64/bullet3/src/"
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
				 ../../dependencies/x64/lua/
				 ../../dependencies/x64/bullet3/)
                 
file(GLOB FONT_FILES ${PROJECT_SOURCE_DIR}/../assets/Fonts/*.fnt)
file(GLOB MODEL_FILES ${PROJECT_SOURCE_DIR}/../assets/Models/*.mdl)
file(GLOB MATERIAL_FILES ${PROJECT_SOURCE_DIR}/../assets/Materials/*.vmt)
file(GLOB PREFAB_FILES ${PROJECT_SOURCE_DIR}/../assets/Prefabs/*.pfb)
file(GLOB SCENE_FILES ${PROJECT_SOURCE_DIR}/../assets/Scenes/*.scene)
file(GLOB SCENE_CONFIG ${PROJECT_SOURCE_DIR}/../assets/Scenes/scenes.config)
file(GLOB SCRIPT_FILES ${PROJECT_SOURCE_DIR}/../assets/Scripts/*.lua)
file(GLOB HLSL_VS_FILES ${PROJECT_SOURCE_DIR}/../assets/Shaders/DirectX/*_VS.hlsl)
file(GLOB HLSL_PS_FILES ${PROJECT_SOURCE_DIR}/../assets/Shaders/DirectX/*_PS.hlsl)
file(GLOB GLSL_FILES ${PROJECT_SOURCE_DIR}/../assets/Shaders/OpenGL/*.glsl)
file(GLOB TEXTURE_FILES ${PROJECT_SOURCE_DIR}/../assets/Textures/*.png ${PROJECT_SOURCE_DIR}/../assets/Textures/*.jpg)

set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_TYPE Pixel)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_ENTRYPOINT main)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${HLSL_PS_FILES} PROPERTY VS_SHADER_FLAGS "/DFLAGS_ADDED /Fh \"$(OutDir)%(Filename).h\"")

set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_TYPE Vertex)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_ENTRYPOINT main)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_MODEL 5.0)
set_property(SOURCE ${HLSL_VS_FILES} PROPERTY VS_SHADER_FLAGS "/DFLAGS_ADDED /Fh \"$(OutDir)%(Filename).h\"")

source_group("Asset Files\\Models" FILES ${MODEL_FILES})
source_group("Asset Files\\Materials" FILES ${MATERIAL_FILES})
source_group("Asset Files\\Fonts" FILES ${FONT_FILES})
source_group("Asset Files\\Prefabs" FILES ${PREFAB_FILES})
source_group("Asset Files\\Scenes" FILES ${SCENE_FILES} ${SCENE_CONFIG})
source_group("Asset Files\\Scripts" FILES ${SCRIPT_FILES})
source_group("Asset Files\\Shaders\\HLSL" FILES ${HLSL_VS_FILES} ${HLSL_PS_FILES})
source_group("Asset Files\\Shaders\\GLSL" FILES ${GLSL_FILES})
source_group("Asset Files\\Textures" FILES ${TEXTURE_FILES})

set(RESOURCE_FILES ${MODEL_FILES} ${FONT_FILES} ${PREFAB_FILES} ${SCENE_FILES} ${SCENE_CONFIG} ${SCRIPT_FILES} ${HLSL_VS_FILES} ${HLSL_PS_FILES} ${GLSL_FILES} ${TEXTURE_FILES} ${MATERIAL_FILES})

add_executable(vtest ${PROJECT_SOURCE_DIR}/../source/vtest/main.cpp ${RESOURCE_FILES})

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

target_link_libraries(vtest vcore vgraphics vgame SDL2 lua tinyxml2 Assimp Freeimage BulletCollision BulletDynamics BulletSoftBody LinearMath)


