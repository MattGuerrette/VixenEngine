
<img src="https://raw.githubusercontent.com/MattGuerrette/VixenEngine/master/assets/Others/vixen.png?token=AGF82f6bQ31yR9rHAllCYsrR50J2y6ebks5WGJ5twA%3D%3D">

# Vixen Engine
C++ Open Source Game Engine

# About

Vixen Engine, is an attempt to develop a completely free and open game engine for use in commerical, academic, and personal
projects. It was initially developed at Rochester Institue of Technology for class projects in the Game Design and Development curriculum.

# Platforms

Vixen Engine currently targets the following platforms:

* Windows ( Windows 10, Windows 7 )
* Linux   ( Ubuntu )

# Dependencies

* SDL2
* GLEW
* DirectX (DirectX 11)
* OpenGL  (OpenGL 3.3+)
* Assimp
* FreeImage
* tinyxml2
* Lua
* lua-intf

# Building

Build instructions are available for Ubuntu Linux and Microsoft Windows

## Windows (64-bit)

Included in the repository is a Visual Studio 2015 solution file. It is already setup to build and run Vixen Engine targeting x64. There are currently no plans to target 32-bit and there are no prebuilt dependencies in the repository. If you wish to develop a 32 bit version of Vixen, you will have to retrieve all the depencies and build 32-bit versions.

If you have any issues getting the VS2015 solution file to open and VCore, VGraphics, VGame, or VTest project files
to build, please file an issue.

NOTE: All dependencies have been included prebuilt targeting x64 with VC++14 compiler in the repository for building on Windows.

## Linux

Currently, Vixen Engine is being developed on Linux using just a Makefile and g++. There is no CMAKE build system in place.

If you wish to develop Vixen for Linux you may need to make slight modifications to the Makefile included in the Linux directory of the Vixen Engine repository.

* Make Targets
  * vcore     (libvcore)
  * vgraphics (libvgraphics)
  * vgame     (libvgame)
  * vtest     (vtest application)

NOTE: All Vixen libraries will output to /usr/local/lib as specified in Makefile.
