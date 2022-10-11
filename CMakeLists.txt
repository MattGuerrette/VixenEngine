cmake_minimum_required(VERSION 3.23)
project(VixenEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
        inih
        GIT_REPOSITORY https://github.com/benhoyt/inih.git
        GIT_TAG "r56"
)
FetchContent_Declare(
        luaintf
        GIT_REPOSITORY https://github.com/SteveKChiu/lua-intf.git
        GIT_TAG master
)
FetchContent_MakeAvailable(inih luaintf)

find_package(tinyxml2 CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

set(CORE_SOURCE
        include/vix_algorithms.h
        include/vix_asset.h
        include/vix_containers.h
        include/vix_debugutil.h
        include/vix_file.h
        include/vix_file_interface.h
        include/vix_filemanager.h
        include/vix_fileutil.h
        include/vix_inireader.h
        include/vix_iniwriter.h
        include/vix_jsoncpp.h
        include/vix_manager.h
        include/vix_noncopy.h
        include/vix_osutil.h
        include/vix_pathmanager.h
        include/vix_platform.h
        include/vix_singleton.h
        include/vix_stlutil.h
        include/vix_stringutil.h
        include/vix_tinyxml.h
        include/vix_typedefs.h
        source/vix_asset.cpp
        source/vix_debugutil.cpp
        source/vix_file.cpp
        source/vix_filemanager.cpp
        source/vix_fileutil.cpp
        source/vix_inireader.cpp
        source/vix_iniwriter.cpp
        source/vix_osutil.cpp
        source/vix_pathmanager.cpp
        source/vix_stringutil.cpp
        ${inih_SOURCE_DIR}/ini.c)

set(GRAPHICS_SOURCE
        include/vix_assimp.h
        include/vix_bmfont.h
        include/vix_camera.h
        include/vix_camera2d.h
        include/vix_camera3d.h
        include/vix_color.h
        include/vix_directx.h
        include/vix_dxcamera2d.h
        include/vix_dxcamera3d.h
        include/vix_dxdefferedbuffers.h
        include/vix_dxindexbuffer.h
        include/vix_dxinstancebuffer.h
        include/vix_dxlightbuffer.h
        include/vix_dxmaterial.h
        include/vix_dxmathfunctions.h
        include/vix_dxmodel.h
        include/vix_dxpixelshader.h
        include/vix_dxquad.h
        include/vix_dxrenderer.h
        include/vix_dxresourceloader.h
        include/vix_dxshader.h
        include/vix_dxspritebatcher.h
        include/vix_dxtexture.h
        include/vix_dxvertexbuffer.h
        include/vix_dxvertexshader.h
        include/vix_font.h
        include/vix_freeimage.h
        include/vix_indexbuffer.h
        include/vix_instancebuffer.h
        include/vix_light.h
        include/vix_lightbuffer.h
        include/vix_material.h
        include/vix_math.h
        include/vix_mathfunctions.h
        include/vix_model.h
        include/vix_rectangle.h
        include/vix_renderer.h
        include/vix_renderer_singleton.h
        include/vix_resourceloader.h
        include/vix_resourcemanager.h
        include/vix_shader.h
        include/vix_shadervariable.h
        include/vix_spritebatcher.h
        include/vix_texture.h
        include/vix_vector3.h
        include/vix_vector2.h
        include/vix_vertexbuffer.h
        source/vix_assimp.cpp
        source/vix_bmfont.cpp
        source/vix_dxcamera2d.cpp
        source/vix_dxcamera3d.cpp
        source/vix_dxdefferedbuffers.cpp
        source/vix_dxindexbuffer.cpp
        source/vix_dxinstancebuffer.cpp
        source/vix_dxlightbuffer.cpp
        source/vix_dxmaterial.cpp
        source/vix_dxmathfunctions.cpp
        source/vix_dxmodel.cpp
        source/vix_dxpixelshader.cpp
        source/vix_dxrenderer.cpp
        source/vix_dxresourceloader.cpp
        source/vix_dxshader.cpp
        source/vix_dxspritebatcher.cpp
        source/vix_dxtexture.cpp
        source/vix_dxvertexbuffer.cpp
        source/vix_dxvertexshader.cpp
        source/vix_font.cpp
        source/vix_freeimage.cpp
        source/vix_material.cpp
        source/vix_math.cpp
        source/vix_mathfunctions.cpp
        source/vix_model.cpp
        source/vix_rectangle.cpp
        source/vix_renderer_singleton.cpp
        source/vix_resourcemanager.cpp
        source/vix_shader.cpp
        source/vix_shadervariable.cpp
        source/vix_texture.cpp
        source/vix_vector3.cpp
        source/vix_vector2.cpp)

set(GAME_SOURCE
        include/spotlightcomponent.h
        include/vix_aabb.h
        include/vix_bullet.h
        include/vix_bullet_boxcollider.h
        include/vix_bullet_collidershape.h
        include/vix_bullet_planecollider.h
        include/vix_bullet_spherecollider.h
        include/vix_bulletsimulator.h
        include/vix_camera2Dcomponent.h
        include/vix_camera3Dcomponent.h
        include/vix_component.h
        include/vix_curl.h
        include/vix_curl_singleton.h
        include/vix_directionlightcomponent.h
        include/vix_game.h
        include/vix_gameconfig.h
        include/vix_gameobject.h
        include/vix_gamewindow.h
        include/vix_input.h
        include/vix_keyboardstate.h
        include/vix_lightmanager.h
        include/vix_lua.h
        include/vix_luaengine.h
        include/vix_luascript.h
        include/vix_luascriptmanager.h
        include/vix_modelcomponent.h
        include/vix_mousestate.h
        include/vix_objectmanager.h
        include/vix_pathmanager.h
        include/vix_pointlightcomponent.h
        include/vix_prefab.h
        include/vix_prefabmanager.h
        include/vix_rendercomponent.h
        include/vix_rendercomponent2D.h
        include/vix_rigidbody_component.h
        include/vix_scene.h
        include/vix_scenemanager.h
        include/vix_sdlinput.h
        include/vix_sdlwindow.h
        include/vix_spotlightcomponent.h
        include/vix_time.h
        include/vix_transform.h
        include/vix_uicomponent.h
        include/vix_uitext.h
        include/vix_window_singleton.h
        source/vix_aabb.cpp
        source/vix_bullet_boxcollider.cpp
        source/vix_bullet_collidershape.cpp
        source/vix_bullet_planecollider.cpp
        source/vix_bullet_spherecollider.cpp
        source/vix_bulletsimulator.cpp
        source/vix_camera2Dcomponent.cpp
        source/vix_camera3Dcomponent.cpp
        source/vix_game.cpp
        source/vix_gameconfig.cpp
        source/vix_gameobject.cpp
        source/vix_input.cpp
        source/vix_lightmanager.cpp
        source/vix_luaengine.cpp
        source/vix_luascript.cpp
        source/vix_luascriptmanager.cpp
        source/vix_modelcomponent.cpp
        source/vix_objectmanager.cpp
        source/vix_pathmanager.cpp
        source/vix_pointlightcomponent.cpp
        source/vix_prefab.cpp
        source/vix_prefabmanager.cpp
        source/vix_rigidbody_component.cpp
        source/vix_scene.cpp
        source/vix_scenemanager.cpp
        source/vix_sdlinput.cpp
        source/vix_sdlwindow.cpp
        source/vix_spotlightcomponent.cpp
        source/vix_time.cpp
        source/vix_transform.cpp
        source/vix_uitext.cpp
        source/vix_window_singleton.cpp
        )

add_library(${PROJECT_NAME} SHARED
        ${CORE_SOURCE}
        ${GRAPHICS_SOURCE}
        ${GAME_SOURCE}
        )
target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE ${inih_SOURCE_DIR} ${luaintf_SOURCE_DIR} ${LUA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC d3d11 d3dcompiler SDL2::SDL2 tinyxml2::tinyxml2 assimp::assimp freeimage::FreeImage
        freeimage::FreeImagePlus LinearMath Bullet3Common BulletCollision BulletDynamics BulletSoftBody ${LUA_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PRIVATE VIX_NONCLIENT_BUILD UNICODE)

add_executable(VixenTest WIN32
        source/main.cpp)
target_link_libraries(VixenTest PRIVATE ${PROJECT_NAME})